#include "scheduler.h"
#include "as5600.h"
#include "test.h"
#include <stdio.h>
#include <string.h>

#define MAX_TASKS 10
extern volatile uint8_t tim2_flag;

static SchedulerTask tasks[MAX_TASKS];

//sets each active flag to 0, or not busy
void scheduler_init(void)
{
	for(int i = 0; i< MAX_TASKS; i++){
		tasks[i].active = 0;
	}
}

int  scheduler_add(TaskFunction func, uint32_t interval_ms)
{
	//go through each available task until not active
	for(int i = 0; i < MAX_TASKS; i++){
		if(!tasks[i].active){
			tasks[i].func 		= func;
			tasks[i].interval 	= interval_ms;
			tasks[i].counter 	= 0;
			tasks[i].active  	= 1;
		}
	}
	return -1;
}

//ExecutionLoop that checks every tim2 tick what function to execute.
//
void scheduler_start(void){
	while(1){
		if(!tim2_flag) continue;
		tim2_flag = 0;

		for(int i = 0; i < MAX_TASKS; i++){
			if(!tasks[i].active) continue;
			tasks[i].counter++;
			if(tasks[i].counter >= tasks[i].interval){
				tasks[i].counter = 0;
				tasks[i].func();
			}
		}
	}
}
