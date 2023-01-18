/*
--------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                               | 
--------------------------------------------------------------------------------------------------
| < FILE                     : modules.h                                                         |                                  
| < Author                   : Hassan Elsaied                                                    |
| < Version                  : Mega2v241022                                                      |
| < Refences                 : no refence                                                        |
| < SRAM USAGE               : header file                                                       |
| < PROGRAM USAGE            : header file                                                       |                                      
| < Hardware Usage           : header file                                                       |
| < File Created             : 24-10-2022                                                        |
--------------------------------------------------------------------------------------------------
 */

#ifndef XC_MODULES_H
#define	XC_MODULES_H






/*
 ----------------------------------------------------------------------------------------------------------------------
 |                                   <Use this file >                                                                 |
 ----------------------------------------------------------------------------------------------------------------------
 | < @Description      : copy this file with created module in res.h in app and include this file in resource.h       |
 |                     : each res.h different in application application a using lcd and system and keypad            |
 |                     : application b using memory,comm module in application and  copy active modules from module.h |
 |                     : to res.h in application and include this resource.h                                          |
 | < @note             : to Enable Module set as 1                                                                    |
 |                     : to Disable module set a 0                                                                    |
 |                     : default all module as disabled in this file                                                  |
 | < @notice of danger : Please don't remove and edit this file this file has a refence to how add module             |
 ---------------------------------------------------------------------------------------------------------------------- 
 */


/*
 ---------------------------------------------------------------------------------------
 |                                <System MODULE>                                      | 
 ---------------------------------------------------------------------------------------
 | <macro F_CPU                  : F_CPU CLOCK  >look clock.h                          |                                        |
 | <macro @N_OF_US_REQUIRED      : each F_CPU has base number of micro                 |
 |                               : select one of number of micro seconds               |
 |                               : _number+us  > is defined and supported time         |  
 | <macro SRAM_USAGE             : 14 Byte                                             |
 | <macro PROGRAM_USAGE          : 694 byte (347 Instruction)                          |
 ---------------------------------------------------------------------------------------
 */
#define     F_CPU                          XTAL_01000000
#define     N_OF_US_REQUIRED               (_32000us)
/*
 ---------------------------------------------------------------------------------------
 |                                <GPIO MODULE>                                        | 
 ---------------------------------------------------------------------------------------
 | < macro GPIO2_PREFER_SPEED     : gpio speed acess                                   |
 |                                : 0 the  function called used                        |
 |                                : 1 the  function not called and used inline         |
 | < macro GPIO2_IOREGS_ABOVEFF   : enable or disable access gpio with in atomic block |
 |                                : 0 gpio acess without atomic                        |
 |                                : 1 gpio acess with in atomic                        |
 |                                : @note : atomic means disable any extrnal interrupt |
 |                                :       : to not effect in gpio pins at write or...  |
 ---------------------------------------------------------------------------------------
 */
#define     GPIO2_PREFER_SPEED               (1)
#define     GPIO2_IOREGS_ABOVEFF             (0)





/*
 ---------------------------------------------------------------------------------------
 |                     < Periodically tasks >                                          |
 ---------------------------------------------------------------------------------------
 | < @PERIODICALLY_TASKS_MAX_TIME: @assume1 task 1 = 5ms , task 2 = 20 ms              |
 |                               : the max time is 20ms becouse 20/5 = Interger value  |
 |                               : and 20ms is Lagrest number                          |
 |                               : @assume2 task 1 = 5ms , task 2 = 7ms the max time   |
 |                               : is 7ms *5ms = 35ms becouse the 35ms can divid by 5,7|
 ---------------------------------------------------------------------------------------
 */
#define      PERIODICALLY_TASKS_MAX_TIME        (64)


/*
 ------------------------------------------------------------------------------------------------------------
 |                             < USART_MODULE  >                                                            |                                       
 |-----------------------------------------------------------------------------------------------------------
 | < USART_MODULE               : 0 module is not active                                                    |
 |                              : 1 module is active                                                        |
 ------------------------------------------------------------------------------------------------------------
 | < USARTx_ENABLED            : to enable USART please define USART0_ENABLED                               |
 |                             : or defined USART0_ENABLED or defined both                                  |
 |                             : version supported a 4 USART (0,1,2,3)                                      |
 |-----------------------------------------------------------------------------------------------------------
 | < speed (Mbps)                                       |  Bit duration  |  byte rate      | byte duration  |
 |------------------------------------------------------|----------------|-----------------|----------------|  
 | < UARTx_BUADRATE           @StandBaudRate_1200       |    833.33 us   |  00120 byte/s   |  8333.33 us    |                
 | < x is 0 to 3              @StandBaudRate_2400       |    416.66 us   |  00240 byte/s   |  4166.66 us    |                                   
 |                            @StandBaudRate_4800       |    208.33 us   |  00480 byte/s   |  2083.33 us    |                     
 |                            @StandBaudRate_9600       |    104.16 us   |  00960 byte/s   |  1041.66 us    |                            
 |                            @StandBaudRate_19200      |    052.08 us   |  01920 byte/s   |  0520.83 us    |                                      
 |                            @StandBaudRate_38400      |    026.04 us   |  03840 byte/s   |  0260.41 us    |                        
 |                            @StandBaudRate_57600      |    017.36 us   |  05760 byte/s   |  0173.61 us    |
 |                            @StandBaudRate_76800      |    013.68 us   |  07680 byte/s   |  0130.20 us    |
 |                            @StandBaudRate_115200     |    008.68 us   |  11520 byte/s   |  0086.00 us    |                                                                  
 ------------------------------------------------------------------------------------------------------------
 | < note : @UARTx_BUADRATE      : x  0 to 3 if defined more UART please defined the baud rate every uart   |
 |        : @UART_XYZ            : not supported in current version the usart is work only 8nit data and    |
 |                               : and  no parity and 1-stop bit in new version can support this  and       | 
 |                               : @X is a number of bits and @Y type the parity and @Z is n-stop bits      | 
 | < SRAM USAGE                  : no-used                                                                  |
 | < PROGRAM USAGE               : 40 Byte with enable Uart 0, Uart 1 (20 Instruction)                      |                                                |
 ------------------------------------------------------------------------------------------------------------
 */
#define  USART_MODULE                                                           (0)
#if      USART_MODULE
#define  USART0_ENABLED
#define  UART0_BUADRATE                                                     StandBaudRate_19200
#endif




/*
----------------------------------------------------------------------------------------
|                                <TWI MODULE>                                          | 
----------------------------------------------------------------------------------------
| < TWI_MODULE              : 0 module is not active                                   | 
|                           : 1 module is active                                       |
| < TWI_TYPE                : @TWI_MASTER_SLAVE >  Work as two mode                    |
|                           : @TWI_SLAVE        >  work as slave                       |
|                           : @TWI_MASTER       >  work as master                      | 
| < TWI_INTERNAL_PULL_UP    : @TWI_PULL_ENABLE  >  enable internal pull up             |
|                           : @TWI_PULL_DIABLE  >  disable internal pull up            | 
| < TWI_SCL_PIN             : clock gpio pin if has enable interanl pull up            |
|                           : at disaple pull up don't care                            |
| < TWI_SDA_PIN             : data gpio pin if has enable interanl pull up             |
|                           : at disaple pull up don't care                            |
| < SRAM USAGE              : 8-Byte in Master Mode  && Slave mode 7 Byte              |  
| < PROGRAM USAGE           : 658 Byte (329 Instruction)   in Master mode              |
|                           : under test in slave mode                                 |   
----------------------------------------------------------------------------------------
 */
#define  TWI_MODULE                                    (0)
#if    TWI_MODULE
#define             TWI_TYPE                                      TWI_MASTER
#define            TWI_INTERNAL_PULL_UP                           TWI_PULL_ENABLE
#define            TWI_SCL_PIN                                    NOT_A_PIN
#define            TWI_SDA_PIN                                    NOT_A_PIN
#endif

/*
----------------------------------------------------------------------------------------
|                                <EEPROM MODULE>                                       | 
----------------------------------------------------------------------------------------
| < EEPROM_MODULE           : 0 module is not active                                   | 
|                           : 1 module is active                                       |
| < SRAM USAGE              : 21-Byte 10 in Read Buffer 4Byte Time out , 7 Byte used   |  
| < PROGRAM USAGE           : 722 Byte (361 Instruction)                               |  
----------------------------------------------------------------------------------------
 */
#define       EEPROM_MODULE    (0)
/* 
 -------------------------------------------------------------------------------------------------------------------------------------
 |                         <EX_EEPROM MODULE>                                                                                        |              
 -------------------------------------------------------------------------------------------------------------------------------------
 | < EX_EEPROM_MODULE         : 0 module is not active                                                                               |
 |                            : 1 module is active                                                                                   |
 | < EXEEPROM_MEM_ADDR_LEN    : internal address select one by four option >                                                         |              
 |                            : <@one   TWI_SLAVE_NO_INTERNAL_ADDRESS >  :  chip no have Internal address                            |         
 |                            : <@two   TWI_SLAVE_ONE_BYTE_SIZE    >     :  chip have one byte internal address 2^8 addresses        |        
 |                            : <@three TWI_SLAVE_TWO_BYTE_SIZE    >     :  chip have two byte internal address 2^16 addresses       |         
 |                            : <@Four  TWI_SLAVE_THREE_BYTE_SIZE  >     :  chip have a three byte internal address 2^24 addresses   |        
 | < EXEEPROM_MEM_PAGE_SIZE   : write page size in external memory >                                                                 |            
 | < EXEEPROM_MEM_ADDR        : chip address                                                                                         |             
 | < EXEEPROM_MEM_MAX_BUFFER  : max buffer read and write                                                                            |
 | < EXEEPROM_BUS_SPEED       : TWI_100KHZ   chip work speed 100Khz clock                                                            |
 |                            : TWI_400KHZ   chip work speed 10Khz  clock                                                            |
 | < SRAM_USAGE               : 40 Byte                                                                                              |
 |                            : @TWI  9 Byte Used                                                                                    |
 |                            : @Time Out  4 Byte                                                                                    |
 |                            : @eeprom description 11 Byte                                                                          |
 |                            : @Internal Read Buffer default used 16 Byte                                                           |
 | < PROGRAM_USAGE            : 1002 byte (501 Instruction)                                                                          |                                                                                                                        
 -------------------------------------------------------------------------------------------------------------------------------------
 */
#define  EX_EEPROM_MODULE             (0)
#if  EX_EEPROM_MODULE 
#define  EXEEPROM_MEM_ADDR_LEN        TWI_SLAVE_ONE_BYTE_SIZE
#define  EXEEPROM_MEM_PAGE_SIZE       (32)
#define  EXEEPROM_MEM_ADDR            (0xA0)
#define  EXEEPROM_MEM_MAX_BUFFER      (16)
#define  EXEEPROM_BUS_SPEED           (TWI_400KHZ)
#endif

/* 
 -------------------------------------------------------------------------------------------------
 |                          < LCD MODULE                                                         |                                            
 -------------------------------------------------------------------------------------------------
 | < LCD_MODULE              : 0 module is not active                                            |
 |                           : 1 module is active                                                |
 | < LCD_NUMBER_OF_LINE      : LCD has a number of line  shuc as 2 , 4 , , 3 ,..etc              |                                                      
 | < LCD_NUMBER_OF_BYTE      : LCD number of char per line   16 char , 20 char , ......etc       |                                                               
 | < LCD_RW                  : read pin in gpio pin such as GPIO_A0                              |                                                          
 | < LCD_RS                  : RS   pin in gpio pin such as GPIO_A1                              |
 | < LCD_EN                  : Enable pin in gpio pin such as GPIO_A2                            |
 | < LCD_D4                  : Data  bit 4 in gpio pin such as GPIO_A3                           |
 | < LCD_D5                  : Data  bit 4 in gpio pin such as GPIO_A4                           |
 | < LCD_D6                  : Data  bit 4 in gpio pin such as GPIO_A5                           |
 | < LCD_D7                  : Data  bit 4 in gpio pin such as GPIO_A6                           |
 | < SRAM USAGE              : 36-Byte in default ==> 32 buffer , 4 byte data                    |  
 | < PROGRAM USAGE           : 980 Byte (950 byte (475 Instruction)) + 30 Byte custom char       |                             
 -------------------------------------------------------------------------------------------------
 */
#define  LCD_MODULE               (0)
#if  LCD_MODULE
#define  LCD_NUMBER_OF_LINE        (2)
#define  LCD_NUMBER_OF_BYTE        (16)
#define  LCD_RW                   (GPIO_A0)
#define  LCD_RS                   (GPIO_A1)
#define  LCD_EN                   (GPIO_A2)
#define  LCD_D4                   (GPIO_A2)
#define  LCD_D5                   (GPIO_A2)
#define  LCD_D6                   (GPIO_A2)
#define  LCD_D7                   (GPIO_A2)
#endif
/* 
 -------------------------------------------------------------------------------------------------
 |                          < KEYPAD MODULE  >                                                   |                                             
 -------------------------------------------------------------------------------------------------
 | < KEYPAD_MODULE                : 0 module is not active                                       |
 |                                : 1 module is active                                           |
 | < KEY_PREDIOC_TASK_TIME        : run evey x time                                              |
 | < KEYPAD_MAX_ROW               : max row in keypad and this value less than 8                 |
 | < KEYPAD_MAX_COL               : max column in keypad and this value less than 8              |
 | < KEYPAD_MAX_BUFFER            : max key stored                                               |
 | < KEYPAD_DEDEBOUND_TIME        : time required to press or released switch                    |
 | < KEYPAD_LONG_TIME             : time required to long press                                  |
 | < KEYPAD_REPEAT_TIME           : time required to repeat key                                  |
 | < KEYPAD_REPEAT_RATE           : time required between repeat key                             |
 | < note                         : keypad state is fixed active low                             |
 | < pin                          : replace NOT_A_PIN by digital pin with max rows and column    |                    
 | < SRAM USAGE                   : (4 Byte buffer , 6 buffer dis , r*c byte  , 2byte            |
 | < PROGRAM USAGE                : (764)((548 Byte)+(216Byte when enable signal))               |               
 -------------------------------------------------------------------------------------------------
 */
#define   KEYPAD_MODULE                   0
#if KEYPAD_MODULE
#define   KEYPAD_MAX_ROW                 (4)
#define   KEYPAD_MAX_COL                 (4)
#define   KEYPAD_DEDEBOUND_TIME          (20)   /* 20 ms*/
#define   KEYPAD_LONG_TIME               (2000) /* 2 second*/
#define   KEYPAD_REPEAT_TIME             (3000) /* 3 second*/
#define   KEYPAD_REPEAT_RATE             (5)    /* 5 ms*/
#define   KEY_PREDIOC_TASK_TIME          (10)
/***********************ROW Pins********************/
#define KEYPAD_C01_PIN          NOT_A_PIN
#define KEYPAD_C02_PIN          NOT_A_PIN
#define KEYPAD_C04_PIN          NOT_A_PIN
#define KEYPAD_C05_PIN          NOT_A_PIN
#define KEYPAD_C06_PIN          NOT_A_PIN
#define KEYPAD_C07_PIN          NOT_A_PIN
#define KEYPAD_C08_PIN          NOT_A_PIN
/***********************Clomuns Pins********************/
#define KEYPAD_SW01_PIN          NOT_A_PIN
#define KEYPAD_SW02_PIN          NOT_A_PIN
#define KEYPAD_SW03_PIN          NOT_A_PIN
#define KEYPAD_SW04_PIN          NOT_A_PIN
#define KEYPAD_SW05_PIN          NOT_A_PIN
#define KEYPAD_SW06_PIN          NOT_A_PIN
#define KEYPAD_SW07_PIN          NOT_A_PIN
#define KEYPAD_SW08_PIN          NOT_A_PIN
#endif


/* 
 -------------------------------------------------------------------------------------------------
 |                          < BUTTON_MODULE   >                                                  |                                             
 -------------------------------------------------------------------------------------------------
 | < BUTTON_MODULE                : 0 module is not active                                       |
 |                                : 1 module is active                                           |
 | < NUMBER_OF_BUTTON             : number  of Buttons  used                                     |  
 | < BUTTON_PREDIOC_TASK_TIME     : run evey x time                                              |
 | < BUTTON_MAX_BUFFER            : max key stored                                               |
 | < BUTTON_DEDEBOUND_TIME        : time required to press or released switch                    |
 | < BUTTON_LONG_TIME             : time required to long press                                  |
 | < BUTTON_REPEAT_TIME           : time required to repeat key                                  |
 | < BUTTON_REPEAT_RATE           : time required between repeat key                             |
 | < note                         : keypad state is fixed active low                             |          
 | < SRAM USAGE                   : 14 Byte + BUTTON_MAX_BUFFER                                  |  
 | < PROGRAM USAGE                : 624 Byte (312 Instruction)                                   |               
 -------------------------------------------------------------------------------------------------
 */
#define   BUTTON_MODULE                   0
#if BUTTON_MODULE
#define   NUMBER_OF_BUTTON               (1)
#define   BUTTON_DEDEBOUND_TIME          (20)   /* 20 ms*/
#define   BUTTON_LONG_TIME               (2000) /* 2 second*/
#define   BUTTON_REPEAT_TIME             (3000) /* 3 second*/
#define   BUTTON_REPEAT_RATE             (5)    /* 5 ms*/
#define   BUTTON_PREDIOC_TASK_TIME       (10)   
#define   BUTTON_MAX_BUFFER              (4)
#endif

/* 
 -------------------------------------------------------------------------------------------------
 |                          < DS1307 MODULE >                                                    |                                             
 -------------------------------------------------------------------------------------------------
 | < DS1307_MODULE                : 0 module is not active                                       |
 |                                : 1 module is active                                           |
 | < DS1307_MODE                  : DS1307_MODE_12H  DS1307 work with AM and PM                  |
 |                                : DS1307_MODE_24H  DS1307 work witch normal clock              |
 | < DS1307_PERDIOC_READ_PER_MIN  : DS1307 Read clock every a min clock                          |
 | < SRAM USAGE                   : 21-Byte                                                      |  
 | < PROGRAM USAGE                : 1248 Byte (624 Instruction)                                  |
 | < @note                        : in this version not support a 12 hour clock operation        |                                                                                                              
 -------------------------------------------------------------------------------------------------
 */
#define  DS1307_MODULE             (0)
#if DS1307_MODULE
#define          DS1307_MODE                                     DS1307_MODE_24H    
#define          DS1307_PERDIOC_READ_PER_MIN                     5UL
#endif

/* 
 -------------------------------------------------------------------------------------------------
 |                          < LCD MNUE MODULE >                                                  |                                             
 -------------------------------------------------------------------------------------------------
 | < LCDMNUE_MODULE               : 0 module is not active                                       |
 |                                : 1 module is active                                           |
 | < MENU_DOWN_SW                 : down switch (-) code set form keypad                         |
 | < MENU_UP_SW                   : up switch (+) code set form keypad                           |
 | < MENU_ENTER_SW                : enter switch  code set form keypad                           |
 | < MENU_CANSEL_SW               : cancel switch  code set form keypad                          |
 | < SRAM USAGE                   : 3-Byte                                                       |  
 | < PROGRAM USAGE                : 908 Byte (454 -Instruction)                                  |
 | < @note                        :  no option used                                              |                                                                                                              
 -------------------------------------------------------------------------------------------------
 */
#define        LCDMNUE_MODULE               (0)
#if  LCDMNUE_MODULE
#define        MENU_DOWN_SW                  KEYPAD_SW01
#define        MENU_UP_SW                    KEYPAD_SW02
#define        MENU_ENTER_SW                 KEYPAD_SW02
#define        MENU_CANSEL_SW                KEYPAD_SW02
#endif
/*
 --------------------------------------------------------------------------------------
 |                               < CSMA_MODULE  >                                     |                                       
 |-------------------------------------------------------------------------------------
 |< @CSMA_MODULE                 : 0 module is not active                             |
 |                               : 1 module is active                                 |
 |< @STATION_BLOCK_TIME          : Station Blocking Time(ms)after send Block address  |    
 |< @COM_PLAYLOAD_SIZE           : number of Byte Data send                           |                                                  
 --------------------------------------------------------------------------------------
 */
#define    CSMA_MODULE                                     (0)
#if        CSMA_MODULE
#define    STATION_BLOCK_TIME                              (50)  
#define    COM_PAYLOAD_SIZE                               (10)
#define    COM_MAX_RETARY                                  (10)
#endif



/*
 ----------------------------------------------------------------------------------------
 |                                <SIGNALGENERATED_MODULE>                              | 
 ----------------------------------------------------------------------------------------
 | < BUZ_MODULE              : 0 module is not active                                   | 
 |                           : 1 module is active                                       |
 | < SIGNAL_NUMBER_OF_PINS   : number of Pins to Generated different signal             |
 | < SRAM USAGE              : 10 Byte Per Pin  +2 Byte Pinter to first signal          |      
 | < PROGRAM USAGE           : (918 Byte ) 459 Instruction                              |  
 ----------------------------------------------------------------------------------------
 */
#define       SIGNALGENERATED_MODULE                  (1)
#if SIGNALGENERATED_MODULE
#define   SIGNAL_NUMBER_OF_PINS                       (2)
#endif




#endif	/* XC_MODULES_H */


