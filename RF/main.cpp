#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#include <pigpio.h>


#define IRQ 25
#define TX_CMD 0xB800

int tx = 0;
int rx = 0;

void interrupt();
int sendCmd(int data);
void printHex(int data);
void readStatus();
void printStatus();
void printRXBuffer();


int rxBuf[100][4];
int rxPos = 0;
int rxCount = 0;

void setTX();
void setRX();

uint8_t onCmd[8] = { 0xAA, 0x2D, 0xD4, 0xE8, 0x01, 0xE9, 0x55, 0xFF };
uint8_t offCmd[8] = { 0xAA, 0x2D, 0xD4, 0xE8, 0x02 ,0xEA ,0x55, 0xFF };

int pos = 0;
int count = 25;
int errCount = 0;
int okCount = 0;


int main()
{
	int res;
	res = wiringPiSetup();

	if (res < 0)
	{
		std::cout << "Error wiringPi " << res << std::endl;
		return 1;
	}

	pinMode(IRQ, INPUT);
	wiringPiISR(IRQ, INT_EDGE_FALLING, &interrupt);
	
	res = wiringPiSPISetup(1,1000000);

	if (res < 0)
	{
		std::cout << "Error init SPI " << res << std::endl;
		return 1;
	}

	//Setup RF
	sendCmd(0xFE00);
	delay(100);
	sendCmd(0x8027); 
	sendCmd(0x8259);
	sendCmd(0xA67F);
	sendCmd(0xC691);
	sendCmd(0x94A0);
	sendCmd(0xC2AF);
	sendCmd(0xCA85);
	sendCmd(0xCED4);
	sendCmd(0xC483);
	sendCmd(0x9830);
	sendCmd(0xCC77);
	sendCmd(0xE000);
	sendCmd(0xC800);
	sendCmd(0xC009);
	
	std::cout << "Initial ";
	readStatus();
	printStatus();
	//setTX();
	setRX();

	while (true)
	{
		delay(10000);
		printStatus();

		if (rx && rxCount > 0)
			printRXBuffer();

		if (tx && count == 0)
		{
			std::cout << std::dec << "TX Done. OK: " << okCount << " Err: " << errCount << std::endl;
			pos = 0;
			count = 25;
			okCount = 0;
			errCount = 0;
			setTX();
		}
	}
	return 0;
}



void interrupt()
{
	int status = sendCmd(0x0000);

	if (tx)
	{
		if (status & 0x2000)
			errCount++;
		if (status & 0x8000)
			okCount++;

		if (pos < 8)
		{
			sendCmd(TX_CMD | offCmd[pos]);
			pos++;
		
		}
		else
		{
			sendCmd(0x8250); //Disable TX
			sendCmd(0x8027); //Disable TX Register
			count--;
			pos = 0;
			
			if (count > 0)
			{
				delay(18);
				setTX();
			}
		}
	}
	else
	{
		if (status & 0x8000)
		{
			if (rxPos < 4)
			{
				rxBuf[rxCount][rxPos] = sendCmd(0xB000) & 0xFF;
				rxPos++;
			}
			else
			{
				rxCount++;
				rxPos = 0;
				sendCmd(0xCA81); //disable FIFO
				sendCmd(0xCA83); //enable FIFO
			}
		}
		else if (status & 0x2000)
			std::cout << "FIFO overflow" << std::endl;

	}
}

void setTX() 
{
	tx = 1;
	rx = 0;
	sendCmd(0x80A7); //Enable TX Register
	sendCmd(0x8270); //Enable TX
}

void setRX()
{
	rx = 1;
	tx = 0;
	sendCmd(0x8067); //Enable FIFO Buffer
	sendCmd(0x82D0); //Enable RX
	sendCmd(0xCA81); //disable FIFO
	sendCmd(0xCA83); //enable FIFO
}



void readStatus()
{
	int status;
	status = sendCmd(0x0000);
	std::cout << "Status:";
	printHex(status);
}

int sendCmd(int data)
{
	unsigned char dataArr[2];
	dataArr[1] = static_cast<unsigned char>(data & 0xFF);
	dataArr[0] = static_cast<unsigned char>((data >> 8) & 0xFF);

	int res;
	res = wiringPiSPIDataRW(1, dataArr, 2);


	if (res < 0)
	{
		std::cout << "Error Read/Write" << std::endl;
	}

	return (dataArr[0] << 8) | dataArr[1];
}

void printHex(int data)
{
	std::cout << " 0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << data << std::endl;
}

void printRXBuffer()
{
	std::cout << "Received " << rxCount << " messages: " << std::endl;
	for(int i = 0; i < rxCount; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << " 0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << rxBuf[i][j];
		}
		std::cout << std::endl;
	}
	rxCount = 0;
	rxPos = 0;
}

void printStatus()
{
	int iStatus = sendCmd(0x0000);
	char sStatus[100];// = "Status: ";
	
	sprintf(sStatus, "Status (0x%04X): ", iStatus);

	if (iStatus & 0x4000) strcat(sStatus, "Power-On Reset, ");
	if (iStatus & 0x2000) strcat(sStatus, tx ? "TX Register Underrun, " : "RX FIFO Overflow, ");
	if (iStatus & 0x0200) strcat(sStatus, "FIFO is empty, ");

	if (strlen(sStatus) == 17)
		strcat(sStatus, "OK!");
	else
		sStatus[strlen(sStatus) - 2] = 0;
	std::cout << sStatus << std::endl;
}