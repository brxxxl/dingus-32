#include <Arduino.h>

byte Battery1Char[] = {0x0e,  //  ■■■
					   0x1b,  // ■■ ■■
					   0x11,  // ■   ■
					   0x11,  // ■   ■
					   0x11,  // ■   ■
					   0x11,  // ■   ■
					   0x11,  // ■   ■
					   0x1f}; // ■■■■■

byte Battery2Char[] = {0x0e,  //  ■■■
					   0x1b,  // ■■ ■■
					   0x11,  // ■   ■
					   0x11,  // ■   ■
					   0x11,  // ■   ■
					   0x11,  // ■■■■■
					   0x1f,  // ■■■■■
					   0x1f}; // ■■■■■

byte Battery3Char[] = {0x0e,  //  ■■■
					   0x1b,  // ■■ ■■
					   0x11,  // ■   ■
					   0x1f,  // ■■■■■
					   0x1f,  // ■■■■■
					   0x1f,  // ■■■■■
					   0x1f,  // ■■■■■
					   0x1f}; // ■■■■■

byte Battery4Char[] = {0x0e,  //  ■■■
					   0x1f,  // ■■■■■
					   0x1f,  // ■■■■■
					   0x1f,  // ■■■■■
					   0x1f,  // ■■■■■
					   0x1f,  // ■■■■■
					   0x1f,  // ■■■■■
					   0x1f}; // ■■■■■

/*
	lcd.createChar(0, Battery1Char);
	lcd.createChar(1, Battery2Char);
	lcd.createChar(2, Battery3Char);
	lcd.createChar(3, Battery4Char);

	for (int i = 0; i < 4; i++)
	{
		lcd.setCursor(15, 1);
		lcd.write(byte(i));
		delay(500);
	}
*/