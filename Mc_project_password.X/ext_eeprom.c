#include <xc.h>
#include "i2c.h"
#include "ext_eeprom.h"



void ext_eeprom_write(unsigned char addr, unsigned char data)
{
    
        i2c_start();
        i2c_write(SLAVE_WRITE_EEP);
        i2c_write(addr);
        i2c_write(data);
        i2c_stop();
    
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
