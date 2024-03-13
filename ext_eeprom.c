#include <xc.h>
#include "i2c.h"
#include "ext_eeprom.h"

extern unsigned char *events[9] ;
extern unsigned char clock_reg[3];
extern unsigned char speed[4];

extern signed int event_count,event_10;
unsigned char event_log[15] = {'\0'};
unsigned char index = 0;

void write_event_log(unsigned char i)
{
    if(event_count >= 10)
    {
        event_count = 0;
    }
    write_time(clock_reg);
    event_log[index++] = ' ';
    write_event(events[i]);
    event_log[index++] = ' ';    
    write_speed(speed+1);
    ext_eeprom_write(event_log);
}

static void write_time(unsigned char *clock_reg)
{
    unsigned char time[9];
    event_log[0] = ((clock_reg[0] >> 4) & 0x03) + '0';
    event_log[1] = (clock_reg[0] & 0x0F) + '0';
    
    event_log[2] = ':';
    // MM 
    event_log[3] = ((clock_reg[1] >> 4) & 0x07) + '0';
    event_log[4] = (clock_reg[1] & 0x0F) + '0';
    
    event_log[5] = ':';
    // SS
    event_log[6] = ((clock_reg[2] >> 4) & 0x07) + '0';
    event_log[7] = (clock_reg[2] & 0x0F) + '0';
    index = 8;
    /*for(unsigned int index = 0; index <8; index++)
    {
        ext_eeprom_write(time[index],addr);
        addr++;
    }*/
}


static void write_event(unsigned char *event)
{
    while(*event)
    {
        event_log[index++] = *event++;
    }
}

static void write_speed(unsigned char *speed)
{
    while(*speed)
    {
        event_log[index++] = *speed++;
        
    }
}

static void ext_eeprom_write(unsigned char *event_log)
{
    for(unsigned char i = event_count *15; i < ((event_count+1)*15); i++ )
    {
        i2c_start();
        i2c_write(SLAVE_WRITE_EEP);
        i2c_write(i);
        i2c_write(*event_log++);
        i2c_stop();
    }
}

unsigned char ext_eeprom_read(unsigned char addr)
{
    unsigned char data;
    i2c_start();
    i2c_write(SLAVE_WRITE_EEP);
    i2c_write(addr);
    i2c_rep_start();
    i2c_write(SLAVE_READ_EEP);
    data = i2c_read(0);
    i2c_stop();
    return data;
}
