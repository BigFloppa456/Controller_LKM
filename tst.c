

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <stdint.h>
#include "ioctl_prac.h"

//Returns the number of axes on the controller.
// uint8_t get_axis_count(int js){
//     uint8_t axesNum;
//     if (ioctl(js, JSIOCGAXES, &axesNum)  == -1){
//         return 0;
//     }
//     return axesNum;
// }

// uint8_t get_button_count(int js){
//     uint8_t buttons;
//     if (ioctl(js, JSIOCGBUTTONS, &buttons)  == -1){
//         return 0;
//     }
//     return buttons;
// }


int main() {
	char* deviceRoute = "/dev/input/js2";
    int js = open(deviceRoute, O_RDONLY);

	if (js == -1)
	{
		perror("Couldn't open joystick\n");
        return -1;
	}


    while(true){
        usleep(100000);

        struct js_event event;

        int bytesRead = read(js, &event, sizeof(event));
        if (bytesRead <= 0) return -1;

        if(event.type == JS_EVENT_INIT){
            printf("Initialized. Event type: %d\n", event.type);
        }
        if (event.type == JS_EVENT_BUTTON ) {
			printf("Button %d's value is: %d\n", event.number, event.value);
            struct joyinp send = {event.number, event.type, event.value};
            ioctl(js,READVALUE,&send);
        }
		if (event.type == JS_EVENT_AXIS ) {
			printf("Axis %d's value is: %d\n", event.number, event.value);
            struct joyinp send = {event.number, event.type, event.value};
            ioctl(js,READVALUE,&send);
		}
        
    }

    struct joyinp send = {4, JS_EVENT_BUTTON, 1};
    ioctl(js,READVALUE,&send);
    
    close(js);
    printf("---  |\nend  |\n---  |\n");

	return 0;
    }

