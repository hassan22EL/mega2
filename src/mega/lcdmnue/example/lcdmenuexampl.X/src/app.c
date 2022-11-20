/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : app.c                                                                    |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no- ref                                                                  |  
| < SRAM USAGE               : 1-Byte                                                                   |
| < PROGRAM USAGE            : 464 Byte  (232 Instruction)                                              |                                    
| < Hardware Usage           : no-used                                                                  |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */

#include "../inc/app.h"
#if defined LCDMNUE_MODULE
#if LCDMNUE_MODULE






MenuItem(Menu, NullItem, NullItem, NullItem, User, NULL, Menu_Lable, "0.SYSTEM MENU");
MenuItem(User, System, System, Menu, Time, NULL, User_Lable, "1.USER");
MenuItem(System, User, User, Menu, NetWork, NULL, System_Lable, "2.System");

//test 1
MenuItem(Time, Date, Reset, User, NullItem, NULL, Time_Lable, "1.Time");
MenuItem(Date, Report, Time, User, NullItem, NULL, Date_Lable, "2.Date");
MenuItem(Report, Summary, Date, User, NullItem, NULL, Report_Lable, "3.Reports");
MenuItem(Summary, Reset, Report, User, NullItem, NULL, Summary_Lable, "4.Summary");
MenuItem(Reset, Time, Summary, User, NullItem, NULL, Reset_Lable, "5.Reset Data");


MenuItem(NetWork, Points, ResetSystem, System, TestNetWork, NULL, NetWork_Lable, "1.Network");
MenuItem(Points, Zones, NetWork, System, NullItem, NULL, Points_lable, "2.Points");
MenuItem(Zones, ResetSystem, Points, System, NullItem, NULL, Zones_lable, "3.Zones");
MenuItem(ResetSystem, NetWork, Zones, System, ResetData, NULL, ResetSystem_Lable, "4.Reset");
//network
MenuItem(TestNetWork, RepNetwork, RepNetwork, NetWork, NullItem, NULL, TestNetWork_Lable, "1.Test Network ");
MenuItem(RepNetwork, TestNetWork, TestNetWork, NetWork, NullItem, NULL, RepNetwork_Lable, "2.Rep Network ");
//Reset
MenuItem(ResetData, EraseData, EraseZone, ResetSystem, NullItem, NULL, ResetData_Lable, "1.Reset Data");
MenuItem(EraseData, EraseZone, ResetData, ResetSystem, NullItem, NULL, EraseData_Lable, "2.Erase Data");
MenuItem(EraseZone, ResetData, EraseData, ResetSystem, NullItem, NULL, EraseZone_Lable, "3.Erase zone");

volatile uint8_t appState;
#endif
#endif

void appBoot(void) {

}

void appInit(void) {

}

void appSync(void) {

}

void appMain(void) {
#if defined LCDMNUE_MODULE
#if LCDMNUE_MODULE
    switch (appState) {
        case 0:
            menuStart(&Menu);
            appState = 1;
            break;
        case 1:
            if (!menuIsOpen()) {
                appState = 2;
            }
            break;
        case 2:
            break;
    }

#endif
#endif
}


/*test*/

