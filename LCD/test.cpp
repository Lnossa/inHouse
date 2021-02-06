#include <iostream>
#include <wiringPi.h>
#include "LCD.h"


void LCDDriver::lcdTest(LCDDriver* pLCDDriver) 
{

	//lcdPuts(res, "Ti pup, ti pup!");
	int opt;
	bool loop = true;
	std::string text = "";
	int on = 0;
	int k = 0;

	while (loop)
	{
		std::cout << "Command:" << std::endl <<
			"1. lcdInit()" << std::endl <<
			"2. lcdClearScr()" << std::endl <<
			"3. lcdHome()" << std::endl <<
			"4. lcdSetPosition()" << std::endl <<
			"5. lcdSetDisplay()" << std::endl <<
			"6. lcdSetCursor" << std::endl <<
			"7. lcdSetCursorBlink" << std::endl <<
			"8. Enter Text" << std::endl <<
			"9. Shift" << std::endl <<
			"10. Print char" << std::endl;

		std::cin >> opt;
		pLCDDriver->mMutex.lock();
		switch (opt)
		{
		case 1:
			pLCDDriver->lcdInit();
			break;
		case 2:
			pLCDDriver->lcdClearScr();
			break;
		case 3:
			pLCDDriver->lcdHome();
			break;
		case 4:
			pLCDDriver->lcdSetPosition(18, 1);
			break;
		case 5:
			std::cin >> on;
			pLCDDriver->lcdSetDisplay(on);
			break;
		case 6:
			std::cin >> on;
			pLCDDriver->lcdSetCursor(on);
			break;
		case 7:
			std::cin >> on;
			pLCDDriver->lcdSetCursorBlink(on);
			break;
		case 8:
			std::cin.ignore();
			std::getline(std::cin, text);
			pLCDDriver->lcdSetPosition(0, 0);
			pLCDDriver->lcdPuts(text.c_str());
			break;
		case 9:
			while (k < 40)
			{
				pLCDDriver->lcdShift(2);
				delay(500);
				k++;
			}
			k = 0;
			break;
		case 10:
			std::cin.ignore();
			std::getline(std::cin, text);
			pLCDDriver->lcdSetPosition(15, 0);
			pLCDDriver->lcdPrintCustomChar(std::stoi(text, nullptr));
			break;
		default:
			loop = false;
			break;
		}
		pLCDDriver->mMutex.unlock();
	}
}

//int main()
//{
//	wiringPiSetup();
//	LCDDriver x;
//	x.lcdTest(&x);
//	return 0;
//}