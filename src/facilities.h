#include <BluetoothSerial.h>
#include <BluetoothSerial.cpp>
#include <TaskScheduler.h>
#include <AsyncTCP.h>
#include <ELMduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HardwareSerial.h>

// #define DEBUG_SKIP_CONNECTION
#define CHAR_PROTOCOL 0
#define CLEAR_STRING "                "

uint8_t mac[6] = {0x24, 0x44, 0x8B, 0xC0, 0x2A, 0x53};

struct button
{
	const uint8_t pin;
	bool state;
	int mode;
};

typedef enum
{
	ENG_RPM,
	SPEED,
	TORQUE,
	THROTTLE
} obd_pid_states;
obd_pid_states obd_state = ENG_RPM;

button button1 = {19, false, 0};

LiquidCrystal_I2C lcd(0x27, 16, 2);
BluetoothSerial SerialBT;
ELM327 myELM327;

#define ELM_PORT SerialBT
#define DEBUG_PORT Serial

void restartESP()
{
	ESP.restart();
	abort();
}

void printNewToLine(String text, int line, LiquidCrystal_I2C lcd, bool clearOtherLine)
{
	if (clearOtherLine)
	{
		lcd.setCursor(0, 1 - line);
		lcd.print(CLEAR_STRING);
	}
	else
	{
		lcd.setCursor(0, line);
		lcd.print(CLEAR_STRING);
	}
	lcd.setCursor(0, line);
	lcd.print(text);
}

void printNewToLCD(String text, LiquidCrystal_I2C lcd)
{
	lcd.setCursor(0, 0);
	lcd.print(CLEAR_STRING);
	lcd.setCursor(0, 1);
	lcd.print(CLEAR_STRING);
	if (text.length() > 16)
	{
		printNewToLine(text.substring(0, 16), 0, lcd, true);
		printNewToLine(text.substring(16, text.length()), 1, lcd, false);
	}
	else
	{
		printNewToLine(text, 0, lcd, true);
	}
}

void blinkingDotsAnimation(int startColumn, int startRow, LiquidCrystal_I2C lcd)
{
	lcd.setCursor(startColumn, startRow);
	lcd.print("   ");
	delay(500);
	lcd.setCursor(startColumn, startRow);
	lcd.print(".");
	delay(500);
	lcd.print(".");
	delay(500);
	lcd.print(".");
	delay(500);
}

void attemptToConnect(uint8_t mac[6])
{
	if (!ELM_PORT.connect(mac))
	{
		DEBUG_PORT.println("Couldn't connect to OBD scanner - Phase 1");
		lcd.clear();
		printNewToLCD("Phase 1 - Failed", lcd);
		delay(1000);
#ifndef DEBUG_SKIP_CONNECTION
		restartESP();
#endif // DEBUG_SKIP_CONNECTION
	}
	else
	{
		DEBUG_PORT.println("Phase 1 - successful");
		lcd.clear();
		printNewToLine("Phase 1 -       ", 0, lcd, true);
		printNewToLine("Successful      ", 1, lcd, false);
		delay(500);
	}

	if (!myELM327.begin(ELM_PORT, true, 2000, (char)CHAR_PROTOCOL))
	{
		Serial.println("Couldn't connect to OBD scanner - Phase 2");
		lcd.clear();
		printNewToLCD("Phase 2 - Failed", lcd);
		delay(1000);
#ifndef DEBUG_SKIP_CONNECTION
		restartESP();
#endif // DEBUG_SKIP_CONNECTION
	}
	else
	{
		DEBUG_PORT.println("Phase 2 - successful");
		lcd.clear();
		printNewToLine("Phase 2 -       ", 0, lcd, true);
		printNewToLine("Successful      ", 1, lcd, false);
		delay(500);
		printNewToLine("Connected to    ", 0, lcd, true);
		printNewToLine("ELM327          ", 1, lcd, false);
	}
}

void startDevices()
{
#ifdef DEBUG_PORT
	DEBUG_PORT.begin(38400);
#endif // DEBUG_PORT
	ELM_PORT.begin("ArduHUD", true);
	ELM_PORT.setPin("1234");
	lcd.init();
	lcd.backlight();
	lcd.clear();
	lcd.setContrast(150);

	lcd.load_custom_character(0, carSpeed);
	lcd.load_custom_character(1, clockRpm);
	lcd.load_custom_character(2, celsius);
	lcd.load_custom_character(3, injectionNozzle);
}