/*
 *  ======== message_control_thread.c ========
 */

/* Board Header file */
#include "test_thread.h"

/*
 *  ======== mainThread ========
 */
void *testThread(void *arg0)
{
    char msg_buffer[32];

    // Initiate for tests
    if (create_MqttQueue() != CREATE_QUEUE_SUCCESS) {
        while (1) {} // failed
    }

    init_testTimer();

    while (1) {
        readMsg_MqttQueue(msg_buffer);
        usleep(100);
    }
}
