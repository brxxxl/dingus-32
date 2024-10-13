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

byte carSpeed[] = {0x00,
				   0x00,
				   0x00,
				   0x1C,
				   0x1F,
				   0x1F,
				   0x0A,
				   0x00};

byte clockRpm[] = {0x00,
				   0x0E,
				   0x13,
				   0x15,
				   0x11,
				   0x0E,
				   0x00,
				   0x00};

byte celsius[] = {0x18,
				  0x18,
				  0x00,
				  0x07,
				  0x08,
				  0x08,
				  0x08,
				  0x07};

byte injectionNozzle[] = {0x00,
						  0x1F,
						  0x0E,
						  0x0E,
						  0x00,
						  0x04,
						  0x02,
						  0x01};

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