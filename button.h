#ifndef BUTTON_H
#define BUTTON_H

#include "eventtime.h"

class Button
{
public:
	Button(int pinNr);
	void loop(); // calls resetAllEvents() and sets new events afterwards

	// returns true, if the button was pressed and released within 1s
	bool pressedEvent();

	// returns true, if the button was pressed and released within 1s
	bool holdEvent();

	bool isPressed();

private:
	enum State{Pressed, Released};

	void resetPressedEdge();
	void resetReleasedEdge();

	void resetAllEvents(); // calls all resetXxxxEvent() functions
	int pinNr;              // The Arduino Pin number where the button is connected
	bool pressedEdge;      // Is true when a rising edge on a button occured in the past, and is reset by resetPressedEvent()
	bool releasedEdge;      // Is true when a rising edge on a button occured in the past, and is reset by resetPressedEvent()

	State state;			// current state
	State oldState;          // old State of Button after loop()
	EventTime tPressed;	// time of the last transition from released to pressed
	EventTime pressedDuration;	// last duration between pushed and released events, updated on released event
};

#endif // BUTTON_H
