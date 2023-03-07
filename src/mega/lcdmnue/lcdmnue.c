/*
--------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                     | 
--------------------------------------------------------------------------------------------------------
| < FILE                     : lcdmnue.c                                                               |                                  
| < Author                   : Hassan Elsaied                                                          |
| < Version                  : Mega2v241022                                                            |
| < Refences                 : no refence                                                              |
| < SRAM USAGE               : 3 Byte (2 byte pointer to constant , 1-byte flags                       |
| < PROGRAM USAGE            : 908-byte (454 Instuctiosn)                                              |                                      
| < Hardware Usage           : LCD and buttons or keypads                                              |
| < File Created             : 24-10-2022                                                              |
--------------------------------------------------------------------------------------------------------
 */
#include <stdint-gcc.h>
#include <avr/pgmspace.h>

#include "../../../inc/mega.h"
#if defined LCDMNUE_MODULE
#if LCDMNUE_MODULE
/*
--------------------------------------------------------------------------------------------------------
|                           < Required Modules check active >                                          | 
--------------------------------------------------------------------------------------------------------
 */

#if (!defined (LCD_MODULE)) || (!defined (KEYPAD_MODULE))
#error  "Please check defined lcd module and keypad module"
#else 
#if ((LCD_MODULE == 0 ) || (KEYPAD_MODULE == 0))
#error "Please check active lcd module and keypad module"
#endif
#endif
/*
 --------------------------------------------------------------------------------------------------------
 |                                <   mnue chlid Descirption   >                                        |
 --------------------------------------------------------------------------------------------------------
 | < Description                   : menu Item Info struct                                              |
 | < Uasge                         : 2 byte                                                             |
 | < param ItemsCount              : number of the item in parent                                       |
 | < param position                : restore  item position in parent (1,2,3,4                          |        
 --------------------------------------------------------------------------------------------------------
 */

#if  LCD_NUMBER_OF_LINE >2

typedef struct Info_s {
    uint8_t ItemsCount;
    uint8_t position;
} menuItemInfo_t;
#endif

/*
 --------------------------------------------------------------------------------------------------------
 |                           < null item  >                                                             | 
 --------------------------------------------------------------------------------------------------------
 |< @Description : when the create item and not have any next (last item in menu)can set nullitem       |
 |              : in next  or the created item is first item set previous item is nullitem              |
 |              : and apply this in all                                                                 |
 --------------------------------------------------------------------------------------------------------     
 */
#if COMPILER_TYPE == GCC
const menueItem_t NullItem PROGMEM = {(const menueItem_t *) NULL, (const menueItem_t *) NULL, (const menueItem_t *) NULL, (const menueItem_t *) NULL,
    (pFuncMenueCallBack_t) NULL,
    (const char *) NULL};
#elif COMPILER_TYPE == XC
const menueItem_t NullItem = {(const menueItem_t *) NULL, (const menueItem_t *) NULL, (const menueItem_t *) NULL, (const menueItem_t *) NULL,
    (pFuncMenueCallBack_t) NULL,
    (const char *) NULL};
#endif
/*
 ---------------------------------------------------------------------------------------------------------
 |                           < current item  >                                                           | 
 ---------------------------------------------------------------------------------------------------------
 | @var  : pointer to constant var    ( pointer to value stored into program memory                      |
 |       : @picutre 1  : const menueItem_t *gpCurrentMenuItem                                            |
 |       : @picutre 2  : menueItem_t const *gpCurrentMenuItem                                            | 
  --------------------------------------------------------------------------------------------------------  
 */
static const menueItem_t *gpCurrentMenuItem;
/*
  --------------------------------------------------------------------------------------------------------
 |                           < flags  >                                                                  | 
  --------------------------------------------------------------------------------------------------------
 | < @B0     : menu action flag  (this flag indicator a mnue have new action or not                      |
 | < @B1     : menu show data update (this flag indicator a new item showing                             |
 | < @B2     : menu open  (indicator menu open or close)                                                 |
 ---------------------------------------------------------------------------------------------------------
 */
static volatile byte_Flags_t gu8OPenMenueFlag;
/*
 --------------------------------------------------------------------------------------------------------
 |                           < Basic Function Definitions  >                                            | 
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getmenuLable >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getmenuLable                                                            |
 | < @Description       : return Parent item of input item                                              |
 | < @Param item        : pointer to constant item to get data                                          |                   
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const char * getmenuLable(const menueItem_t *item);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getmenuNext >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getmenuNext                                                             |
 | < @Description       : return Parent item of input item                                              | 
 | < @Param item        : pointer to constant item to get data                                          |                   
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const menueItem_t * getmenuNext(const menueItem_t *item);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getmenuPrev >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getmenuPrev                                                             |
 | < @Description       : return Parent item of input item                                              |
 | < @Param item        : pointer to constant item to get data                                          |                   
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const menueItem_t * getmenuPrev(const menueItem_t *item);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getmenuParent >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getmenuParent                                                           |
 | < @Description       : return Parent item of input item                                              |  
 | < @Param item        : pointer to constant item to get data                                          |                  
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const menueItem_t * getmenuParent(const menueItem_t *item);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getmenuChlid >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getmenuChlid                                                            |
 | < @Description       : return Parent item of input item                                              |
 | < @Param item        : pointer to constant item to get data                                          |                   
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const menueItem_t * getmenuChlid(const menueItem_t *item);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <showMenueItem >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getmenuChlid                                                            |
 | < @Description       : assign current item by input item                                             |
 | < @Param item        : pointer to constant item to be as a current item                              |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void showMenueItem(const menueItem_t *item);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <menuEvent >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   menuItemAction                                                         |
 | < @Description       : call back exeucation of the current item                                      |                 
 | < @return            : call back state 0 is call back runing and 1 call back done                    |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t menuItemAction();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <menuAction >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   menuAction                                                             |
 | < @Description       : run with event enter                                                          |                 
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void menuAction();
#if LCD_NUMBER_OF_LINE > 2
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getItemInfo >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : menuItemInfo_t   getItemInfo                                                  |
 | < @Description       : get item position from item list                                              |    
 | < @Param item        : pointer to constant item                                                      |             
 | < @return            : item information ( number of item in list and item position in lisit          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static menuItemInfo_t getItemInfo(const menueItem_t *item);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <menuLCDChild >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   menuLCDChild                                                           |
 | < @Description       : lcd write data of the items per pos                                           |    
 | < @Param item        : pointer to constant item                                                      |
 | < @Param line        : item pos in lcd line 0or 1 , ...,max lines                                    |
 | < @Param pos         : item start char pos in lcd line 0 ,1,..., number of char per line             |             
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void menuLCDChild(const menueItem_t *item, uint8_t line, uint8_t pos);
#endif

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <menuLCDReader >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   menuLCDReader                                                          |
 | < @Description       : lcd write data of the items and parent                                        |                
 | < @return            : void                                                                          |                                                    
 --------------------------------------------------------------------------------------------------------
 */
static void menuLCDReader();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <menueCencelEvent >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   menueCencelEvent                                                       |
 | < @Description       : action when set Cencel Event                                                  |                
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t menueCencelEvent(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <menueUpEvent >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   menueUpEvent                                                           |
 | < @Description       : action when set Up Event                                                      |                
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t menueUpEvent(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <menueDownEventEvent >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   menueDownEventEvent                                                    |
 | < @Description       : action when set DownEvents Event                                              |                
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t menueDownEventEvent(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <menueDownEventEvent >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   menueDownEventEvent                                                    |
 | < @Description       : action when set DownEvents Event                                              |                
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t menueDownEventEvent(stkey_t *key);

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <MenuRegisterKey >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   MenuRegisterKey                                                        |
 | < @Description       : Menu Event Register                                                           |  
 | < @Param type        : type 0 is remove all Register data   , one is register all data               |
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void MenuRegisterKey(uint8_t type);
/*
 --------------------------------------------------------------------------------------------------------
 |                           < Basic Function Implementions  >                                          | 
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getmenuLable >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getmenuLable                                                            |
 | < @Description       : return Parent item of input item                                              |
 | < @Param item        : pointer to constant item to get data                                          |                   
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const char * getmenuLable(const menueItem_t *item) {
#if COMPILER_TYPE == GCC
    return (const char *) pgm_read_word(&item->menuLable); /*gcc-compiler*/
#elif COMPILER_TYPE == XC
    return (const char *) (item->menuLable); /*xc-compiler*/
#endif
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getmenuNext >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getmenuNext                                                             |
 | < @Description       : return Parent item of input item                                              | 
 | < @Param item        : pointer to constant item to get data                                          |                   
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const menueItem_t * getmenuNext(const menueItem_t *item) {
#if COMPILER_TYPE == GCC
    return (const menueItem_t *) pgm_read_word(&item->menuNext); /*gcc-compiler*/
#elif  COMPILER_TYPE == XC
    return (const menueItem_t *) (item->menuNext); /*xc-compiler*/
#endif
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getmenuPrev >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getmenuPrev                                                             |
 | < @Description       : return Parent item of input item                                              |
 | < @Param item        : pointer to constant item to get data                                          |                   
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const menueItem_t * getmenuPrev(const menueItem_t *item) {
#if COMPILER_TYPE == GCC
    return (const menueItem_t *) pgm_read_word(&item->menuPre); /*gcc-compiler*/
#elif COMPILER_TYPE == XC
    return (const menueItem_t *) (item->menuPre); /*xc-compiler*/
#endif
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getmenuParent >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getmenuParent                                                           |
 | < @Description       : return Parent item of input item                                              |  
 | < @Param item        : pointer to constant item to get data                                          |                  
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const menueItem_t * getmenuParent(const menueItem_t *item) {
#if COMPILER_TYPE == GCC
    return (const menueItem_t *) pgm_read_word(&item->menuParent); /*gcc-compiler*/
#elif  COMPILER_TYPE == XC
    return (const menueItem_t *) (item->menuParent); /*xc-compiler*/
#endif
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getmenuChlid >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getmenuChlid                                                            |
 | < @Description       : return Parent item of input item                                              |
 | < @Param item        : pointer to constant item to get data                                          |                   
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const menueItem_t * getmenuChlid(const menueItem_t *item) {
#if COMPILER_TYPE == GCC
    return (const menueItem_t *) pgm_read_word(&item->menuChild); /*gcc-compiler*/
#elif  COMPILER_TYPE == XC
    return (const menueItem_t *) (item->menuChild); /*xc-compiler*/
#endif
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <showMenueItem >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getmenuChlid                                                            |
 | < @Description       : assign current item by input item                                             |
 | < @Param item        : pointer to constant item to be as a current item                              |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void showMenueItem(const menueItem_t *item) {
    if (item && item != &NullItem) { /*pointer != Null  and  pointer to point a null item*/
        gpCurrentMenuItem = item;
        gu8OPenMenueFlag.b1 = 1;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <menuEvent >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   menuItemAction                                                         |
 | < @Description       : call back exeucation of the current item                                      |                 
 | < @return            : call back state 0 is call back runing and 1 call back done                    |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t menuItemAction() {
    pFuncMenueCallBack_t callback;
    if (gpCurrentMenuItem && gpCurrentMenuItem != &NullItem) {
#if COMPILER_TYPE == GCC
        callback = (pFuncMenueCallBack_t) pgm_read_word(&gpCurrentMenuItem->menuCallback); /*gcc-compiler*/
#elif COMPILER_TYPE == XC
        callback = (pFuncMenueCallBack_t) (gpCurrentMenuItem->menuCallback);
#endif
        if (callback) {
            if ((*callback)()) {
                lcdNoBlink(); /*close any lcd blink at any position*/
                if (getmenuParent(getmenuParent(gpCurrentMenuItem)) != &NullItem) {
                    showMenueItem(getmenuParent(gpCurrentMenuItem)); /*show parent of the current event with chlid*/
                } else {
                    showMenueItem(gpCurrentMenuItem);
                }
                return (1);
            }
        } else {
            if (getmenuChlid(gpCurrentMenuItem) && getmenuChlid(gpCurrentMenuItem) != &NullItem) {
                showMenueItem(getmenuChlid(gpCurrentMenuItem));
            }
            return (1);
        }
    }
    return (0);
}

/*
 --------------------------------------------+------------------------------------------------------------
 |                                 <menuAction >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   menuAction                                                             |
 | < @Description       : run with event enter                                                          |                 
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void menuAction() {
    if (menuItemAction()) {

        MenuRegisterKey(1); /*set all register */
        /*menu action done*/
        gu8OPenMenueFlag.b0 = 0;

    }
}

#if LCD_NUMBER_OF_LINE >2

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getItemInfo >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : menuItemInfo_t   getItemInfo                                                  |
 | < @Description       : get item position from item list                                              |    
 | < @Param item        : pointer to constant item                                                      |             
 | < @return            : item information ( number of item in list and item position in list          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static menuItemInfo_t getItemInfo(const menueItem_t *item) {
    menuItemInfo_t res;
    res.position = 0;
    res.ItemsCount = 0;
    const menueItem_t *i = getmenuChlid(getmenuParent(item));
    for (; i && i != &NullItem; i = getmenuNext(i)) {
        if (item == i) {
            res.position = res.ItemsCount;
        }
        res.ItemsCount++;
        if (i->menuNext == getmenuChlid(getmenuParent(i))) {
            break;
        }
    }
    return res;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <menuLCDChild >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   menuLCDChild                                                           |
 | < @Description       : lcd write data of the items per pos                                           |    
 | < @Param item        : pointer to constant item                                                      |
 | < @Param line        : item pos in lcd line 0or 1 , ...,max lines                                    |
 | < @Param pos         : item start char pos in lcd line 0 ,1,..., number of char per line             |             
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void menuLCDChild(const menueItem_t *item, uint8_t line, uint8_t pos) {
    /*upgrade*/
#if COMPILER_TYPE == GCC
    uint8_t len;
    const char * PROGMEM ScurrentItem = getmenuLable(item);
    len = strlen_P(ScurrentItem);
    char s[len];
    strcpy_P(s, ScurrentItem);
    lcdwrite(line, pos, s);

#elif COMPILER_TYPE == XC
    const char * ScurrentItem = getmenuLable(item);
    lcdwrite(line, pos, ScurrentItem);
#endif

}
#endif

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <menuLCDReader >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   menuLCDReader                                                          |
 | < @Description       : lcd write data of the items and parent                                        |                
 | < @return            : void                                                          |                                                          
 --------------------------------------------------------------------------------------------------------
 */
static void menuLCDReader() {
    /*in gcc compiler copy string form program memory to sram*/


    if (gpCurrentMenuItem && gpCurrentMenuItem == &NullItem) {
        return; /*no - item select*/
    }
    lcdClear();
#if COMPILER_TYPE == GCC
    /*copy to ram location and return pointer to string*/
    PGM_P  Sparent = (getmenuLable(getmenuParent(gpCurrentMenuItem))) + 2;
    lcdWriteString(0, Sparent);
    // lcdwrite(0, , s);
#if LCD_NUMBER_OF_LINE >2
    menuItemPos();
#else
    PGM_P  lable = getmenuLable(gpCurrentMenuItem);
    lcdWriteromFlash(1, 0, (PGM_P const *) lable);
    lcdUpdateNow();
#endif

#elif COMPILER_TYPE == XC
    /*copy to ram location and return pointer to string*/
    const char * Sparent = (getmenuLable(getmenuParent(gpCurrentMenuItem))) + 2;
    lcdwrite(0, LCD_TEXT_CENTER, Sparent);
#if LCD_NUMBER_OF_LINE >2
    menuItemPos();
#else
    const char * lable = getmenuLable(gpCurrentMenuItem);
    lcdwrite(1, 0, lable); /*update lcd */
#endif

#endif
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <menueEnterEvent >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   menueEnterEvent                                                        |
 | < @Description       : action when set Enter Event                                                   |                
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t menueEnterEvent(stkey_t *key) {
    if (key->State == KEY_PRESS) {
        gu8OPenMenueFlag.b0 = 1; /*menu action update*/
        MenuRegisterKey(0); /*Remove all register */
    }
    KeypadResetTabCounter(key, 1);
    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <menueCencelEvent >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   menueCencelEvent                                                       |
 | < @Description       : action when set Cencel Event                                                  |                
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t menueCencelEvent(stkey_t *key) {
    if (key->State == KEY_PRESS) {
        if (getmenuParent(getmenuParent(gpCurrentMenuItem)) == &NullItem) {
            gpCurrentMenuItem = &NullItem;
            lcdClear();
            /*close menu and clear all data */
            gu8OPenMenueFlag.b0 = 0; /*clear all actions*/
            gu8OPenMenueFlag.b2 = 0; /*close menu flag */
            gu8OPenMenueFlag.b1 = 0; /*clear any update*/
            lcdNoBlink(); /*close any lcd blink at any position*/
            lcdUpdateNow();
            MenuRegisterKey(0); /*Remove all register */
            /*assignment*/
            return (1);
        }

        lcdNoBlink(); /*close any blink*/
        showMenueItem(getmenuParent(gpCurrentMenuItem)); /*show parent of the current event with chlid*/
    }
    KeypadResetTabCounter(key, 1);
    return (1);

}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <menueUpEvent >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   menueUpEvent                                                           |
 | < @Description       : action when set Up Event                                                      |                
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t menueUpEvent(stkey_t *key) {

    if (key->State == KEY_PRESS) {
        showMenueItem(getmenuNext(gpCurrentMenuItem));
        gu8OPenMenueFlag.b1 = 1; /*menu show data update*/

    }
    KeypadResetTabCounter(key, 1);
    return (1);

}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <MenuRegisterKey >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   MenuRegisterKey                                                        |
 | < @Description       : Menu Event Register                                                           |  
 | < @Param type        : type 0 is remove all Register data   , one is register all data               |
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void MenuRegisterKey(uint8_t type) {
    if (type) {
        KeypadRegisterEvent(menueEnterEvent, ENTERKEY_INDEX);
        KeypadRegisterEvent(menueCencelEvent, CENCELKEY_INDEX);
        KeypadRegisterEvent(menueUpEvent, UPKEY_INDEX);
        KeypadRegisterEvent(menueDownEventEvent, DOWNKEY_INDEX);
    } else {
        KeypadRegisterEvent(NULL, ENTERKEY_INDEX);
        KeypadRegisterEvent(NULL, CENCELKEY_INDEX);
        KeypadRegisterEvent(NULL, UPKEY_INDEX);
        KeypadRegisterEvent(NULL, DOWNKEY_INDEX);
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <menueDownEventEvent >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   menueDownEventEvent                                                    |
 | < @Description       : action when set DownEvents Event                                              |                
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t menueDownEventEvent(stkey_t *key) {
    if (key->State == KEY_PRESS) {
        showMenueItem(getmenuPrev(gpCurrentMenuItem));
        gu8OPenMenueFlag.b1 = 1; /*menu show data update*/
    }
    KeypadResetTabCounter(key, 1);
    return (1);
}


/*
 --------------------------------------------------------------------------------------------------------
 |                           < user Function Implementions >                                            | 
 --------------------------------------------------------------------------------------------------------
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
void MenuInit() {
    gpCurrentMenuItem = &NullItem;
    gu8OPenMenueFlag.byte = 0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < menueDriver >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  menueDriver                                                             |
 | < @Description       : run in background task at open menu                                           |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void menueDriver() {
    if (!gu8OPenMenueFlag.b2)
        return;
    /*register callbacks with Index*/
    if (gu8OPenMenueFlag.b0) {
        menuAction();
        return;
    }
    if (gu8OPenMenueFlag.b1 && (!lcdIsBusy())) {
        menuLCDReader();
        lcdUpdateNow();
        gu8OPenMenueFlag.b1 = 0;
        return;
    }


}

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
uint8_t menuIsOpen() {
    return gu8OPenMenueFlag.b2;
}

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
void menuStart(const menueItem_t *item) {
    showMenueItem(item); /*register first item in menu*/
    menuAction(); /*first event */
    gu8OPenMenueFlag.b2 = 1; /*start menu*/
    /*Register callback from keyIndexs*/
    MenuRegisterKey(1);
}



#endif
#endif


