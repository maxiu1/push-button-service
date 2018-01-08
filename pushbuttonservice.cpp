
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h> // open()
#include <unistd.h> // read()
#include <sys/time.h> // gettimeofday(...)

#include "raspi.h"
#include "pushbuttonservice.h"


#ifdef RASPI
#include <pigpio.h>
#endif

PushButtonService* obj;

PushButtonService::PushButtonService()
{
	obj = this;
#ifdef RASPI
	if (gpioInitialise()<0){
		printf("Cannot initialize the pigpio library\n");
	}
#endif

	prev = new Button(PIN_PREV);
	pause = new Button(PIN_PAUSE);
	play = new Button(PIN_PLAY);
	next = new Button(PIN_NEXT);
}

int PushButtonService::run()
{
	while(1){

		prev->loop();
		pause->loop();
		play->loop();
		next->loop();

		if(prev->pressedEvent()){
			printf("prev\n");
			system("mpc prev");
		}
		if(pause->pressedEvent()){
			printf("pause\n");
			system("mpc pause");
		}
		if(play->pressedEvent()){
			printf("play\n");
			system("mpc play");
		}
		if(next->pressedEvent()){
			printf("next\n");
			system("mpc next");
		}


		if(prev->holdEvent()){
			printf("prev hold\n");
		}
		if(pause->holdEvent()){
			printf("pause hold\n");
		}
		if(play->holdEvent()){
			printf("play hold\n");
		}
		if(next->holdEvent()){
			printf("next hold\n");
		}

		usleep(5e3); // 5ms
	}
}

