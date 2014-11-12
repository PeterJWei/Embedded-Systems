#include <arm/timer.h>
#include <arm/reg.h>

extern volatile unsigned long global_timer;


void initializeTimer() {
//	timer=0;
}

void addTimer(int time) {
//	timer+=time;
}

unsigned int get_clock() {
    return global_timer;
}
