/* 
 * *****************************************************************************
 *                        Module  Definition                                   *
 * *****************************************************************************
 * File         :   csma.h
 * Author       :   Hassan Elsaied
 * Data Memory  :   total byte used 0 Byte  
 * Program Space:   under upgrade
 * Version      :   Mega2v241022
 * Start Data   :   24-10-2022  20:00:00
 * End Data     :   24-10-2022  23:48:00
 * Work Time    :   1-hour
 * Comments     :   no comment
 *  
 */
#ifndef CSMA_H
#define	CSMA_H

#include "../mega.h"
#if defined CSMA_MODULE
#if CSMA_MODULE

/*
 *****************************************************************
 *                    usart check                                *
 * ***************************************************************
 */
#ifndef    USART_MODULE
#error    CSMA Module Must be used UART_MODULE
#elif      USART_MODULE == 0
#error     CSMA Module Must be used UART_MODULE 
#endif

/*
 *****************************************************************
 *                    device  type                                *
 * ***************************************************************
 */

#define  CSMA_MASTER  (0)
#define  CSMA_SLAVE   (1)
#ifndef  CSMA_DEVICE_TYPE
#define  CSMA_DEVICE_TYPE   CSMA_MASTER
#endif


#endif
#endif
#endif /*CSMA_H*/















