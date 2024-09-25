#include "BluetoothSerial.h"
#include "BluetoothSerial.cpp"
#include "ELMduino.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include <HardwareSerial.h>
#include "facilities.h"

#ifdef DEBUG_SKIP_CONNECTION
#undef DEBUG_SKIP_CONNECTION
#endif // DEBUG_SKIP_CONNECTION

uint8_t mac[6] = {0x1C, 0xA1, 0x35, 0x69, 0x8D, 0xC5};

typedef enum
{
	ENG_RPM,
	SPEED
} obd_pid_states;
obd_pid_states obd_state = ENG_RPM;

button button1 = {19, false};

int mode = 0;
int modeCount = 1; // Number of modes - 1
float rpm = 0;
float kph = 0;

void IRAM_ATTR buttonPressed()
{
	button1.state = true;
}

void setButtonInterrupts()
{
	pinMode(button1.pin, INPUT_PULLDOWN);
	attachInterrupt(button1.pin, buttonPressed, FALLING);
}

void setup()
{
	startDevices();
	DEBUG_PORT.println("Device started");
	DEBUG_PORT.println("Attempting to connect to ELM327...");
	printNewToLine("Connecting to", 0, lcd, true);
	printNewToLine("ELM327", 1, lcd, false);
	blinkingDotsAnimation(6, 1, lcd);
	attemptToConnect(mac); // Connect to the OBD scanner
	setButtonInterrupts();

	Serial.println("Connected to ELM327");
	delay(1000);
}

void loop()
{
	if (button1.state == true)
	{
		if (mode < modeCount)
		{
			mode++;
		}
		else
		{
			mode = 0;
		}
		button1.state = false;
	}

	switch (mode)
	{
	case 0:
	{
#ifndef DEBUG_SKIP_CONNECTION
		rpm = myELM327.rpm();
#endif // DEBUG_SKIP_CONNECTION
		printNewToLine("RPM: ", 0, lcd, true);
		lcd.setCursor(5, 0);
		lcd.print(rpm);
		break;
	}
	case 1:
	{
#ifndef DEBUG_SKIP_CONNECTION
		kph = myELM327.kph();
#endif // DEBUG_SKIP_CONNECTION
		printNewToLine("KPH: ", 0, lcd, true);
		lcd.setCursor(5, 0);
		lcd.print(kph);
		break;
	}
	}
	delay(300);
}