#pragma once
#include "main.h"
#include <stdint.h>

//create a function pointer type
typedef void(*TaskFunction)(void);

typedef struct {
	TaskFunction func;	//points to the function to run
	uint32_t interval;	//how many ms interval
	uint32_t  counter;	//keeps track of elapsed ms
	uint32_t   active; 	//keeps track if function assigned to slot
} SchedulerTask;

void scheduler_init(void);
int  scheduler_add(TaskFunction func, uint32_t interval_ms);
void scheduler_start(void);
