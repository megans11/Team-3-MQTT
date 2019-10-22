/*
 * test_timer.c
 *
 *  Created on: Oct 20, 2019
 *      Author: lukeb
 */

#include "test_timer.h"


/*
 * This callback sends the time since last ISR call in ms to queue 1
 */
void testTimerCallback(Timer_Handle myHandle) {
    sendMsg_MqttQueue("/cc32xx/Debug", "Test", "Hello World!");
}

int init_testTimer() {

     Timer_init();

     // init timer
     Timer_Params_init(&test_params);
     test_params.period = MOTOR_TIMER_PERIOD;
     test_params.periodUnits = Timer_PERIOD_US;
     test_params.timerMode = Timer_CONTINUOUS_CALLBACK;
     test_params.timerCallback = testTimerCallback;

     // start timer
     test_timer = Timer_open(TEST_TIMER, &test_params);

     if (test_timer == NULL) {
         /* Failed to initialized timer */
         errorRoutine(0);
         return TIMER_FAILURE;
     }

     if (Timer_start(test_timer) == Timer_STATUS_ERROR) {
         /* Failed to start timer */
         errorRoutine(0);
         return TIMER_FAILURE;
     }

     return TIMER_SUCCESS;
}

