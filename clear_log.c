#include <xc.h>
#include "main.h"
#include "clcd.h"

unsigned char clear = 0;
extern signed int event_count,event_10 ;
extern unsigned char no_event ;
void clear_log(void)
{
    event_count = -1;
    event_10 = -1;
    no_event = 1;
    clear_clcd();
    clcd_print("  logs cleared  ",LINE1(0));
    clcd_print("  successfully  ",LINE2(0));
    __delay_ms(2000);
    clear_clcd();
}
