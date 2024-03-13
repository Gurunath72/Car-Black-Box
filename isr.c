#include <xc.h>
#include "clcd.h"
#include "main.h"
extern unsigned char timer_flag;
extern unsigned long int count2;
void __interrupt() isr(void)
{
    static unsigned long int count = 0;
    if(TMR0IF == 1)
    {
        TMR0 += 8;
        if(timer_flag && ++count == 20000)
        {
            count = 0;
            if(count2 < 180)
            {
                
                
                //print_sec((unsigned long int)10 - count2);
                count2++;
            }
            
        }
        TMR0IF = 0;
    }
}
