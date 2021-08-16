
#include "oledSSD1306.h"
#include "font.h"

uint8_t y[128][8] = {0};

int8_t SSD1306_getAbs(int8_t x){
	if (x < 0) return -x;
	return x;
}

int8_t SSD1306_getSign(int8_t x){
	if(x < 0) return -1;
	if(x > 0) return 1;
	else return 0;
}


void SSD1306_init(void){
	TWI_startTransmition(OLED_ADRES);
	TWI_write(_SSD1306_SET_LOWER_COLUMN);
	TWI_write(_SSD1306_DISPLAY_OFF);
	TWI_write(_SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO);
	TWI_write(0x80);
	TWI_write(_SSD1306_SET_DISPLAY_OFFSET);
	TWI_write(_SSD1306_SET_LOWER_COLUMN);
	TWI_write(_SSD1306_SET_START_LINE);
	TWI_write(_SSD1306_CHARGE_PUMP);
	TWI_write(0x14);
	TWI_write(_SSD1306_MEMORY_ADDR_MODE);
	TWI_write(_SSD1306_SET_LOWER_COLUMN);
	TWI_write(0xA1);
	TWI_write(_SSD1306_COM_SCAN_DIR_DEC);
	TWI_write(_SSD1306_SET_COM_PINS);
	TWI_write(0x12);
	TWI_write(_SSD1306_SET_CONTRAST_CONTROL);
	TWI_write(0xCF);
	TWI_write(_SSD1306_SET_PRECHARGE_PERIOD);
	TWI_write(0xF1);
	TWI_write(0xD8);
	TWI_write(_SSD1306_SET_START_LINE);
	TWI_write(_SSD1306_DISPLAY_ALL_ON_RESUME);
	TWI_write(_SSD1306_NORMAL_DISPLAY);
	TWI_stopTransmition();
	SSD1306_cleer();
	SSD1306_com(_SSD1306_DISPLAY_ON);	
}

void SSD1306_com(int com){
	TWI_startTransmition(OLED_ADRES);
	TWI_write(0x00);
	TWI_write(com);
	TWI_stopTransmition();
}

void SSD1306_data(int data){
	TWI_startTransmition(OLED_ADRES);
	TWI_write(0x40);
	TWI_write(data);
	TWI_stopTransmition();
}



void SSD1306_cleer(){
	SSD1306_com(_SSD1306_SET_COLUMN_ADDR);
	SSD1306_com(0x00);
	SSD1306_com(0x7F);
	SSD1306_com(_SSD1306_SET_PAGE_ADDR);
	SSD1306_com(0x00);
	SSD1306_com(0x07);
	for(int i = 0; i < 1024; i++){
		SSD1306_data(0x00);
	}
	for(uint8_t i = 0 ; i < 128; i++)
	for (uint8_t j = 0; j < 8; j++)
	y[i][j] = 0;
}

void SSD1306_fill(void){
	SSD1306_com(_SSD1306_SET_COLUMN_ADDR);
	SSD1306_com(0x00);
	SSD1306_com(0x7F);
	SSD1306_com(_SSD1306_SET_PAGE_ADDR);
	SSD1306_com(0x00);
	SSD1306_com(0x07);
	for(int i = 0; i < 1024; i++){
		SSD1306_data(0xFF);
	}
	for(uint8_t i = 0 ; i < 128; i++)
	for (uint8_t j = 0; j < 8; j++)
	y[i][j] = 0xFF;
}

void SSD1306_drawPixel(uint8_t x1, uint8_t y1){
	if ((x1 >= 0) && (x1 < 128) && (y1 >= 0) && (y1 < 64))
	{
		y[x1][y1>>3] &= ~(1<<(y1&7));
		y[x1][y1>>3] |= (1<<(y1&7));
		SSD1306_com(_SSD1306_SET_COLUMN_ADDR);
		SSD1306_com(x1);
		SSD1306_com(x1);
		SSD1306_com(_SSD1306_SET_PAGE_ADDR);
		SSD1306_com(y1>>3);
		SSD1306_com(y1>>3);
		SSD1306_data(y[x1][y1>>3]);
	}
}

void SSD1306_invPixel(uint8_t x1, uint8_t y1){
	if ((x1 >= 0) && (x1 < 128) && (y1 >= 0) && (y1 < 64))
	{
		y[x1][y1>>3] &= ~(1<<(y1&7));
		SSD1306_com(0x21);
		SSD1306_com(x1);
		SSD1306_com(x1);
		SSD1306_com(0x22);
		SSD1306_com(y1>>3);
		SSD1306_com(y1>>3);
		SSD1306_data(y[x1][y1>>3]);
	}
}

void SSD1306_drawByte(uint8_t x1, uint8_t y1, uint8_t b){
	if ((x1 >= 0) && (x1 < 128) && (y1 >= 0) && (y1 <= 63))
	{
		if ((y1 & 0x07) == 0){
			y[x1][y1 >> 3] = b;
			SSD1306_com(0x21);
			SSD1306_com(x1);
			SSD1306_com(x1);
			SSD1306_com(0x22);
			SSD1306_com(y1 >> 3);
			SSD1306_com(y1 >> 3);
			SSD1306_data(y[x1][y1 >> 3]);
		} 
		else {
			uint8_t y0 = y1 & 0x07;
			uint8_t yc = 0;
			while (y0 < 8)
			{
				yc |= (1 << y0);
				y0++;
			}
			y[x1][y1 >> 3] &= ~yc;
			y[x1][(y1 >> 3) + 1] &= yc;
			/*y0 = 8 - (y1 & 0x07);
			yc = 0;
			while (y0 != 0)
			{
				y0--;
				yc |= (1 << y0);
			}*/
			yc = yc >> (y1 & 0x07);
			y[x1][y1 >> 3] |= (b & yc) << (y1 & 0x07);
			y[x1][(y1 >> 3) + 1] |= (b & (~yc)) >> (8 - (y1 & 0x07));
			for (uint8_t i0 = 0; i0 <=1; i0++)
			{
				SSD1306_com(0x21);
				SSD1306_com(x1);
				SSD1306_com(x1);
				SSD1306_com(0x22);
				SSD1306_com((y1 >> 3) + i0);
				SSD1306_com((y1 >> 3) + i0);
				SSD1306_data(y[x1][(y1 >> 3) + i0]);
			}
		}
	}
}

void SSD1306_drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	uint8_t dX = SSD1306_getAbs(x2 - x1);
	uint8_t dY = SSD1306_getAbs(y2 - y1);
	int8_t signX = SSD1306_getSign(x2 - x1);
	int8_t signY = SSD1306_getSign(y2 - y1);
	int16_t err = dX - dY;
	int16_t err2;
	while(1)
	{
		SSD1306_drawPixel(x1, y1);
		if(x1 == x2 && y1 == y2) break;
		err2 = err * 2;
		if(err2 > -dY)
		{
			err -= dY;
			x1 += signX;
		}
		if(err2 < dX)
		{
			err += dX;
			y1 += signY;
		}
	}	
}

void SSD1306_invLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	uint8_t dX = SSD1306_getAbs(x2 - x1);
	uint8_t dY = SSD1306_getAbs(y2 - y1);
	int8_t signX = SSD1306_getSign(x2 - x1);
	int8_t signY = SSD1306_getSign(y2 - y1);
	int16_t err = dX - dY;
	int16_t err2;
	while(1)
	{
		SSD1306_invPixel(x1, y1);
		if(x1 == x2 && y1 == y2) break;
		err2 = err * 2;
		if(err2 > -dY)
		{
			err -= dY;
			x1 += signX;
		}
		if(err2 < dX)
		{
			err += dX;
			y1 += signY;
		}
	}
}

void SSD1306_drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	SSD1306_drawLine(x1, y1, x2, y1);
	SSD1306_drawLine(x2, y1, x2, y2);
	SSD1306_drawLine(x2, y2, x1, y2);
	SSD1306_drawLine(x1, y2, x1, y1);
}

void SSD1306_invRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	SSD1306_invLine(x1, y1, x2, y1);
	SSD1306_invLine(x2, y1, x2, y2);
	SSD1306_invLine(x2, y2, x1, y2);
	SSD1306_invLine(x1, y2, x1, y1);
}


void SSD1306_printChar_5x8(uint8_t x1, uint8_t y1, char sim){
	if((sim >= 0x20) && (sim <= 0x7F)) sim -= 32;
	else  sim -= 96;
		
	for(uint8_t i = 0; i < 5; i++)
	{
		SSD1306_drawByte(x1 + i, y1, pgm_read_byte(&font_5x8[sim][i]));
	}
}

void SSD1306_printString_5x8(uint8_t x1, uint8_t y1, char *str) // 0..120 / 0..7 / Строка
{
	while(*str)
	{
		SSD1306_printChar_5x8(x1, y1, *str++);
		x1+=6;
	}
}

void SSD1306_drawCircle(uint8_t x0, uint8_t y0, uint8_t radius){
	uint8_t x1 = 0;
	int8_t y1 = radius;
	int16_t delta = 2 - 2 * radius;
	int16_t error = 0;
	while(y1 >= 0)
	{
		SSD1306_drawPixel(x0 + x1, y0 + y1);
		SSD1306_drawPixel(x0 + x1, y0 - y1);
		SSD1306_drawPixel(x0 - x1, y0 + y1);
		SSD1306_drawPixel(x0 - x1, y0 - y1);
		error = 2 * (delta + y1) - 1;
		if(delta < 0 && error <= 0)
		{
			++x1;
			delta += 2 * x1 + 1;
			continue;
		}
		error = 2 * (delta - x1) - 1;
		if(delta > 0 && error > 0)
		{
			--y1;
			delta += 1 - 2 * y1;
			continue;
		}
		++x1;
		delta += 2 * (x1 - y1);
		--y1;
	}
}

void SSD1306_invCircle(uint8_t x0, uint8_t y0, uint8_t radius){
	uint8_t x1 = 0;
	int8_t y1 = radius;
	int16_t delta = 2 - 2 * radius;
	int16_t error = 0;
	while(y1 >= 0)
	{
		SSD1306_invPixel(x0 + x1, y0 + y1);
		SSD1306_invPixel(x0 + x1, y0 - y1);
		SSD1306_invPixel(x0 - x1, y0 + y1);
		SSD1306_invPixel(x0 - x1, y0 - y1);
		error = 2 * (delta + y1) - 1;
		if(delta < 0 && error <= 0)
		{
			++x1;
			delta += 2 * x1 + 1;
			continue;
		}
		error = 2 * (delta - x1) - 1;
		if(delta > 0 && error > 0)
		{
			--y1;
			delta += 1 - 2 * y1;
			continue;
		}
		++x1;
		delta += 2 * (x1 - y1);
		--y1;
	}
}
