#include <xc.h>
#include "digital_keypad.h"
#include "main.h"
#include "clcd.h"

extern unsigned char pwd_success;
extern unsigned char passwd_read;
extern unsigned char dash_flag ;
unsigned char menu_select = 0;
extern unsigned char set_time_flag ;
unsigned char *option_menu[5] = {"view log","clear log","download log","set time","change passwd"};
void menu(void)
{
    //clcd_print("menu mode",LINE1(0));
    static unsigned char  scroll_key,long_press1=1,long_press2 = 1;
    
    //static unsigned char up=0, down = 0;
    static unsigned int dkp4_press = 0,dkp5_press = 0;
    scroll_key = read_digital_keypad(LEVEL); 
    if(scroll_key == SW4)
    {
        dkp4_press++;
        long_press1 = 0;
    }
    else if(scroll_key == ALL_RELEASED && !long_press1)
    {
        long_press1 = 1;
        if(dkp4_press < 20)
        {
            if(menu_select > 0)
            {
                menu_select--;
                clear_clcd();                               
            }
        }
        else
        {            
            switch(menu_select)
            {
                case 0 : view_logs();
                         break;
                case 1 : clear_log();
                         break;
                case 2 : download();
                         break;
                case 3 : set_time();
                         break;
                case 4 : change_psswd();
                         break;
                    
            }
            menu_select = 0;
        }
        dkp4_press = 0;
    }
    if(scroll_key == SW5 )
    {
        dkp5_press++;
        long_press2 = 0;
    }
    else if(scroll_key == ALL_RELEASED && !long_press2)
    {
        long_press2 = 1;
        if(dkp5_press < 50)
        {
            dkp5_press = 0;
            
            if(menu_select < 4 )
            {
                menu_select++;
                clear_clcd();
            }
        }
        else
        {
            dkp5_press = 0;
            passwd_read = 1;
            pwd_success = 0;
            dash_flag = 1;
            menu_select = 0;
            clear_clcd();
            return;
        }
        
    }
    display_menu(option_menu,menu_select);
    if(set_time_flag)
    {
        set_time_flag = 0;
        clear_clcd();
    }
    
}

static void display_menu(unsigned char *menu[5],unsigned char menu_select)
{
   // unsigned char pointer_pos = 0;
    if(menu_select == 4)
    {
        clcd_putch('*',LINE2(0));
        clcd_print(menu[menu_select-1],LINE1(2));
        clcd_print(menu[menu_select],LINE2(2));
    }
    else
    {
        clcd_putch('*',LINE1(0));
        clcd_print(menu[menu_select],LINE1(2));
        clcd_print(menu[menu_select+1],LINE2(2));
    }
}
