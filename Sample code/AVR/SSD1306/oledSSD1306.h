/*
 * oledSSD1306.h
 *
 * Created: 09.02.2020 16:39:19
 *  Author: nara_
 */ 


#ifndef OLEDSSD1306_H_
#define OLEDSSD1306_H_

#define OLED_ADRES 0x78
// �������� �������
#define _SSD1306_SET_CONTRAST_CONTROL					0x81
#define _SSD1306_DISPLAY_ALL_ON_RESUME					0xA4
#define _SSD1306_DISPLAY_ALL_ON							0xA5
#define _SSD1306_NORMAL_DISPLAY							0xA6
#define _SSD1306_INVERT_DISPLAY							0xA7
#define _SSD1306_DISPLAY_OFF							0xAE
#define _SSD1306_DISPLAY_ON								0xAF
#define _SSD1306_NOP									0xE3
// ������� ���������
#define _SSD1306_HORIZONTAL_SCROLL_RIGHT				0x26
#define _SSD1306_HORIZONTAL_SCROLL_LEFT					0x27
#define _SSD1306_HORIZONTAL_SCROLL_VERTICAL_AND_RIGHT	0x29
#define _SSD1306_HORIZONTAL_SCROLL_VERTICAL_AND_LEFT	0x2A
#define _SSD1306_DEACTIVATE_SCROLL						0x2E
#define _SSD1306_ACTIVATE_SCROLL						0x2F
#define _SSD1306_SET_VERTICAL_SCROLL_AREA				0xA3
// ������� ��������� ��������� ���������
#define _SSD1306_SET_LOWER_COLUMN						0x00
#define _SSD1306_SET_HIGHER_COLUMN						0x10
#define _SSD1306_MEMORY_ADDR_MODE						0x20
#define _SSD1306_SET_COLUMN_ADDR						0x21
#define _SSD1306_SET_PAGE_ADDR							0x22
// ������� ������������	������
#define _SSD1306_SET_START_LINE							0x40
#define _SSD1306_SET_SEGMENT_REMAP						0xA0
#define _SSD1306_SET_MULTIPLEX_RATIO					0xA8
#define _SSD1306_COM_SCAN_DIR_INC						0xC0
#define _SSD1306_COM_SCAN_DIR_DEC						0xC8
#define _SSD1306_SET_DISPLAY_OFFSET						0xD3
#define _SSD1306_SET_COM_PINS							0xDA
#define _SSD1306_CHARGE_PUMP							0x8D
// ������� ��������� �������������
#define _SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO			0xD5
#define _SSD1306_SET_PRECHARGE_PERIOD					0xD9
#define _SSD1306_SET_VCOM_DESELECT						0xDB

#include "TWI.h"

int8_t SSD1306_getAbs(int8_t x);										// ���������� ������ �����
int8_t SSD1306_getSign(int8_t x);										// ���������� ���� �����

void SSD1306_init(void);												// ������������� �������
void SSD1306_com(int com);												// ������ ������� �������
void SSD1306_data(int data);											// ������ ������ �������
void SSD1306_cleer(void);												// ������� �������
void SSD1306_fill(void);												// ���������� �������

void SSD1306_drawPixel(uint8_t x1, uint8_t y1);							// ��������� �������
void SSD1306_invPixel(uint8_t x1, uint8_t y1);							// �������������� �������
void SSD1306_drawByte(uint8_t x1, uint8_t y1, uint8_t b);				// ��������� �����
 
void SSD1306_drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);	// ��������� ����� (�������� ����������)
void SSD1306_invLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);	// �������� �����

void SSD1306_drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);	// ��������� ��������
void SSD1306_invRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);	// �������� ��������

void SSD1306_drawCircle(uint8_t x0, uint8_t y0, uint8_t radius);		// ��������� ����������
void SSD1306_invCircle(uint8_t x0, uint8_t y0, uint8_t radius);			// �������� ����������

void drawPictOled(uint8_t x1, uint8_t y1, uint8_t dx, uint8_t dy);// ��������� ��������

void SSD1306_printChar_5x8(uint8_t x1, uint8_t y1, char sim);			// ��������� �����
void SSD1306_printString_5x8(uint8_t x1, uint8_t y1, char *str);		// ��������� ������

#endif /* OLEDSSD1306_H_ */