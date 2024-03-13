/* 
 * File:   main.h
 * Author: Dell
 *
 * Created on 18 September, 2023, 5:45 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#define _XTALFREQ 20000000
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

#endif	/* MAIN_H */

