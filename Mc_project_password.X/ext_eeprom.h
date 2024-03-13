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


void ext_eeprom_write(unsigned char addr,unsigned char data);
unsigned char ext_eeprom_read(unsigned char addr);





#endif	/* EXT_EEPROM_H */

