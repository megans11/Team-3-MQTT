/*
 * testThread.h
 *
 *  Created on: Sep 20, 2019
 *      Author: Luke_
 */

#ifndef TEST_THREAD_H_
#define TEST_THREAD_H_

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

#include "Board.h"
#include "my_queue_files/mqtt_queue.h"
#include "test_timer.h"

void *testThread(void *arg0);

#endif /* TEST_THREAD_H_ */
