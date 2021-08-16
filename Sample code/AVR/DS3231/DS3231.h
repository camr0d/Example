/*
 * DS3231.h
 *
 * Created: 09.02.2020 17:03:11
 *  Author: nara_
 */ 


#ifndef DS3231_H_
#define DS3231_H_

#define RTC_ADRES 0b11010000

#include "TWI.h"
#include <stdint.h>

#define SECOND 0x00
#define MINUTES 0x01
#define HOURS 0x02
#define DATE 0x04
#define MONTH 0x05
#define YEAR 0x06
#define TEMPUP 0x11
#define TEMPLOW 0x12

struct RTC{
	uint8_t s;							 // �������
	uint8_t m;							 // ������
	uint8_t h;							 // ����
};

struct calendar{
	uint8_t d;							 // ����
	uint8_t m;							 // �����
	uint8_t y;							 // ���
};

struct temp{
	uint8_t tempUpper;					// ����� ����� 
	uint8_t tempLower;					// ������� �����
};

void DS3231_write(uint8_t, uint8_t);	// ������ ������ adr, data
uint8_t DS3231_read(uint8_t);			// ������ ������	data



#endif /* DS3231_H_ */