/*
    FreeRTOS V6.1.0 - Copyright (C) 2010 Real Time Engineers Ltd.

    This file is part of the FreeRTOS distribution.

    This is example #5 from the book Using the FreeRTOS Real Time Kernel - A Practical Guide

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public 
    License and the FreeRTOS license exception along with FreeRTOS; if not it 
    can be viewed here: http://www.freertos.org/a00114.html and also obtained 
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/* System includes */
#include <stdio.h>
#include <stdint.h>


/* CMSIS / hardware includes */
#include "system_stm32f4xx.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "debug.h"

/* Demo includes. */
#include "basic_io.h"

/* The task function. */
void vTaskFunction(void *pvParameters);

/* Define the strings that will be passed in as the task parameters.  These are
defined const and off the stack to ensure they remain valid when the tasks are
executing. */
const char *pcTextForTask1 = "Task 1 is running\r\n";
const char *pcTextForTask2 = "Task 2 is running\r\n";

/*-----------------------------------------------------------*/

int main(void)
{
	/* System Initialization. */
	SystemInit();
	SystemCoreClockUpdate();
	// Create the debug task & print example number and system core clock.
	vDebugInit(5);

	/* Create the first task at priority 1... */
	xTaskCreate(vTaskFunction, (const signed char * const)"Task 1", 240, (void*)pcTextForTask1, 1, NULL);

	/* ... and the second task at priority 2.  The priority is the second to
	last parameter. */
	xTaskCreate(vTaskFunction, (const signed char * const)"Task 2", 240, (void*)pcTextForTask2, 2, NULL);

	/* Start the scheduler so our tasks start executing. */
	vTaskStartScheduler();	
	
	/* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
	while(1);
}
/*-----------------------------------------------------------*/

void vTaskFunction(void *pvParameters)
{
	(void)pvParameters;
	char *pcTaskName;
	portTickType xLastWakeTime;

	/* The string to print out is passed in via the parameter.  Cast this to a
	character pointer. */
	pcTaskName = (char *) pvParameters;

	/* The xLastWakeTime variable needs to be initialized with the current tick
	count.  Note that this is the only time we access this variable.  From this
	point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
	API function. */
	xLastWakeTime = xTaskGetTickCount();

	/* As per most tasks, this task is implemented in an infinite loop. */
	while(1)
	{
		/* Print out the name of this task. */
		vPrintString(pcTaskName);

		/* We want this task to execute exactly every 250 milliseconds.  As per
		the vTaskDelay() function, time is measured in ticks, and the
		portTICK_RATE_MS constant is used to convert this to milliseconds.
		xLastWakeTime is automatically updated within vTaskDelayUntil() so does not
		have to be updated by this task code. */
		vTaskDelayUntil(&xLastWakeTime, (250 / portTICK_RATE_MS));
	}
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook(void)
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining - and
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. */
	while(1);
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
	(void)pxTask;
	(void)pcTaskName;
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation and will only be performed if configCHECK_FOR_STACK_OVERFLOW
	is set to either 1 or 2 in FreeRTOSConfig.h. */
	while(1);
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook(void)
{
	/* This example does not use the idle hook to perform any processing.  The
	idle hook will only be called if configUSE_IDLE_HOOK is set to 1 in 
	FreeRTOSConfig.h. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook(void)
{
	/* This example does not use the tick hook to perform any processing.   The
	tick hook will only be called if configUSE_TICK_HOOK is set to 1 in
	FreeRTOSConfig.h. */
}
