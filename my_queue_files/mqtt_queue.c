/*
 * sensor_queue.c
 *
 *  Created on: Sep 8, 2019
 *      Author: Luke Beckwith
 */
#include <my_queue_files/mqtt_queue.h>


/**
 * Wrapper for createQueue to create predefined queue1
 */
int create_MqttQueue(){
    mqttQueue = xQueueCreate(UART_QUEUE_LENGTH, UART_QUEUE_WIDTH);

    if(mqttQueue != NULL)
        return CREATE_QUEUE_SUCCESS;
    else
        errorRoutine(0);

    return CREATE_QUEUE_FAILURE;
}

/**
 * Sends signed value - use when called from ISR
 * Returns FreeRTOS return value
 */
int sendDebugMsg_MqttQueue(char* topic, char* type, char* action){

    // Debug before sending within ISR/callback
    mqtt_msg_struct msg;
    memset(msg.topic,'\0',sizeof(msg.topic));
    memset(msg.type,'\0',sizeof(msg.type));
    memset(msg.action,'\0',sizeof(msg.action));

    strncpy(msg.topic, topic, strlen(topic));
    strncpy(msg.type, type, strlen(type));
    strncpy(msg.action, action, strlen(action));
    msg.msg_type = PUBLISH_MESSAGE;

    BaseType_t ret_val = xQueueSendFromISR(mqttQueue, (const void*) &msg, pdFALSE);

    // Debug after sending within ISR/callback

    if (ret_val == errQUEUE_FULL)
        return QUEUE_FULL;
    else
        return SENT_SUCCESS;

}

int sendCmdMsg_MqttQueue(int type){

    // Debug before sending within ISR/callback
    mqtt_msg_struct msg;
    msg.msg_type = type;

    BaseType_t ret_val = xQueueSendFromISR(mqttQueue, (const void*) &msg, pdFALSE);

    // Debug after sending within ISR/callback

    if (ret_val == errQUEUE_FULL)
        return QUEUE_FULL;
    else
        return SENT_SUCCESS;

}

/**
 * Blocking read from Queue 1. Fills correct buffer, return type specifies type received.
 */
int readMsg_MqttQueue(mqtt_msg_struct *msg_buffer){
    // Debug before receiving from queue in ISR
//    dbgOutputLoc(0);
    int read_status = xQueueReceive(mqttQueue, (void*) msg_buffer, portMAX_DELAY);
//    dbgOutputLoc(0);

    // Block until message, check if valid
    if (read_status == pdTRUE) {
        // For now:
//        strncpy(topic, msg_buffer.topic, strlen(msg_buffer.topic));
//        strncpy(type, msg_buffer.type, strlen(msg_buffer.type));
//        strncpy(action, msg_buffer.action, strlen(msg_buffer.action));

        // Fill correct buffer
//        switch (msg_buffer[0]){
//            case MSG_TYPE_DEBUG:
//                msg_ptr = &msg_buffer[1];
//                memcpy(debug_buffer, msg_ptr, strlen(msg_ptr));
//                debug_buffer[strlen(msg_ptr)] = '\0';
//                return MSG_TYPE_DEBUG;
//
//            default:
//                errorRoutine(0);
        return READ_SUCCESS;

    }
    return READ_FAILURE;
}

