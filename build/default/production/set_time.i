# 1 "set_time.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.00/packs/Microchip/PIC16Fxxx_DFP/1.3.42/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "set_time.c" 2
# 1 "./ds1307.h" 1
# 16 "./ds1307.h"
void init_ds1307(void);
unsigned char read_ds1307(unsigned char addr);
void write_ds1307(unsigned char addr, unsigned char data);
# 1 "set_time.c" 2

# 1 "./i2c.h" 1
# 10 "./i2c.h"
void init_i2c(unsigned long baud);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
unsigned char i2c_read(unsigned char ack);
int i2c_write(unsigned char data);
# 2 "set_time.c" 2

# 1 "./clcd.h" 1
# 32 "./clcd.h"
void init_clcd(void);
void clcd_putch(const char data, unsigned char addr);
void clcd_print(const char *str, unsigned char addr);
void clear_clcd(void);
# 3 "set_time.c" 2

# 1 "./main.h" 1
# 12 "./main.h"
void init_timer(void);
void dashboard(unsigned char event_key);
void login(void);
void clear_arr(unsigned char *arr);
int my_strcmp(unsigned char *str1, unsigned char *str2);
void menu(void);
void view_logs(void);
void clear_log(void);
void download(void);
void set_time(void);
void change_psswd(void);
void write_password(unsigned char *str);
void write_time_rtc(void);
static void display_menu(unsigned char *menu[5],unsigned char menu_select);
void print_sec(unsigned long int count);
# 4 "set_time.c" 2

# 1 "./digital_keypad.h" 1
# 31 "./digital_keypad.h"
unsigned char read_digital_keypad(unsigned char mode);
void init_digital_keypad(void);
# 5 "set_time.c" 2


extern unsigned char pwd_success;
extern unsigned char dash_flag ;
extern unsigned char menu_select;
extern unsigned char clock_reg[3];
extern unsigned char time[9];
unsigned char clock_write[3] = {0};
unsigned char set_time_flag = 0;

void set_time(void)
{
    clear_clcd();
    set_time_flag = 0;
    clcd_print("Time <HH:MM:SS> ",(0x80 + 0));
    clcd_print(time,(0xC0 + 0));
    unsigned char time_key ;
    unsigned char long_press1=1,long_press2 =1;
    unsigned long int key_press1=0,key_press2=0;
    unsigned char blink[3] = "  ",blink_pos = 2;
    unsigned char time_field[3] = {'\0'};
    unsigned char flag = 1;
    unsigned long int wait = 0;
    unsigned int time_digit = 0;


    while(1)
    {
        time_key = read_digital_keypad(0);
        if(wait++ == 20000)
        {
            wait = 0;
            if(flag)
            {

                clcd_print(time,(0xC0 + 0));

                flag = 0;
            }
            else
            {

                clcd_print(blink,(0xC0 + 3*blink_pos));

                flag = 1;
            }
        }
        if(time_key == 0x37)
        {
            key_press1++;
            long_press1 = 0;

        }
        else if(time_key == 0x3F && !long_press1)
        {
            long_press1 = 1;



            if(key_press1 < 15000)
            {
                key_press1 = 0;
                switch(blink_pos)
                {
                    case 0 :
                            time_digit = ((time[0]-48)*10)+(time[1]-48);
                            time_digit++;
                            if(time_digit == 24)
                            {
                                 time_digit = 0;
                            }
                            time[0] = (time_digit/10)+48;
                            time[1] = (time_digit%10)+48;
                            break;
                    case 1 :
                            time_digit = ((time[3]-48)*10)+(time[4]-48);
                            time_digit++;
                            if(time_digit == 60)
                            {
                                 time_digit = 0;
                            }
                            time[3] = (time_digit/10)+48;
                            time[4] = (time_digit%10)+48;
                            break;
                    case 2 :
                            time_digit = ((time[6]-48)*10)+(time[7]-48);
                            time_digit++;
                            if(time_digit == 60)
                            {
                                 time_digit = 0;
                            }
                            time[6] = (time_digit/10)+48;
                            time[7] = (time_digit%10)+48;
                            break;
                }
            }
            else
            {
                key_press1 = 0;
                pwd_success = 0;
                dash_flag = 1;
                menu_select = 0;
                blink_pos = 2;
                clear_clcd();
                set_time_flag = 1;
                write_time_rtc();
                return;
            }

        }
        if(time_key == 0x2F)
        {
            key_press2++;
            long_press2 = 0;
        }
        else if(time_key == 0x3F && !long_press2)
        {
            long_press2 = 1;
            if(key_press2 < 15000)
            {

                blink_pos = (blink_pos+1)%3;


            }
            key_press2 = 0;
        }
    }

}

void write_time_rtc(void)
{
    clock_write[0] = ((time[0]-48) & 0x03)<<4;
    clock_write[0] |= ((time[1]-48) & 0x0F);

    clock_write[1] = ((time[3]-48) & 0x07)<<4;
    clock_write[1] |= ((time[4]-48) & 0x0F);

    clock_write[2] = ((time[6]-48) & 0x07)<<4;
    clock_write[2] |= ((time[7]-48) & 0x0F);

    write_ds1307(0x00,clock_write[2]);
    write_ds1307(0x01,clock_write[1]);
    write_ds1307(0x02,clock_write[0]);
}
