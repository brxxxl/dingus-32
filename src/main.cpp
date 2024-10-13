#include <customCharacters.h>
#include <tasks.h>

#ifndef DEBUG_SKIP_CONNECTION
// #define DEBUG_SKIP_CONNECTION
#endif // DEBUG_SKIP_CONNECTION

int modeCount = 1; // Number of modes - 1
volatile float tempRPM = 0;
volatile float tempKPH = 0;
volatile float tempOilTemp = 0;
volatile float tempFuelRate = 0;
int obd_state_mode = 0;
int obd_state_max = 3; // Number of states - 1

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
	printNewToLine("Connecting to   ", 0, lcd, true);
	printNewToLine("ELM327          ", 1, lcd, false);
	blinkingDotsAnimation(6, 1, lcd);

	attemptToConnect(mac); // Connect to the OBD scanner

	setButtonInterrupts();

	mainDisplayRoutine.init();
	mainDisplayRoutine.addTask(dataToDisplay);
	dataToDisplay.enable();
	lcd.setCursor(0, 0);
	lcd.print(CLEAR_STRING);
	lcd.setCursor(0, 1);
	lcd.print(CLEAR_STRING);
}

void loop()
{
	mainDisplayRoutine.execute();

	int skipMode = button1.mode;

	switch (obd_state_mode)
	{
	case 0:
		if (skipMode != 0)
		{
			break;
		}
		tempKPH = myELM327.kph();
		if (myELM327.nb_rx_state == ELM_SUCCESS)
		{
			kph = (uint32_t)tempKPH;
		}
		else if (myELM327.nb_rx_state != ELM_GETTING_MSG)
		{
			myELM327.printError();
		}
		break;
	case 1:
		if (skipMode != 0)
		{
			break;
		}
		tempRPM = myELM327.rpm();
		if (myELM327.nb_rx_state == ELM_SUCCESS)
		{
			rpm = (uint32_t)tempRPM;
		}
		else if (myELM327.nb_rx_state != ELM_GETTING_MSG)
		{
			myELM327.printError();
		}
		break;
	case 2:
		if (skipMode != 1)
		{
			break;
		}
		tempOilTemp = myELM327.oilTemp();
		if (myELM327.nb_rx_state == ELM_SUCCESS)
		{
			oilTemp = (uint32_t)tempOilTemp;
		}
		else if (myELM327.nb_rx_state != ELM_GETTING_MSG)
		{
			myELM327.printError();
		}
		break;
	case 3:
		if (skipMode != 1)
		{
			break;
		}
		tempFuelRate = myELM327.fuelRate();
		if (myELM327.nb_rx_state == ELM_SUCCESS)
		{
			fuelRate = (uint32_t)tempFuelRate;
		}
		else if (myELM327.nb_rx_state != ELM_GETTING_MSG)
		{
			myELM327.printError();
		}
		break;
	}
	obd_state_mode++;
	if (obd_state_mode > obd_state_max)
	{
		obd_state_mode = 0;
	}
}