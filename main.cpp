#include "Thread.h"
#include "mbed.h"
#include "mbed_rtx_conf.h"

// main() runs in its own thread in the OS
int main()
{   
    Thread* red_led_thread = new Thread(osPriorityNormal, OS_STACK_SIZE, nullptr, "Red LED Thread");
    
    while (true);
}

