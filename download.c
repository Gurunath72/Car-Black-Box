#include <xc.h>
#include "main.h"
#include "uart.h"
#include "clcd.h"
#include "ext_eeprom.h"

static unsigned char download_log[17] = {'\0'},ind=0;
unsigned int addr = 0;
extern signed int event_count; 
extern signed int event_10;

void download(void)
{
    clear_clcd();
    clcd_print("logs print",LINE1(0));
    __delay_ms(500);
    clear_clcd();
    if(event_10 == -1)
    {
        puts("NO LOGS AVAILABLE\n");
        return;
    }
    for(unsigned int index = addr; index <= event_10; index++)
    {
        for(unsigned int i = index*15; i<((index+1)*15);i++)
        {
            download_log[ind++] = ext_eeprom_read(i);
        }
        //download_log[15] = '\n';
        //puts(download_log);
        
        puts("log 1\n");
        //clear_clcd();
        //clcd_print(download_log,LINE1(0));
        ind = 0;
        //__delay_ms(1000);
    }
    addr = 0;
    clear_clcd();
    return;
    //clear_clcd();
}

