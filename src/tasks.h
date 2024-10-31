#include <facilities.h>

Scheduler mainDisplayRoutine;

int rpm = 0;
int kph = 0;
float torque = 0;
float throttle = 0;

void dataToDisplayCallback();						// Forward declaration
void dataToDisplayCallbackFunction(button button1); // Forward declaration

void dataToDisplayCallbackFunction(button button1)
{
	switch (button1.mode)
	{
	case 0:
		printNewToLine("KM/h:           ", 0, lcd, false);
		lcd.setCursor(6, 0);
		lcd.print(kph);

		printNewToLine("RPM:            ", 1, lcd, false);
		lcd.setCursor(5, 1);
		lcd.print(rpm);
		break;
	case 1:
		printNewToLine("Torq.:          ", 0, lcd, false);
		lcd.setCursor(7, 0);
		lcd.print(torque);

		printNewToLine("Fuel R:         ", 1, lcd, false);
		lcd.setCursor(8, 1);
		lcd.print(throttle);
		break;
	}
}

void dataToDisplayCallback()
{
	dataToDisplayCallbackFunction(button1);
}

Task dataToDisplay(TASK_MILLISECOND * 500, TASK_FOREVER, &dataToDisplayCallback);