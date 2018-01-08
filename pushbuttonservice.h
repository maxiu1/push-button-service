#ifndef PUSHBUTTONSERVICE_H
#define PUSHBUTTONSERVICE_H

/**
 * @brief The PushButtonService class
 *
 * This application is ment to run on a audio player
 * based on RuneAudio (Arch Linux).
 *
 * 4 push buttons are attached to the GPIO expansion header
 *
 * This service reads the push buttons and calls the mpd client mpc
 * with different parameters to controll the playback.
 */

#include <stdint.h>
#include "button.h"

class PushButtonService
{
public:
	PushButtonService();
	int run();

	enum Pins {PIN_PREV=18, PIN_PAUSE=23, PIN_PLAY=24, PIN_NEXT=25}; // MCU GPIO Pin-Nr ( != pinheader pin number)

	Button* prev;
	Button* pause;
	Button* play;
	Button* next;
};

void onPinChange_prev(int gpio, int level, uint32_t tick, void* data);
void onPinChange_pause(int gpio, int level, uint32_t tick, void* data);
void onPinChange_play(int gpio, int level, uint32_t tick, void* data);
void onPinChange_next(int gpio, int level, uint32_t tick, void* data);


#endif // PUSHBUTTONSERVICE_H
