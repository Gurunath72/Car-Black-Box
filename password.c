#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "digital_keypad.h"

extern unsigned char password[5];
extern unsigned char passwd_read;
void change_psswd(void)
{
    unsigned char blink_flag = 1,confirm_flag = 0;
    unsigned char key;
    unsigned char user[5] = {'\0'};
    unsigned char confirm[5] = {'\0'};
    unsigned char blink_pos = 0;
    unsigned int index = 0;
    unsigned int total_attempt = 3;
    unsigned int no_attempt_left = 3, attempt = 0;
    unsigned int wait = 0,wait2=0;
    clear_clcd();
    while(1)
    {
        key = read_digital_keypad(STATE);
        if(!confirm_flag)
        {
        clcd_print("Enter new Passwd",LINE1(0));
        if(++wait == 5)
        {
            wait = 0;
            if(blink_flag == 1)
            {
                clcd_putch(' ',LINE2(blink_pos));
                blink_flag = 0;
            }
            else if(blink_flag == 0)
            {
                clcd_putch(0xFF,LINE2(blink_pos));
                blink_flag = 1;
            }
            else
            {
                blink_flag = 2;
                clcd_putch(' ',LINE2(blink_pos));
            }
        }
        if(key == SW4)
        {
            if(index < 4)
            {
                user[index] = '0';
                clcd_putch('*',LINE2(blink_pos));
                index++;
                blink_pos++;
            }
        }
        else if(key == SW5)
        {
            if(index < 4)
            {
                user[index] = '1';
                clcd_putch('*',LINE2(blink_pos));
                index++;
                blink_pos++;
            }
        
        }
        if(index > 3)
        {
            blink_pos = 0;
            index = 0;
            confirm_flag = 1;
            clear_clcd();
        }
        }
        else
        {
            
            clcd_print("Confrm new Paswd",LINE1(0));
            if(++wait == 5)
            {
                wait = 0;
                if(blink_flag == 1)
                {
                    clcd_putch(' ',LINE2(blink_pos));
                    blink_flag = 0;
                }
                else if(blink_flag == 0)
                {
                    clcd_putch(0xFF,LINE2(blink_pos));
                    blink_flag = 1;
                }
                else
                {
                    blink_flag = 2;
                    clcd_putch(' ',LINE2(blink_pos));
                }
            }
            if(key == SW4)
            {
                if(index < 4)
                {
                    confirm[index] = '0';
                    clcd_putch('*',LINE2(blink_pos));
                    index++;
                    blink_pos++;
                }
            }
            else if(key == SW5)
            {
                if(index < 4)
                {
                    confirm[index] = '1';
                    clcd_putch('*',LINE2(blink_pos));
                    index++;
                    blink_pos++;
                }
        
            }
            if(index > 3)
            {
                blink_pos = 0;
                index = 0;
                confirm_flag = 0;
            
            if(my_strcmp(user,confirm) == 0)
            {              
                write_password(user);
                passwd_read=1;
                clear_clcd();
                clcd_print("Password changed",LINE1(0));
                clcd_print("  Succesfully  ",LINE2(0));
                __delay_ms(1000);
                clear_clcd();
                return;                
            }
            else
            {
                clear_arr(user);
                clear_arr(confirm);
                clear_clcd();
                clcd_print("wrong password",LINE1(0));
                clcd_print("  try again  ",LINE2(0));
                __delay_ms(1000);               
                clear_clcd();
            }
            }
        }
    }
    
}

void write_password(unsigned char *str)
{
    for(unsigned char ind = 0; ind < 4; ind++)
    {
        eeprom_write(ind,*str++);
    }
}


