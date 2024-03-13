/* 
 * File:   ext_eeprom.h
 * Author: Dell
 *
 * Created on 21 September, 2023, 2:21 PM
 */

#ifndef EXT_EEPROM_H
#define	EXT_EEPROM_H

#define SLAVE_WRITE_EEP 0xA0
#define SLAVE_READ_EEP 0xA1


static void ext_eeprom_write(unsigned char *event_log);
unsigned char ext_eeprom_read(unsigned char addr);
void write_event_log(unsigned char i);
static void write_time(unsigned char *clock_reg);
static void write_event(unsigned char *event);
static void write_speed(unsigned char *speed);

static void view_log_events(unsigned char log_no);
unsigned char ext_eeprom_read(unsigned char addr);



#endif	/* EXT_EEPROM_H */

