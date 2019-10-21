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

// message format
typedef struct {
   char topic[10];
   char type[10];
   char action[32];
} mqtt_msg_struct;

// queue parameters
#define UART_QUEUE_LENGTH 16
#define UART_QUEUE_WIDTH sizeof(mqtt_msg_struct) // number of characters allowed

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
int sendDebugMsg_MqttQueue(char* topic, char* type, char* action);
int readMsg_MqttQueue(char* topic, char* type, char* action);


#endif /* SENSOR_QUEUE_H_ */
