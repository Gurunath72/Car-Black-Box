/* 
 * File:   dashboard.h
 * Author: Dell
 *
 * Created on 18 September, 2023, 5:46 PM
 */

#ifndef DASHBOARD_H
#define	DASHBOARD_H

void dashboard(unsigned char event_key);
static void display_time(unsigned char *clock_reg);
static void get_time(unsigned char *clock_reg);



#endif	/* DASHBOARD_H */

