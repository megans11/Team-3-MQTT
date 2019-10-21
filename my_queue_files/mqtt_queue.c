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
int sendDebugMsg_MqttQueue(char* debug_msg){

    // Debug before sending within ISR/callback
    char msg[UART_QUEUE_WIDTH];
    memset(msg,'\0',UART_QUEUE_WIDTH);
    strncpy(&msg[1], debug_msg, strlen(debug_msg));
    msg[0] = MSG_TYPE_DEBUG;

    BaseType_t ret_val = xQueueSendFromISR(mqttQueue, (const void*) msg, pdFALSE);

    // Debug after sending within ISR/callback

    if (ret_val == errQUEUE_FULL)
        return QUEUE_FULL;
    else
        return SENT_SUCCESS;

}

/**
 * Blocking read from Queue 1. Fills correct buffer, return type specifies type received.
 */
int readMsg_MqttQueue(char *debug_buffer){
    char msg_buffer[UART_QUEUE_WIDTH];
    char *msg_ptr;

    // Debug before receiving from queue in ISR
//    dbgOutputLoc(0);
    int read_status = xQueueReceive(mqttQueue, (void*) msg_buffer, portMAX_DELAY);
//    dbgOutputLoc(0);

    // Block until message, check if valid
    if (read_status == pdTRUE) {

        // Fill correct buffer
        switch (msg_buffer[0]){
            case MSG_TYPE_DEBUG:
                msg_ptr = &msg_buffer[1];
                memcpy(debug_buffer, msg_ptr, strlen(msg_ptr));
                debug_buffer[strlen(msg_ptr)] = '\0';
                return MSG_TYPE_DEBUG;

            default:
                errorRoutine(0);
        }
    }
    return READ_FAILURE;
}

