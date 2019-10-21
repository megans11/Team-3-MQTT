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
    char topic[10];
    char type[10];
    char action[32];

    // Initiate for tests (mqttQueue)
    if (create_MqttQueue() != CREATE_QUEUE_SUCCESS) {
        while (1) {} // failed
    }

    init_testTimer();

    while (1) {
        readMsg_MqttQueue(topic, type, action);
        usleep(100);
    }
}
