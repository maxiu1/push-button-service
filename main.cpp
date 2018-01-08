#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pushbuttonservice.h"

void printUsage()
{
	printf("push-button-service\n");
	printf("  no parameters\n");
	printf("  \n");
	printf("  This progamm makes calls to the daemon mpd\n");
	printf("      mpd [prev, pause, play, next]\n");
}


int main(int argc, char** argv)
{
	PushButtonService app;

	for(int i=1; i<argc; i++){
//		if(strcmp(argv[i], "--verbose") == 0 ||
//				strcmp(argv[i], "-v") == 0){
//			app.verbose = true;
//		}else if(strcmp(argv[i], "--console-only") == 0 ||
//				 strcmp(argv[i], "-c") == 0){
//			app.consoleOnly = true;
//		}else
		if(strcmp(argv[i], "--help") == 0 ||
				 strcmp(argv[i], "-h") == 0 ){
			printUsage();
			exit(0);
		}
//		else if(argv[i][0] == '/'){
//			app.device = argv[i];
//		}else if(strcmp(argv[i], "-events") == 0 ||
//				 strcmp(argv[i], "-e") == 0){
//			app.printEvents = true;
//		}else if(strcmp(argv[i], "-raw") == 0 ||
//				 strcmp(argv[i], "-r") == 0){
//			app.rawOutput = true;
//		}
	}

	return app.run();
}
