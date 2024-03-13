/*
 * File:   main.c
 * Author: Gurunath N
 * Project :- Car Black Box
 * Created on 17 September, 2023, 8:41 PM
 */


#include <xc.h>
#include "adc.h"
#include "clcd.h"
#include "digital_keypad.h"
#include "ds1307.h"
#include "i2c.h"
#include "main.h"
#include "uart.h"

#pragma config WDTE = OFF //Watchdog timer disabled

static void init_config(void) {
    //Write your initialization code here
    init_timer();
    init_adc();
    init_clcd();
    init_digital_keypad();
    init_i2c(100000);
    init_ds1307();
    init_uart(9600);
    GIE = 1;
    PEIE = 1;
}

unsigned char pwd_success = 0;
unsigned char dash_flag = 1;
void main(void) {

    init_config(); //call initialization function
    unsigned char key ;
    
    while (1) {
        //Write application code here
        if(dash_flag)
        {
            key = read_digital_keypad(STATE);
        }        
        if(key == SW4 && dash_flag)
        {
            clear_clcd();
            dash_flag = 0;
        }
        /*if(pwd_success)
        {
            key = read_digital_keypad(LEVEL);
        }*/
        switch(dash_flag)
        {
            case 1 : dashboard(key);
                     break;
            case 0 : 
                     if(pwd_success == 0)
                     {
                         login();
                     }
                     else if(pwd_success == 1)
                     {
                         menu();
                     }
                     break;
        }        
    }

}
