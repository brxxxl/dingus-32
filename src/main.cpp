#include <customCharacters.h>
#include <tasks.h>

#ifndef DEBUG_SKIP_CONNECTION
// #define DEBUG_SKIP_CONNECTION
#endif // DEBUG_SKIP_CONNECTION

int modeCount = 1; // Number of modes - 1

// variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;
unsigned long last_button_time = 0;

void IRAM_ATTR buttonPressed()
{
	button_time = millis();
	if (button_time - last_button_time > 200)
	{
		dataToDisplay.forceNextIteration();
		if (button1.mode < modeCount)
		{
			button1.mode++;
		}
		else
		{
			button1.mode = 0;
		}
		last_button_time = button_time;
	}
}

void setButtonInterrupts()
{
	pinMode(button1.pin, INPUT_PULLUP);
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

	pinMode(15, OUTPUT); // LED for debugging

	mainDisplayRoutine.init();
	mainDisplayRoutine.addTask(dataToDisplay);
	dataToDisplay.enable();
}

void loop()
{
	mainDisplayRoutine.execute();

	float tempRPM = myELM327.rpm();

	if (myELM327.nb_rx_state == ELM_SUCCESS)
	{
		rpm = (uint32_t)tempRPM;
		Serial.print("RPM: ");
		Serial.println(rpm);
	}
	else if (myELM327.nb_rx_state != ELM_GETTING_MSG)
	{
		myELM327.printError();
	}
}