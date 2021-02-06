#include "LCD.h"


LCDDriver::LCDDriver()
{
}

void LCDDriver::lcdInit()
{
	digitalWrite(RS, 0);
	pinMode(RS, OUTPUT);
	digitalWrite(EN, 0);
	pinMode(EN, OUTPUT);
	digitalWrite(D4, 0);
	pinMode(D4, OUTPUT);
	digitalWrite(D5, 0);
	pinMode(D5, OUTPUT);
	digitalWrite(D6, 0);
	pinMode(D6, OUTPUT);
	digitalWrite(D7, 0);
	pinMode(D7, OUTPUT);
	delay(50);

	//Set 4 bits. 
	writeData(0x3);
	writeData(0x3);
	writeData(0x3);
	writeData(0x2);
	
	putCmd(0x28);

	//std::cout << "Set: Display ON, Cursor ON, Cursor POS ON" << std::endl;
	lcdSetDisplay(1);
	lcdSetCursor(0);
	lcdSetCursor(0);

	//std::cout << "Display clear" << std::endl;
	lcdClearScr();

	//std::cout << "Entry mode set" << std::endl;
	putCmd(0x06);

	//std::cout << "Setup Done." << std::endl << std::endl;

	//std::cout << std::endl;
	//Add custom characters
	uint8_t cloud[8] = { 0x03,0x0F,0x1F,0x1F,0x0F,0x00,0x00,0x00 };
	uint8_t rain[8] = { 0x03,0x0F,0x1F,0x1F,0x0F,0x02,0x08,0x05 };
	uint8_t sun[8] = { 0x13,0x0F,0x07,0x1F,0x07,0x0F,0x13,0x05 };
	lcdCreateCustomChar(0, cloud);
	lcdCreateCustomChar(1, rain);
	lcdCreateCustomChar(2, sun);
}

void LCDDriver::writeData(int data)
{
	digitalWrite(D4, (data & 1));
	digitalWrite(D5, (data >> 1 & 1));
	digitalWrite(D6, (data >> 2 & 1));
	digitalWrite(D7, (data >> 3 & 1));
	
	delay(1);
	digitalWrite(EN, 1);
	delay(1);
	digitalWrite(EN, 0);
	delay(5);

	//std::cout << "Wrote " << (data >> 3 & 1)  << (data >> 2 & 1) << (data >> 1 & 1) << (data & 1)  << std::endl;
}

void LCDDriver::putCmd(uint8_t cmd) {
	digitalWrite(RS, 0);
	writeData((cmd & 0xF0) >> 4);
	writeData(cmd & 15);
}

void LCDDriver::putChar(int cmd) {
	digitalWrite(RS, 1);
	writeData((cmd & 0xF0) >> 4);
	writeData(cmd & 0x0F);
}

void LCDDriver::lcdSetPosition(int x, int y) {
//ignore conversion warning in cmd |= x
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"

	uint8_t cmd = 0x80;
	if (y == 1)
		cmd |= 0x40;
	cmd += x;
	putCmd(cmd);

#pragma GCC diagnostic pop
}

void LCDDriver::lcdClearScr() 
{
	putCmd(CMD_CLEAR);
}

void LCDDriver::lcdHome()
{
	putCmd(CMD_HOME);
}

void LCDDriver::lcdSetDisplay(bool on)
{
	uint8_t cmd = CMD_DISPLAY;
	if (on) cmd |= CMD_DISPLAY_ON;
	if (mCursor) cmd |= CMD_DISPLAY_CURSOR;
	if (mCursorBlink) cmd |= CMD_DISPLAY_CURSOR_BLINK;

	putCmd(cmd);
	mDisplay = on;
}

void LCDDriver::lcdSetCursor(bool on)
{
	uint8_t cmd = CMD_DISPLAY;
	if (mDisplay) cmd |= CMD_DISPLAY_ON;
	if (on) cmd |= CMD_DISPLAY_CURSOR;
	if (mCursorBlink) cmd |= CMD_DISPLAY_CURSOR_BLINK;

	putCmd(cmd);
	mCursor = on;
}

void LCDDriver::lcdSetCursorBlink(bool on) 
{
	uint8_t cmd = CMD_DISPLAY;
	if (mDisplay) cmd |= CMD_DISPLAY_ON;
	if (mCursor) cmd |= CMD_DISPLAY_CURSOR;
	if (on) cmd |= CMD_DISPLAY_CURSOR_BLINK;

	putCmd(cmd);
	mCursorBlink = on;
}

void LCDDriver::lcdPuts(const char* string) 
{
	logging::TRACE("LCD >> Write to screen: %s", string);
	while (*string)
		putChar(*string++);
}

void LCDDriver::lcdPrintf(const char* string, ...)
{
	va_list argp;
	char buffer[1024];

	va_start(argp, string);
	vsnprintf(buffer, 1023, string, argp);
	va_end(argp);

	lcdPuts(buffer);
}

void LCDDriver::lcdShift(int dir)
{
	uint8_t cmd = dir == 2 ? CMD_SHIFT_R : CMD_SHIFT_L;
	putCmd(cmd);
}

void LCDDriver::lcdCreateCustomChar(int pos, uint8_t byte[8])
{
	uint8_t cmd = static_cast<uint8_t>(CMD_CGRAM_ADDR | (pos << 3));
	putCmd(cmd);
	for (int i = 0; i < 8; i++)
		putChar(byte[i]);
}

void LCDDriver::lcdPrintCustomChar(int pos)
{
	uint8_t c = 0x07 & pos;
	putChar(c);
}

void LCDDriver::Lock() 
{
	std::chrono::seconds wait(1);
	if (!mMutex.try_lock_for(wait))
	{
		logging::ERROR("LCD >> Failed try_lock_for(%d)! Doing simple lock()...", wait);
		mMutex.lock();
	}
	logging::TRACE("LCDDriver >> Mutex || Obtained lock.");
}

void LCDDriver::Unlock()
{
	mMutex.unlock();
	logging::TRACE("LCD >> Mutex || Released lock");
}