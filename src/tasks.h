#include <facilities.h>

Scheduler mainDisplayRoutine;
bool ledState = LOW;

void dataToDisplayCallbackFunction(button button1); // Forward declaration
void dataToDisplayCallback();						// Forward declaration

void dataToDisplayCallbackFunction(button button1)
{
	ledState = HIGH * (ledState == LOW) + LOW * (ledState == HIGH);
	digitalWrite(15, ledState); // Blinking LED for debugging

	switch (button1.mode)
	{
	case 0:
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("RPM: 0");
		break;
	case 1:
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Km/h: 1");
		break;
	}
}

void dataToDisplayCallback()
{
	dataToDisplayCallbackFunction(button1);
}

Task dataToDisplay(TASK_MILLISECOND * 500, TASK_FOREVER, &dataToDisplayCallback);