#include <facilities.h>

Scheduler mainDisplayRoutine;

bool modeSwitch = false;

float rpm = 0;
float kph = 0;
float oilTemp = 0;
float fuelRate = 0;

void dataToDisplayCallback();						// Forward declaration
void dataToDisplayCallbackFunction(button button1); // Forward declaration

void dataToDisplayCallbackFunction(button button1)
{
	if (modeSwitch)
	{
		lcd.setCursor(0, 0);
		lcd.print(CLEAR_STRING);
		lcd.setCursor(0, 1);
		lcd.print(CLEAR_STRING);
		modeSwitch = false;
	}

	switch (button1.mode)
	{
	case 0:
		printNewToLine("KM/h:           ", 0, lcd, false);
		lcd.setCursor(6, 0);
		// lcd.write(0);
		// lcd.setCursor(2, 0);
		lcd.print(kph);

		printNewToLine("RPM:            ", 1, lcd, false);
		lcd.setCursor(5, 1);
		// lcd.setCursor(0, 1);
		// lcd.write(1);
		// lcd.setCursor(2, 1);
		lcd.print(rpm);
		break;
	case 1:
		printNewToLine("Oil T:          ", 0, lcd, false);
		lcd.setCursor(7, 0);
		// lcd.write(2);
		// lcd.setCursor(2, 0);
		lcd.print(oilTemp);

		printNewToLine("Fuel R:         ", 1, lcd, false);
		lcd.setCursor(8, 1);
		// lcd.setCursor(0, 1);
		// lcd.write(3);
		// lcd.setCursor(2, 1);
		lcd.print(fuelRate);
		break;
	}
}

void dataToDisplayCallback()
{
	dataToDisplayCallbackFunction(button1);
}

Task dataToDisplay(TASK_MILLISECOND * 500, TASK_FOREVER, &dataToDisplayCallback);