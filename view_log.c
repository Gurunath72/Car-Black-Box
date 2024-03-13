#include <xc.h>
#include "clcd.h"
#include "digital_keypad.h"
#include "i2c.h"
#include "ext_eeprom.h"
#include "main.h"


extern unsigned char pwd_success;
extern unsigned char dash_flag ;
extern unsigned char clear;
unsigned char view_log[16] = {'\0'},ind=0;
extern signed int event_count; 
extern signed int event_10;
extern unsigned char no_event;


void view_logs(void)
{
    static unsigned char log_no = 0;
    static unsigned char log_key;
    static unsigned char long_press1 = 1, long_press2 = 1;
    static unsigned char press4 = 0, press5 = 0;
    while(1)
    {
        log_key = read_digital_keypad(LEVEL);
        if(no_event)
        {
            clear_clcd();
            clcd_print(" NO EVENTS ",LINE1(0));
            __delay_ms(1000);
            clear_clcd();
            return;
        }
        else
        {
            if(log_key == SW4)
            {
                press4++;
                long_press1 = 0;
            }
            else if(log_key == ALL_RELEASED && !long_press1)
            {
                long_press1 = 1;
                if(press4 < 10)
                {
                    press4 = 0;
                    if(log_no > 0)
                    {
                        log_no--;
                        clear_clcd();                               
                    }
                }
            }
            if(log_key == SW5 )
            {
                press5++;
                long_press2 = 0;
            }
            else if(log_key == ALL_RELEASED && !long_press2)
            {
                long_press2 = 1;
                if(press5 < 10)
                {
                    press5 = 0;
                    if(log_no <= event_10 )
                    {
                        log_no++;
                        if(log_no == event_10+1)
                        {
                            log_no = 0;
                           
                        }
                        clear_clcd();
                    }
                    
                }
                else
                {
                    press5 = 0;
                    log_no = 0;
                    clear_clcd();
                    return;
                }
            }
            view_log_events(log_no);
        }
    }
}

static void view_log_events(unsigned char log_no)
{
    ind = 0;
    for(unsigned int i = log_no*15; i<((log_no+1)*15);i++)
    {
        view_log[ind++] = ext_eeprom_read(i);
    }
    clcd_putch('#',LINE1(0));
    clcd_putch(log_no+48,LINE2(0));
    clcd_print("  TIME    E  SP",LINE1(1));
    
    clcd_print(view_log,LINE2(2));
}


