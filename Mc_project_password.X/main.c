/*
 * File:   main.c
 * Author: Dell
 *
 * Created on 15 October, 2023, 5:43 PM
 */


#include <xc.h>

#include "clcd.h"
#include "ext_eeprom.h"
#include "i2c.h"
#pragma config WDTE = OFF //Watchdog timer disabled

static void init_config(void) {
    //Write your initialization code here
    init_clcd();
    init_i2c(100000);
    
}

void main(void) {

    init_config(); //call initialization function
    unsigned char user_passwd[5] ="1010";
    unsigned char test_psswd[5] = {'\0'};
    unsigned char *str = user_passwd;
    while(1){
        for(unsigned char i=150; i<154; i++)
        {
            ext_eeprom_write(i,*str++);
        }
        for(unsigned char i=150; i<154; i++)
        {
            test_psswd[i] = ext_eeprom_read(i);
        }
        clcd_print(test_psswd,LINE2(3));
        //__delay_ms(1000);
        str = user_passwd;
        
    }

}
