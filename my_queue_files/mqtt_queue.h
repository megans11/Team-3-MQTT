/*
 * sensor_queue.h
 *
 *  Created on: Sep 8, 2019
 *      Author: Luke_
 */


// TODO: update for message control

#ifndef MESSAGE_QUEUE_H_
#define MESSAGE_QUEUE_H_

#include <FreeRTOS.h>
#include <queue.h>
#include "debug.h"

// queue parameters
#define UART_QUEUE_LENGTH 16
#define UART_QUEUE_WIDTH 33 // number of characters allowed

// Return value definitions
#define CREATE_QUEUE_FAILURE -1
#define CREATE_QUEUE_SUCCESS 0

#define QUEUE_FULL -1
#define SENT_SUCCESS 0

#define READ_FAILURE -1
#define READ_SUCCESS 0

// message struct types
#define MSG_TYPE_DEBUG 0

// Collection of all queue handles in project
QueueHandle_t mqttQueue;

// Public queue functions
int create_MqttQueue();
int sendDebugMsg_MqttQueue(char* debug_msg);
int readMsg_MqttQueue(char *debug_msg);


#endif /* SENSOR_QUEUE_H_ */
