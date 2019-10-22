/*
 * test_timer.h
 *
 *  Created on: Oct 20, 2019
 *      Author: lukeb
 */

#ifndef TEST_TIMER_H_
#define TEST_TIMER_H_

#include <ti/drivers/Timer.h>
#include "Board.h"
#include "debug.h"
#include "my_queue_files/mqtt_queue.h"


#define MOTOR_TIMER_PERIOD 80000 // .08s
#define TIMER_FAILURE -1
#define TIMER_SUCCESS 0

Timer_Handle test_timer;
Timer_Params test_params;

int init_testTimer();



#endif /* TEST_TIMER_H_ */
