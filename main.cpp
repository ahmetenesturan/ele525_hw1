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

// main() runs in its own thread in the OS
int main()
{   
    Thread* red_led_thread = new Thread(osPriorityNormal, 2048, nullptr, "Red LED Thread");
    //Thread* blue_led_thread = new Thread(osPriorityNormal, 2048, nullptr, "Blue LED Thread");
    Thread* blue_led_thread = new Thread(osPriorityHigh, 2048, nullptr, "Blue LED Thread");
    red_led_thread->start(&red_led_toggle);
    blue_led_thread->start(&blue_led_toggle);

    thread_sleep_for(5000);
    mbed_stats_thread_t* thread_stats = new mbed_stats_thread_t[MAX_THREAD_STATS];
    int count = mbed_stats_thread_get_each(thread_stats, MAX_THREAD_STATS);

    for(int i = 0; i < count; i++)
    {
        printf("ID:%d\nName:%s\nPriority:%d\nState:%d\nStack Size:%d\nStack Space:%d\n", thread_stats[i].id, thread_stats[i].name, thread_stats[i].priority, thread_stats[i].state, thread_stats[i].stack_size, thread_stats[i].stack_space);

    }
    //printf("ID:%d\nName:%s\nPriority:%d\nState:%d\nStack Size:%d\nStack Space:%d\n", thread_stats->id, thread_stats->name, thread_stats->priority, thread_stats->state, thread_stats->stack_size, thread_stats->stack_space);


    red_led_thread->terminate();
    blue_led_thread->terminate();
    while (true);
}

void red_led_toggle()
{
    while(true)
    {
    //printf("\nRed LED On\n");
    wait_us(WAIT_TIME_US);
    //printf("\nRed LED Off\n");
    wait_us(WAIT_TIME_US);  
    }
}

void blue_led_toggle()
{
    while(true)
    {
    //printf("\nBlue LED On\n");
    wait_us(WAIT_TIME_US);
    //printf("\nBlue LED Off\n");
    wait_us(WAIT_TIME_US);  
    //thread_sleep_for(3000);
    }
}