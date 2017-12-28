// implement the delay function in the dos.h library to work with gcc
// @author: parth_shel
// @version: v:1.0 - Dec. 28, 2017

//include headers
#include <time.h>

//delay function
void delay(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void delay(int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
