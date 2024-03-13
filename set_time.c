#include "ds1307.h"
#include "i2c.h"
#include "clcd.h"
#include "main.h"
#include "digital_keypad.h"

extern unsigned char pwd_success;
extern unsigned char dash_flag ;
extern unsigned char menu_select;
extern unsigned char clock_reg[3];
extern unsigned char time[9];
unsigned char clock_write[3] = {0};
unsigned char set_time_flag = 0;

void set_time(void)
{
    clear_clcd();
    set_time_flag = 0;
    clcd_print("Time <HH:MM:SS> ",LINE1(0));
    clcd_print(time,LINE2(0));
    unsigned char time_key ;
    unsigned char long_press1=1,long_press2 =1;
    unsigned long int key_press1=0,key_press2=0;
    unsigned char blink[3] = "  ",blink_pos = 2;
    unsigned char time_field[3] = {'\0'};
    unsigned char flag = 1;
    unsigned long int wait = 0;
    unsigned int time_digit = 0;
    //time_field[0] =  time[3*blink_pos];
    //time_field[1] =  time[(3*blink_pos)+1];
    while(1)
    {
        time_key = read_digital_keypad(LEVEL);
        if(wait++ == 20000)
        {
            wait = 0;
            if(flag)
            {   
                //clcd_print(time_field,LINE2(3*blink_pos));
                clcd_print(time,LINE2(0));
                //clcd_print("        ",LINE2(8));
                flag = 0;                 
            }
            else
            {
                //clcd_print(time,LINE2(0));
                clcd_print(blink,LINE2(3*blink_pos));
                //clcd_print("        ",LINE2(8));
                flag = 1;
            }
        }
        if(time_key == SW4)
        {
            key_press1++;
            long_press1 = 0;
            //clcd_putch('p',LINE2(15));
        }
        else if(time_key == ALL_RELEASED && !long_press1)
        {
            long_press1 = 1;
            /*clcd_putch((key_press1/100)+48,LINE2(13));
            clcd_putch((key_press1/10)+48,LINE2(14));
            clcd_putch((key_press1%10)+48,LINE2(15));*/
            if(key_press1 < 15000)
            {
                key_press1 = 0;
                switch(blink_pos)
                {
                    case 0 :
                            time_digit = ((time[0]-48)*10)+(time[1]-48);
                            time_digit++;
                            if(time_digit == 24)
                            {
                                 time_digit = 0;
                            }
                            time[0] = (time_digit/10)+48;
                            time[1] = (time_digit%10)+48;
                            break;
                    case 1 : 
                            time_digit = ((time[3]-48)*10)+(time[4]-48);
                            time_digit++;
                            if(time_digit == 60)
                            {
                                 time_digit = 0;
                            }
                            time[3] = (time_digit/10)+48;
                            time[4] = (time_digit%10)+48;
                            break;
                    case 2 :
                            time_digit = ((time[6]-48)*10)+(time[7]-48);
                            time_digit++;
                            if(time_digit == 60)
                            {
                                 time_digit = 0;
                            }
                            time[6] = (time_digit/10)+48;
                            time[7] = (time_digit%10)+48;
                            break;
                }
            }
            else
            {
                key_press1 = 0;
                pwd_success = 0;
                dash_flag = 1;
                menu_select = 0;
                blink_pos = 2;
                clear_clcd();
                set_time_flag = 1;
                write_time_rtc();
                return;
            }
            
        }
        if(time_key == SW5)
        {
            key_press2++;
            long_press2 = 0;
        }
        else if(time_key == ALL_RELEASED && !long_press2)
        {
            long_press2 = 1;
            if(key_press2 < 15000)
            {
                
                blink_pos = (blink_pos+1)%3;
                //time_field[0] =  time[3*blink_pos];
                //time_field[1] =  time[(3*blink_pos)+1];
            }
            key_press2 = 0;
        } 
    }
    
}

void write_time_rtc(void)
{
    clock_write[0] = ((time[0]-48) & 0x03)<<4;
    clock_write[0] |= ((time[1]-48) & 0x0F);
    
    clock_write[1] = ((time[3]-48) & 0x07)<<4;
    clock_write[1] |= ((time[4]-48) & 0x0F);
    
    clock_write[2] = ((time[6]-48) & 0x07)<<4;
    clock_write[2] |= ((time[7]-48) & 0x0F);
    
    write_ds1307(SEC_ADDR,clock_write[2]);
    write_ds1307(MIN_ADDR,clock_write[1]);
    write_ds1307(HOUR_ADDR,clock_write[0]);
}
