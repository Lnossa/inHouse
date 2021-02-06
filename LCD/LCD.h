#pragma once
#include<iostream>
#include<stdarg.h>
#include<thread>
#include<mutex>
#include "wiringPi.h"
#include "Logger/Logger.h"

#define RS 26 //Phys Pin 32;
#define EN 31 //Phys Pin 28;
#define D4 10 //Phys Pin 24;
#define D5 6  //Phys Pin 22;
#define D6 5  //Phys Pin 18;
#define D7 4  //Phys Pin 16;

#define CMD_CLEAR					0x01
#define CMD_HOME					0x02

#define CMD_DISPLAY					0x08
#define CMD_DISPLAY_ON				0x04
#define CMD_DISPLAY_CURSOR			0x02
#define CMD_DISPLAY_CURSOR_BLINK	0x01
#define CMD_DISPLAY_POS				0x01
#define	CMD_CLEAR					0x01

#define CMD_SHIFT_R					0x18
#define CMD_SHIFT_L					0x1C

#define CMD_CGRAM_ADDR				0x40


#define LCD_CHR_CLOUD				0
#define LCD_CHR_RAIN				1
#define LCD_CHR_SUN					2


class LCDDriver
{

	
private:

	bool mCursor = false;
	bool mCursorBlink = false;
	bool mDisplay = false;
	std::recursive_timed_mutex mMutex;

	void writeData(int data);
	void putChar(int cmd);
	void putCmd(uint8_t cmd);
public:

	LCDDriver();
	void lcdInit();
	void lcdClearScr();
	void lcdHome();
	void lcdSetPosition(int x, int y);
	
	void lcdSetDisplay(bool on);
	void lcdSetCursor(bool on);
	void lcdSetCursorBlink(bool on);

	void lcdPuts(const char* string);
	void lcdPrintf(const char* string, ...);

	void lcdShift(int dir);

	void lcdCreateCustomChar(int pos, uint8_t byte[8]);
	void lcdPrintCustomChar(int pos);

	void lcdTest(LCDDriver *pLCDDriver);

	void Lock();
	void Unlock();
};

