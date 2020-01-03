#define __display_c
#include "includeAll.h"


void smg_control(int num,int smg)
{
 
    
    tempKeyValue5 = P1_4;
    tempKeyValue4 = P1_2;

    
        P_smga = 0;
        P_smgb = 0;
        P_smgc = 0;
        P_smgd = 0;
        P_smge = 0;
        P_smgf = 0;
        P_smgg = 0;
        P_smgdg = 0;
    F_ledOff();
    if(smg == 1)
    {
        P_smgcon1 = 0;
        P_smgcon2 = 1;
    }
    if(smg == 2)
    {
        P_smgcon1 = 1;
        P_smgcon2 = 0;
    }
 

    if(num == 0)
    {
        P_smga = 1;
        P_smgb = 1;
        P_smgc = 1;
        P_smgd = 1;
        P_smge = 1;
        P_smgf = 1;
        P_smgg = 0;
        P_smgdg = 1;
    }
    if(num == 1)
    {
        P_smga = 0;
        P_smgb = 1;
        P_smgc = 1;
        P_smgd = 0;
        P_smge = 0;
        P_smgf = 0;
        P_smgg = 0;
        P_smgdg = 1;
    }
    if(num == 2)
    {
        P_smga = 1;
        P_smgb = 1;
        P_smgc = 0;
        P_smgd = 1;
        P_smge = 1;
        P_smgf = 0;
        P_smgg = 1;
        P_smgdg = 1;
    }
    if(num == 3)
    {
        P_smga = 1;
        P_smgb = 1;
        P_smgc = 1;
        P_smgd = 1;
        P_smge = 0;
        P_smgf = 0;
        P_smgg = 1;
        P_smgdg = 1;
    }
        if(num == 4)
    {
        P_smga = 0;
        P_smgb = 1;
        P_smgc = 1;
        P_smgd = 0;
        P_smge = 0;
        P_smgf = 1;
        P_smgg = 1;
        P_smgdg = 1;
    }
        if(num == 5)
    {
        P_smga = 1;
        P_smgb = 0;
        P_smgc = 1;
        P_smgd = 1;
        P_smge = 0;
        P_smgf = 1;
        P_smgg = 1;
        P_smgdg = 1;
    }
        if(num == 6)
    {
        P_smga = 1;
        P_smgb = 0;
        P_smgc = 1;
        P_smgd = 1;
        P_smge = 1;
        P_smgf = 1;
        P_smgg = 1;
        P_smgdg = 1;
    }
        if(num == 7)
    {
        P_smga = 1;
        P_smgb = 1;
        P_smgc = 1;
        P_smgd = 0;
        P_smge = 0;
        P_smgf = 1;
        P_smgg = 0;
        P_smgdg = 1;
    }
        if(num == 8)
    {
        P_smga = 1;
        P_smgb = 1;
        P_smgc = 1;
        P_smgd = 1;
        P_smge = 1;
        P_smgf = 1;
        P_smgg = 1;
        P_smgdg = 1;
    }
        if(num == 9)
    {
        P_smga = 1;
        P_smgb = 1;
        P_smgc = 1;
        P_smgd = 0;
        P_smge = 0;
        P_smgf = 1;
        P_smgg = 1;
        P_smgdg = 1;
    }

    
    P_smgcon1 = 1;
    P_smgcon2 = 1;
    
        P_smga = 0;
        P_smgb = 0;
        P_smgc = 0;
        P_smgd = 0;
        P_smge = 0;
        P_smgf = 0;
        P_smgg = 0;
        P_smgdg = 0;

    P1_4 = tempKeyValue5;
    P1_2 = tempKeyValue4;
    F_ledOn();




}