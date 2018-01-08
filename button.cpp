#include "button.h"
#include <stdio.h>
#include "raspi.h"

#ifdef RASPI
#include <pigpio.h>
#endif


Button::Button(int pinNr)
{
	this->pinNr = pinNr;

#ifdef RASPI
	// activate pull-up
	gpioSetPullUpDown(pinNr, PI_PUD_UP);

	// set pins to input
	gpioSetMode(pinNr, PI_INPUT);
#endif


	pressedEdge=false;
	releasedEdge=false;
	oldState = Released;
	state = Released;
}

void Button::loop()
{
	// update button state:
	if(gpioRead(pinNr)==0){
		state = Pressed;
	}else{
		state = Released;
	}

	pressedEdge = false;
	releasedEdge = false;

	if(state != oldState){ // transition has happened
		if(state == Pressed){
			tPressed = EventTime::now();
			pressedEdge = true;
//			printf("Button Pressed Edge\n");
		}
		if(state == Released){
			releasedEdge = true;
			pressedDuration = EventTime::now()-tPressed;
//			printf("Button Released Edge, ");
//			printf("pressedDuration = ");
//			pressedDuration.println();
		}
	}

	oldState=state;
}

bool Button::pressedEvent()
{
	if(releasedEdge && (pressedDuration > EventTime(0, 30000)) && (pressedDuration < EventTime(1, 0))){
//		printf("Button Pressed Event\n");
		return true;
	}
	return false;
}

bool Button::holdEvent()
{
	if((state == Pressed) && ((EventTime::now()-tPressed) > EventTime(3,0))){
//		printf("Button Hold Event\n");
		return true;
	}
	return false;
}

bool Button::isPressed()
{
	return state == Pressed;
}
