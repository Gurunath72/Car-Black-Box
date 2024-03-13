#include <xc.h>
#include "clcd.h"
#include "digital_keypad.h"
#include "ds1307.h"
#include "adc.h"
#include "dashboard.h"
#include "i2c.h"
#include "ext_eeprom.h"

unsigned char *events[9] = {"ON","GN","GR","G1","G2","G3","G4","G5","C "};
unsigned char clock_reg[3];
unsigned char time[9];
unsigned char speed[4];
signed int event_count= -1,event_10 = -1;

unsigned char no_event = 1;

void dashboard(unsigned char event_key)
{
    //clear_clcd();
    clcd_print(" TIME     E  SP",LINE1(0));
    static unsigned char i = 0;
    get_time(clock_reg);
    display_time(clock_reg);
    unsigned short int reg = read_adc()/10.23;
    
    
    for(int j=2; j>=0; j--)
    {
        speed[j] = reg%10 + '0';
        reg = reg / 10;
    }
    speed[3] = '\0';
    if(event_key == SW1)
    {
        i = 8;
        if(no_event)
        {
            no_event = 0;
        }
        if(event_count < 10)
        {
            event_count++;
            if(event_count == 10)
            {
                event_count = 0;
            }
        }
        if(event_10 < 9)
        {
            event_10++;
        }
        
        write_event_log(i);
    }
    else if(event_key == SW2 && i<7)
    {
        i++;
        if(no_event)
        {
            no_event = 0;
        }
        if(event_count < 10)
        {
            event_count++;
            if(event_count == 10)
            {
                event_count = 0;
            }
        }
        if(event_10 < 9)
        {
            event_10++;
        }
        write_event_log(i);
        
    }
    else if(event_key == SW3 && i>0)
    {
        i--;
        if(no_event)
        {
            no_event = 0;
        }
        if(event_count < 10)
        {
            event_count++;
            if(event_count == 10)
            {
                event_count = 0;
            }
        }
        if(event_10 < 9)
        {
            event_10++;
        }
        write_event_log(i);
    }
    clcd_print(events[i],LINE2(10));
    clcd_print(speed,LINE2(13));    
}

static void display_time(unsigned char *clock_reg)
{
    //BCD Format 
    //clock_reg[0] = HH
    //clock_reg[1] = MM
    //clock_reg[2] = SS
   
    /* To store the time in HH:MM:SS format */
      // "HH:MM:SS"
    // HH -> 
    time[0] = ((clock_reg[0] >> 4) & 0x03) + '0';
    time[1] = (clock_reg[0] & 0x0F) + '0';
    
    time[2] = ':';
    // MM 
    time[3] = ((clock_reg[1] >> 4) & 0x07) + '0';
    time[4] = (clock_reg[1] & 0x0F) + '0';
    
    time[5] = ':';
    // SS
    time[6] = ((clock_reg[2] >> 4) & 0x07) + '0';
    time[7] = (clock_reg[2] & 0x0F) + '0';
    time[8] = '\0';
    
    clcd_print(time, LINE2(1)); // HH:MM:SS 
}

static void get_time(unsigned char *clock_reg)
{
    clock_reg[0] = read_ds1307(HOUR_ADDR); // HH -> BCD 
    clock_reg[1] = read_ds1307(MIN_ADDR); // MM -> BCD 
    clock_reg[2] = read_ds1307(SEC_ADDR); // SS -> BCD 
}