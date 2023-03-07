/* 
 * File:   AddressableDevice.c
 * Author: hp
 *
 * Created on March 2, 2023, 12:54 PM
 */
#include "../inc/appRes.h"
/*
 * <@var time out of the connect device
 */
static stTimer_TimeOut_t gstConnectedDeviceTimeOut;
/*
 <@var Connected decive state
 */
static uint8_t gu8DeviceState;
/*
 *buffer to send to serial
 */
static uint8_t gu8SendBuffer[10];
/*
 <@buf index to send by data
 */
static uint8_t gu8SendIndex;
/*
 <@ state of the callback system
 */
static uint8_t gu8DecviceTypeState;
/*
 <@edit value of the addressable system
 */
static uint8_t gu8DecviceTypeValue;
/*
 * Pointer to current check connection
 */
static stProductPrint_t * gpstProductPrint;
/*
 * <@var static connection state
 */
static uint8_t gu8ConnectionState;
/*
 *<@var data in in uasrt 
 */
static uint8_t gu8ReveiveBuffer[4];
/*
 *<@var data in index
 */
static uint8_t gu8SendFlag;
/*
 * <@var not send Data
 */
static uint8_t gu8ReceiveLength;

/*
  --------------------------------------------------------------------------------------------------------
  |                            < AddressableFunctionInit  >                                 |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  AddressableFunctionInit                                    |
  | < @Description       : change type of  Addressable System                    |                                   |                                                  |                                                           
  | < @return            : void                                                                       |                     
  --------------------------------------------------------------------------------------------------------
 */
void AddressableFunctionInit() {
    gu8ReceiveLength = 0;
    gu8SendFlag = 0;
    gu8ConnectionState = 0;
    gu8DecviceTypeValue = 0;
    gu8DecviceTypeState = 0;
    gu8SendIndex = 0;
    gu8DeviceState = 0;
}


/*
  --------------------------------------------------------------------------------------------------------
  |                            < changeDeciceTypeEvent  >                                 |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  changeDeciceTypeEvent                                    |
  | < @Description       : change type of  Addressable System                    |                                   |                                                  |                                                           
  | < @return            : void                                                                       |                     
  --------------------------------------------------------------------------------------------------------
 */
static void changeDeciceTypeEvent();
/*
  --------------------------------------------------------------------------------------------------------
  |                            < changeCencelTypeEvent  >                                 |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  changeCencelTypeEvent                                    |
  | < @Description       : cech type of  Addressable System                    |                                   |                                                  |                                                           
  | < @return            : void                                                                       |                     
  --------------------------------------------------------------------------------------------------------
 */
static void changeCencelTypeEvent();
/*
  --------------------------------------------------------------------------------------------------------
  |                            < ConnectionTimeOutEvnetCencel  >                                         |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  ConnectionTimeOutEvnetCencel                                            |
  | < @Description       : cencel for wait connection device                                             |                                   |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
static void ConnectionTimeOutEvnetCencel();

ISR(UART0_RECEIVE_INTERRUPT) {
    gu8ReveiveBuffer[gu8ReceiveLength] = usart0GetByte();
    if (gu8SendFlag) {
        if (gu8SendIndex < 10) {
            while (!Empty_BUFFER0());
            usart0PutByte(gu8SendBuffer[gu8SendIndex++]);
            return;
        }
        gu8SendFlag = 0;
        gu8SendIndex = 0;
    }

    /*Receive the data*/
    if (gu8ReveiveBuffer[gu8ReceiveLength] == '\n') {
        if ((gu8ReveiveBuffer[0] == 'S') &&(gu8ReveiveBuffer[1] == 'D')) {
            gu8ConnectionState = 4;
        } else if ((gu8ReveiveBuffer[0] == 'O') &&(gu8ReveiveBuffer[1] == 'K')) {
            gu8ConnectionState = 3;
        }
        gu8SendFlag = 0;
        gu8ReceiveLength = 0;
        return;
    } else {
        if (gu8ReceiveLength < 10) {
            gu8ReceiveLength++;
        } else {
            gu8ReceiveLength = 0;
        }
    }
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < stopCommuincationWithOtherDevice  >                                 |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  stopCommuincationWithOtherDevice                                    |
  | < @Description       :stop commuincation with RS485                     |                                   |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
void stopCommuincationWithOtherDevice() {
    ENABLE_TRANSMIT0_INTERRUPT();
    DISABLE_RECEIVE0_INTERRUPT();
    digitalPinWrite(COMM_CONTROL, GPIO_HIGH);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < DeviceType  >                                 |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  DeviceType                                    |
  | < @Description       : set Addressable System                    |                                   |                                                  |                                                           
  | < @return            : 0  is running , 1 is done                                                                        |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t DeviceTypeCallBack() {
    if (gu8DecviceTypeState == 0) {
        lcdClear();
        gu8DecviceTypeValue = gu8DeviceState; /*load from memory*/
        WriteMessage(0, MSG_DEVICETYPE);
        WriteMessage(1, MSG_DEVICETYPE2 + gu8DecviceTypeValue);
        CommanEventFunctions(changeDeciceTypeEvent, NULL, NULL, NULL, changeCencelTypeEvent);
        gu8DecviceTypeState = 1;
    }

    if (gu8DecviceTypeState == 1) {
        return (0);
    }

    if (gu8DecviceTypeState == 2) {
        if (SaveIntoMemory(ADDREASSABLE_PRODUCT_ADDRESS, &gu8DecviceTypeValue, 1)) {
            gu8DecviceTypeState = 0;
            setDeciveActive(gu8DecviceTypeValue);
        }
        return (0);
    }

    if (gu8DecviceTypeState == 3) {
        ReturnMenuCallBack();
        gu8DecviceTypeState = 0;
        return (1);
    }
    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < changeDeciceTypeEvent  >                                 |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  changeDeciceTypeEvent                                    |
  | < @Description       : change type of  Addressable System                    |                                   |                                                  |                                                           
  | < @return            : void                                                                       |                     
  --------------------------------------------------------------------------------------------------------
 */
static void changeDeciceTypeEvent() {
    gu8DecviceTypeValue ^= 1;
    gu8DecviceTypeState = 2;
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < changeCencelTypeEvent  >                                 |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  changeCencelTypeEvent                                    |
  | < @Description       : cech type of  Addressable System                    |                                   |                                                  |                                                           
  | < @return            : void                                                                       |                     
  --------------------------------------------------------------------------------------------------------
 */
static void changeCencelTypeEvent() {

    gu8DecviceTypeState = 3;
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < ConnectionDecive  >                                 |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  ConnectionDecive                                    |
  | < @Description       : check connection of the system                   |                                   |                                                  |                                                           
  | < @return            : void                                                                       |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t ConnectionDecive() {

    switch (gu8ConnectionState) {
        case 0:
            DISABLE_TRANSMIT0_INTERRUPT();
            ENABLE_RECEIVE0_INTERRUPT();
            digitalPinWrite(COMM_CONTROL, GPIO_LOW);
            appPrintMessage(gu8SendBuffer, 0, MSG_RD_CMD);
            copyBuff(gu8SendBuffer + 2, gpstProductPrint, 6);
            appPrintMessage(gu8SendBuffer, 8, MSG_SD_CMD);
            CommanEventFunctions(NULL, NULL, NULL, NULL, ConnectionTimeOutEvnetCencel);
            gu8ConnectionState = 1;
            break;
        case 1:
            if (!sysIsTimeoutMs(&gstConnectedDeviceTimeOut)) {
                lcdClear();
                WriteMessage(0, MSG_CONNECT_DECIVE1);
                WriteMessage(1, MSG_CONNECT_DECIVE2);
                while (!Empty_BUFFER0());
                gu8SendIndex = 0;
                usart0PutByte(gu8SendBuffer[gu8SendIndex++]);
                gu8SendFlag = 1;
                gu8ConnectionState = 2;
                sysSetPeriodMS(&gstConnectedDeviceTimeOut, 2000);
            }
            break;
        case 2:
            if (sysIsTimeoutMs(&gstConnectedDeviceTimeOut) == 0) {
                lcdClear();
                WriteMessage(0, MSG_CONNECT_DECIVE2);
                WriteMessage(1, MSG_CONNECT_DECIVE3);
                sysSetPeriodMS(&gstConnectedDeviceTimeOut, 1000);
                gu8ConnectionState = 1;
            }
            break;
        case 3:
            gu8SendFlag = 0;
            gu8ReceiveLength = 0;
            gu8SendIndex = 0;
            gu8ConnectionState = 0;
            ReturnMenuCallBack();
            stopCommuincationWithOtherDevice();
            return (1);
            break;
        case 4:
            break;
        default:
            break;

    }
    return (0);

}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < setDeciveActive  >                                                      |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  setDeciveActive                                                         |
  | < @Description       : state of the system load in power on                                          |                                   |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
void setDeciveActive(uint8_t DeviceType) {
    gu8DeviceState = DeviceType;
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < getSystemType  >                                                      |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  getSystemType                                                         |
  | < @Description       : get ststem State                                          |                                   |                                                  |                                                           
  | < @return            : 0 system not addssable ,1 system addressable                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t getSystemType() {
    return gu8DeviceState;
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < StartConnected  >                                                      |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  StartConnected                                                         |
  | < @Description       : Start connected with Other Device                                        |                                   |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
void StartConnected(stProductPrint_t *Product) {
    gpstProductPrint = Product;

}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < ConnectionTimeOutEvnetCencel  >                                         |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  ConnectionTimeOutEvnetCencel                                            |
  | < @Description       : cencel for wait connection device                                             |                                   |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
static void ConnectionTimeOutEvnetCencel() {
    gu8ConnectionState = 0;
    gu8SendFlag = 0;
    gu8SendIndex = 0;
    stopCommuincationWithOtherDevice();
    PrintLableInit();
}