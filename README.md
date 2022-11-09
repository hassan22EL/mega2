**A- install lib in your porject** \
 1- git clone https://github.com/hassan22EL/mega2.git \
 2- add inc files in headers file in your project \
 3- install lib by mega/dis/mega.a to add in lib in your project \

 **B- install module** 
 to add module in project copy module from modul.h within inc folder in res.h in application 
 for example to add module twi copy this block from module.h and pate into res.h in your application
```ruby
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
| < PROGRAM USAGE          : 826 Byte (413 Instruction)   in Master mode               |
|                          : under test in slave mode                                  |   
----------------------------------------------------------------------------------------
 */

#define  TWI_MODULE                                                (0)
#if    TWI_MODULE
#define             TWI_TYPE                                      TWI_MASTER
#define            TWI_INTERNAL_PULL_UP                           TWI_PULL_ENABLE
#define            TWI_SCL_PIN                                    NOT_A_PIN
#define            TWI_SDA_PIN                                    NOT_A_PIN
#endif
```
1- copy this block from module.h in res.h in your appliction \
2- change paramter required such twi as master or slave or have internal pull up or not \
3- in case pull up chang pins in GPIO_Px  ==> GPIO_A0 or GPIO_A1 P--> port name , x is pin number \
4- GPIO in all cases use this defintion in all other modules or used in your application \
5- after finsh edit all paramter in modules don't forget the active module by set one complete \

```ruby
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
| < PROGRAM USAGE          : 826 Byte (413 Instruction)   in Master mode               |
|                          : under test in slave mode                                  |   
----------------------------------------------------------------------------------------
 */

#define  TWI_MODULE                                                (1)
#if    TWI_MODULE
#define             TWI_TYPE                                      TWI_MASTER
#define            TWI_INTERNAL_PULL_UP                           TWI_PULL_ENABLE
#define            TWI_SCL_PIN                                    GPIO_A2
#define            TWI_SDA_PIN                                    GPIO_A3
#endif
```
6- after complete please include the res.h in resourse .h 
```ruby
/*
 ****************************************************
 *                    Modules                       *
 * **************************************************
 */
//add  include the res.h in application 
#include "../../mega2.X/src/mega/exeeprom/examples/exeepromExamples.X/inc/res.h"
```
**look example in each driver to how implement a app with mega**
