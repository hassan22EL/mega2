/*
--------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                     | 
--------------------------------------------------------------------------------------------------------
| < FILE                     : lcdmnue.h                                                               |                                  
| < Author                   : Hassan Elsaied                                                          |
| < Version                  : Mega2v241022                                                            |
| < Refences                 : no refence                                                              |
| < SRAM USAGE               : 3 Byte (2 byte pointer to constant , 1-byte flags                       |
| < PROGRAM USAGE            : 908-byte (454 Instuctiosn)                                              |                                      
| < Hardware Usage           : LCD and buttons or keypads                                              |
| < File Created             : 24-10-2022                                                              |
--------------------------------------------------------------------------------------------------------
 */
#ifndef LCDMENU_H
#define	LCDMENU_H
#include "../mega.h"

#if defined LCDMNUE_MODULE
#if LCDMNUE_MODULE 
/*
--------------------------------------------------------------------------------------------------
|                           < menu main actions >                                                | 
--------------------------------------------------------------------------------------------------
 */
/*down switch (-)*/
#ifndef MENU_DOWN_SW 
#define  MENU_DOWN_SW  KEYPAD01_SW01
#endif 
/*up switch (+)*/
#ifndef MENU_UP_SW 
#define  MENU_UP_SW  KEYPAD01_SW02
#endif 

/*enter switch*/
#ifndef  MENU_ENTER_SW 
#define  MENU_ENTER_SW  KEYPAD01_SW03
#endif 
/*cancel switch*/
#ifndef MENU_CANSEL_SW
#define MENU_CANSEL_SW  KEYPAD01_SW04
#endif


/*
--------------------------------------------------------------------------------------------------
|                           < Mnue call back Function >                                          | 
--------------------------------------------------------------------------------------------------
 */
typedef uint8_t(* pFuncMenueCallBack_t)(void);

/*
 --------------------------------------------------------------------------------------------------
 |                                <   mnue Descirption   >                                        |
 --------------------------------------------------------------------------------------------------
 | < Description                   : mnue struct                                                  |
 | < Uasge                         : 10 Byte in Progrm Memeory + lable                            |                                     
 | < param menuNext                : next item of the current item                                |
 | < param menuPre                 : previous item of the current item                            | 
 | < param menuParent              : Parent of the current item                                   |
 | < param menuChild               : first child of the currnt item                               |
 | < param menuCallback            : action of the item                                           |
 | < param menuLable               : string lable in lcd                                          |
 --------------------------------------------------------------------------------------------------
 */

typedef struct menueItem_s {
    struct menueItem_s const * PROGMEM menuNext; /*pointer to constant menueItem_s */
    struct menueItem_s const * PROGMEM menuPre; /*pointer to constant menueItem_s */
    struct menueItem_s const * PROGMEM menuParent; /*pointer to constant menueItem_s */
    struct menueItem_s const * PROGMEM menuChild; /*pointer to constant menueItem_s */
    const pFuncMenueCallBack_t menuCallback; /*pointer to constant pointer (pointer of the call back function)*/
    const char * menuLable; /*pointer to constant char */
} menueItem_t;

/*
 --------------------------------------------------------------------------------------------------
 |                           < null item  >                                                       | 
 --------------------------------------------------------------------------------------------------
 |< @Description : when the create item and not have any next (last item in menu)can set nullitem |
 |              : in next  or the created item is first item set previous item is nullitem        |
 |              : and apply this in all                                                           |
 ---------------------------------------------------------------------------------------------------          
 */
extern const menueItem_t PROGMEM NullItem;
/*
 --------------------------------------------------------------------------------------------------
 |                           < MenuItem  >                                                        | 
 --------------------------------------------------------------------------------------------------
 | < @Description    : create menue item                                                          |
 | < @Param Name     : current item created                                                       |
 | < @Param Next     : next item of the current item                                              |
 | < @Param Previous : Previous item                                                              |
 | < @Param Parent   : parent of the current item                                                 |
 | < @Child          : first child item of the current item                                       |
 | < @Callback       : in current has chlid set a null and else set a function to action item     |
 | < @Lable          : Data show in LCD                                                           |
 --------------------------------------------------------------------------------------------------          
 */
#define MenuItem(Name, Next, Previous, Parent, Child, Callback,NameLable , Lable) \
    extern const menueItem_t PROGMEM   Next; \
    extern const menueItem_t  PROGMEM  Previous;\
    extern const menueItem_t  PROGMEM  Parent;\
    extern const menueItem_t PROGMEM  Child; \
    const char NameLable[] PROGMEM = {Lable};\
    const menueItem_t PROGMEM Name = {&Next, &Previous, &Parent, &Child, Callback, NameLable};

/*xc-compiler*/
/*
#define MenuItem(Name, Next, Previous, Parent, Child, Callback, Lable) \
    extern const menueItem_t    Next; \
    extern const menueItem_t    Previous;\
    extern const menueItem_t    Parent;\
    extern const menueItem_t   Child;\
const menueItem_t PROGMEM Name = {&Next, &Previous, &Parent, &Child, Callback, Lable};
 */
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < MenuInit >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  MenuInit                                                                |
 | < @Description       : initialization all variables                                                  |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void MenuInit();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < menueDriver >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  menueDriver                                                             |
 | < @Description       : run in background task at open menu                                           |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void menueDriver();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < menuIsOpen >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  menuIsOpen                                                              |
 | < @Description       : check menue is open or not                                                    |                  
 | < @return            : 0 : mnue closed                                                               |
 | <                    : 1 : mnue open                                                                 |                                                             
 --------------------------------------------------------------------------------------------------------
 */
uint8_t menuIsOpen();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < menuStartItem >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  menuStartItem                                                           |
 | < @Description       : menu open form start item this call when is open menu with assignment item    |  
 | < @Param item        : first item in the mnue                                                        |                 
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void menuStart(const menueItem_t *item);


#endif
#endif

#endif	/* LCDMENU_H */

