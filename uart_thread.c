/*
 * uart_thread.c
 *
 *  Created on: Oct 9, 2019
 *      Author: lukeb
 */

#include "uart_thread.h"

/*
 *  ======== uartThread ========
 */
void *uartThread(void *arg0)
{
    // turn usb uart
    createUartQueue();
    dbgUARTInit();

    // Command variables
    char msg[UART_QUEUE_WIDTH] = "\r\nUart thread opened\r\n\0";
    dbgUARTVal(msg);

    while (1) {
        // blocking read from queue
        readMsqFromUartQueue(msg);

        // write to UART
        dbgUARTVal(msg);
    }
}


