/*
 * DS3231.c
 *
 * Created: 09.02.2020 17:04:12
 *  Author: nara_
 */ 

#include "DS3231.h"

void DS3231_write(uint8_t adr, uint8_t data){
	TWI_startTransmition(RTC_ADRES|0);
	TWI_write(adr);
	TWI_write(((data/10)<< 4) + data%10);
	TWI_stopTransmition();
}

uint8_t DS3231_read(uint8_t adr){
	uint8_t data;
	TWI_startTransmition(RTC_ADRES|0);
	TWI_write(adr);
	TWI_stopTransmition();
	TWI_startTransmition(RTC_ADRES|1);
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	data = TWDR;
	TWI_stopTransmition();
	if ((adr == TEMPUP) || (adr == TEMPLOW) )
	{
		return data;
	} 
	else
	{
		return (data >> 4)*10 + (data & 0x0F);
	}
}