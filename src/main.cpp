#include "BluetoothSerial.h"
#include "BluetoothSerial.cpp"
#include "ELMduino.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include <HardwareSerial.h>
#include "facilities.h"
#include "customCharacters.h"

#ifndef DEBUG_SKIP_CONNECTION
// #define DEBUG_SKIP_CONNECTION
#endif // DEBUG_SKIP_CONNECTION

uint8_t mac[6] = {0x1C, 0xA1, 0x35, 0x69, 0x8D, 0xC5};

button button1 = {19, false};

int modeCount = 1; // Number of modes - 1
float rpm = 0;
float kph = 0;

void IRAM_ATTR buttonPressed()
{
	if (button1.mode < modeCount)
	{
		button1.mode++;
	}
	else
	{
		button1.mode = 0;
	}
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
	Serial.println("Starting loop...");
	Serial.println("\n");
	Serial.println("\n");
	Serial.println("\n");
}

void loop()
{
	float tempRPM = myELM327.rpm();

	if (myELM327.nb_rx_state == ELM_SUCCESS)
	{
		rpm = (uint32_t)tempRPM;
		Serial.print("RPM: ");
		Serial.println(rpm);
		printNewToLine("RPM: ", 0, lcd, true);
		lcd.setCursor(5, 0);
		lcd.print(tempRPM);
	}
	else if (myELM327.nb_rx_state != ELM_GETTING_MSG)
	{
		myELM327.printError();
		while (1)
			;
	}
}