#include <xc.h>
#include "digital_keypad.h"
#include "main.h"

extern unsigned char pwd_success = 0;
extern unsigned char dash_flag = 1;
unsigned char *menu[5] = {"view log","download log","clear log","set time","change passwd"};
void menu(void)
{
    static unsigned char key ,long_press1=0,long_press2 = 0;
    static unsigned char menu_select = 0;
    static unsigned char up=0, down = 0;
    static unsigned int dkp4_press = 0,dkp5_press = 0;
    key = read_digital_keypad(LEVEL);
    if(key == SW4 )
    {
        dkp4_press++;
        long_press1 = 0;
    }
    else if(key == ALL_RELEASED && !long_press1)
    {
        long_press1 = 1;
        if(dkp4_press < 100)
        {
            dkp4_press = 0;
            if(menu_select > 0)
            {
                menu_select--;
            }
        }
        /*else
        {
         * dkp4_press = 0;
            switch(menu_select)
            {
                case 0 :
                case 1 :
                case 2 :
                case 3 :
                case 4 :
                case 5 :    
            }
        }*/
    }
    if(key == SW5 )
    {
        dkp5_press++;
        long_press2 = 0;
    }
    else if(key == ALL_RELEASED && !long_press2)
    {
        long_press2 = 1;
        if(dkp5_press < 100)
        {
            dkp5_press = 0;
            if(menu_select < )
            {
                menu_select--;
            }
        }
        else
        {
           dkp5_press = 0;
           pwd_success = 0;
           dash_flag = 1;
        }
    }
}
