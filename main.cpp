#include "Thread.h"
#include "cmsis_os2.h"
#include "mbed.h"
#include "mbed_rtx_conf.h"
#include "mbed_thread.h"
#include "mbed_stats.h"
#include <cstdio>

#define WAIT_TIME_US 5e5
#define MAX_THREAD_STATS 8

#if !defined(MBED_THREAD_STATS_ENABLED)
#error "Thread statistics not enabled"
#endif

void red_led_toggle();
void blue_led_toggle();
void green_led_toggle();
void polling_switch();

DigitalIn switchButton(BUTTON1);

// main() runs in its own thread in the OS
int main()
{   
    Thread* red_led_thread = new Thread(osPriorityNormal, 2048, nullptr, "Red LED Thread");
    Thread* blue_led_thread = new Thread(osPriorityNormal, 2048, nullptr, "Blue LED Thread");
    //Thread* blue_led_thread = new Thread(osPriorityHigh, 2048, nullptr, "Blue LED Thread");
    Thread* green_led_thread = new Thread(osPriorityNormal, 2048, nullptr, "Green LED Thread");
    Thread* polling_switch_thread = new Thread(osPriorityAboveNormal, 2048, nullptr, "Polling Switch Thread");
    red_led_thread->start(&red_led_toggle);
    blue_led_thread->start(&blue_led_toggle);
    green_led_thread->start(&green_led_toggle);
    polling_switch_thread->start(&polling_switch);
    
    /*
    thread_sleep_for(5000);
    
    mbed_stats_thread_t* thread_stats = new mbed_stats_thread_t[MAX_THREAD_STATS];
    int count = mbed_stats_thread_get_each(thread_stats, MAX_THREAD_STATS);

    for(int i = 0; i < count; i++)
    {
        printf("ID:%d\nName:%s\nPriority:%d\nState:%d\nStack Size:%d\nStack Space:%d\n\n\n\n", thread_stats[i].id, thread_stats[i].name, thread_stats[i].priority, thread_stats[i].state, thread_stats[i].stack_size, thread_stats[i].stack_space);

    }
    */

    while (true);
}

void red_led_toggle()
{
    while(true)
    {
    printf("\nRed LED On\n");
    printf("\nRed LED Off\n");
    thread_sleep_for(6000);
    }
}

void blue_led_toggle()
{
    while(true)
    {
    printf("\nBlue LED On\n");
    printf("\nBlue LED Off\n");
    thread_sleep_for(6000);
    }
}

void green_led_toggle()
{
    while(true)
    {
    printf("\nGreen LED On\n");
    printf("\nGreen LED Off\n");
    thread_sleep_for(6000);
    }
}

void polling_switch()
{
    while(true)
    {
        while(!switchButton)
        {
            printf("\nRed LED On\n");
            printf("\nRed LED Off\n");
            printf("\nBlue LED On\n");
            printf("\nBlue LED Off\n");
            printf("\nGreen LED On\n");
            printf("\nGreen LED Off\n");
            thread_sleep_for(40);
        }

        thread_sleep_for(100);
    }
}