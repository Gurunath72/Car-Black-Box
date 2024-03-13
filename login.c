#include "clcd.h"
#include "digital_keypad.h"
#include "main.h"
#include <xc.h>
#include "ext_eeprom.h"
extern unsigned char pwd_success;
unsigned char timer_flag = 0;
unsigned long int count2;
extern unsigned char dash_flag;
static unsigned char password[5] ;
static unsigned char passwd_reset = 0;
unsigned char passwd_read=1;
void login(void)
{      
     
    static unsigned char blink_flag = 1;
    static unsigned char passwd_flag = 0;
    
    static unsigned char user[5] = {'\0'};
    static unsigned char blink_pos = 3;
    static unsigned int index = 0;
    static unsigned int total_attempt = 3;
    static unsigned int no_attempt_left = 3, attempt = 0;
    static unsigned int wait = 0;
    if(!passwd_flag && !passwd_reset)
    {
        passwd_flag = 1;
        passwd_reset = 1;
        eeprom_write(0x00,'1');
        eeprom_write(0x01,'0');
        eeprom_write(0x02,'1');
        eeprom_write(0x03,'0');
    }
    if(passwd_read )
    {
        passwd_read = 0;
        for(unsigned char i=0; i<4; i++)
        {
            password[i] = eeprom_read(i);
        }
        clcd_print(password,LINE2(2));
        __delay_ms(1000);
        clear_clcd();
    }
    if(!timer_flag )
    {        
    unsigned char key = read_digital_keypad(STATE);
    clcd_print(" Enter Password ",LINE1(0));
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
       blink_pos = 3;
       index = 0;
       no_attempt_left--;
       attempt++;
       if(my_strcmp(user,password) == 0)
       {
           pwd_success = 1;
           clear_clcd();
           //clcd_print(" login success ",LINE1(0));
           
           //while(1);
       }
       else
       {
           clear_arr(user);
           clear_clcd();
           clcd_print("attempts left ",LINE1(0));
           clcd_putch(no_attempt_left+48 ,LINE2(2));
           __delay_ms(1000);
           //for(unsigned int i= 10000; i--;)
           clear_clcd();
           if(no_attempt_left == 0)
           {
               //clcd_print(" user blocked ",LINE1(0));
               timer_flag = 1;
               clear_clcd();
               
               //while(1);
               
           }
       }
    }
    }
    else
    {
        
        clcd_print("Re Enter Passwd ",LINE1(0));
        clcd_print("Wait for ",LINE2(0));
        if(count2 == 180)
        {
            count2 = 0;
            timer_flag = 0;
            no_attempt_left = 3;
            attempt = 0;
            clear_clcd();
            
        }
        else
        {
            
            print_sec((unsigned)180 - count2);
        }
    }
}   

void clear_arr(unsigned char *arr)
{
    while(*arr)
    {
        *arr = '\0';
        arr++;
    }
}

int my_strcmp(unsigned char *str1, unsigned char *str2)
{
    while(*str1 && *str2 && *str1 == *str2)
    {
        str1++;
        str2++;
    }
    if(*str1 == *str2)
    {
        return 0;
    }
    return *str1 - *str2 ;
}

void print_sec(unsigned long int count)
{
    unsigned char pos = 9;
    unsigned char sec[4] = {'\0'};
    for(int i=2;i>=0 ; i--)
    {
        sec[i] = (count%10)+48;
        count /= 10;
    }
    clcd_print(sec,LINE2(pos));
    clcd_print(" sec",LINE2(12));
}
