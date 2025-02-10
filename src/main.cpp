#include <customCharacters.h>
#include <tasks.h>

#ifndef DEBUG_SKIP_CONNECTION
// #define DEBUG_SKIP_CONNECTION
#endif // DEBUG_SKIP_CONNECTION

int modeCount = 1; // Number of modes - 1
volatile int tempRPM = 0;
volatile int tempKPH = 0;
volatile int tempTorque = 0;
volatile int tempThrottle = 0;

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

	if (button1.mode == 0)
	{
		if (!((obd_state == ENG_RPM) || (obd_state == SPEED)))
		{
			obd_state = ENG_RPM;
		}
		
		switch (obd_state)
		{
		case ENG_RPM:
			tempRPM = myELM327.rpm();
			if (myELM327.nb_rx_state == ELM_SUCCESS)
			{
				rpm = tempRPM;
				obd_state = SPEED;
			}
			else if (myELM327.nb_rx_state != ELM_GETTING_MSG)
			{
				myELM327.printError();
				obd_state = SPEED;
			}
			break;
		case SPEED:
			tempKPH = myELM327.kph();
			if (myELM327.nb_rx_state == ELM_SUCCESS)
			{
				kph = tempKPH;
				obd_state = ENG_RPM;
			}
			else if (myELM327.nb_rx_state != ELM_GETTING_MSG)
			{
				myELM327.printError();
				obd_state = ENG_RPM;
			}
			break;
		}
	}

	if (button1.mode == 1)
	{
		if (!((obd_state == TORQUE) || (obd_state == THROTTLE)))
		{
			obd_state = TORQUE;
		}

		switch (obd_state)
		{
		case TORQUE:
			tempTorque = myELM327.torque();
			if (myELM327.nb_rx_state == ELM_SUCCESS)
			{
				torque = tempTorque;
				obd_state = THROTTLE;
			}
			else if (myELM327.nb_rx_state != ELM_GETTING_MSG)
			{
				myELM327.printError();
				obd_state = THROTTLE;
			}
			break;
		case THROTTLE:
			tempThrottle = myELM327.throttle();
			if (myELM327.nb_rx_state == ELM_SUCCESS)
			{
				throttle = tempThrottle;
				obd_state = TORQUE;
			}
			else if (myELM327.nb_rx_state != ELM_GETTING_MSG)
			{
				myELM327.printError();
				obd_state = TORQUE;
			}
			break;
		}
	}
}