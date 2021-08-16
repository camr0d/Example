#ifndef _ILI9486_H
#define _ILI9486_H
	
#include "stm32f4xx_hal.h"

// Размеры 
#define  ILI9486_LCD_PIXEL_WIDTH  320
#define  ILI9486_LCD_PIXEL_HEIGHT 480

#define ILI9486_DATA_Port	GPIOC
#define ILI9486_D0_Pin		GPIO_PIN_0
#define ILI9486_D1_Pin		GPIO_PIN_1
#define ILI9486_D2_Pin		GPIO_PIN_2
#define ILI9486_D3_Pin		GPIO_PIN_3
#define ILI9486_D4_Pin		GPIO_PIN_4
#define ILI9486_D5_Pin		GPIO_PIN_5
#define ILI9486_D6_Pin		GPIO_PIN_6
#define ILI9486_D7_Pin		GPIO_PIN_7

#define ILI9486_RD_Pin		GPIO_PIN_6
#define ILI9486_RD_Port		GPIOE
#define ILI9486_WR_Pin		GPIO_PIN_4
#define ILI9486_WR_Port		GPIOE
#define ILI9486_DC_Pin		GPIO_PIN_5
#define ILI9486_DC_Port		GPIOE
#define ILI9486_CS_Pin		GPIO_PIN_2
#define ILI9486_CS_Port		GPIOE
#define ILI9486_RST_Pin		GPIO_PIN_13
#define ILI9486_RST_Port	GPIOC	

#define ILI9486_RD_0()		{HAL_GPIO_WritePin(ILI9486_RD_Port, ILI9486_RD_Pin, GPIO_PIN_RESET);}
#define ILI9486_RD_1()		{HAL_GPIO_WritePin(ILI9486_RD_Port, ILI9486_RD_Pin, GPIO_PIN_SET);}
#define ILI9486_WR_0()		{HAL_GPIO_WritePin(ILI9486_WR_Port, ILI9486_WR_Pin, GPIO_PIN_RESET);}
#define ILI9486_WR_1()		{HAL_GPIO_WritePin(ILI9486_WR_Port, ILI9486_WR_Pin, GPIO_PIN_SET);}
#define ILI9486_DC_0()		{HAL_GPIO_WritePin(ILI9486_DC_Port, ILI9486_DC_Pin, GPIO_PIN_RESET);}
#define ILI9486_DC_1()		{HAL_GPIO_WritePin(ILI9486_DC_Port, ILI9486_DC_Pin, GPIO_PIN_SET);}
#define ILI9486_CS_0()		{HAL_GPIO_WritePin(ILI9486_CS_Port, ILI9486_CS_Pin, GPIO_PIN_RESET);}
#define ILI9486_CS_1()		{HAL_GPIO_WritePin(ILI9486_CS_Port, ILI9486_CS_Pin, GPIO_PIN_SET);}
#define ILI9486_RST_0()		{HAL_GPIO_WritePin(ILI9486_RST_Port, ILI9486_RST_Pin, GPIO_PIN_RESET);}
#define ILI9486_RST_1()		{HAL_GPIO_WritePin(ILI9486_RST_Port, ILI9486_RST_Pin, GPIO_PIN_SET);}

#define ILI9486_NOP            0x00
#define ILI9486_SWRESET        0x01

#define ILI9486_RDDID          0x04
#define ILI9486_RDDST          0x09
#define ILI9486_RDMODE         0x0A
#define ILI9486_RDMADCTL       0x0B
#define ILI9486_RDPIXFMT       0x0C
#define ILI9486_RDIMGFMT       0x0D
#define ILI9486_RDSELFDIAG     0x0F

#define ILI9486_SLPIN          0x10
#define ILI9486_SLPOUT         0x11
#define ILI9486_PTLON          0x12
#define ILI9486_NORON          0x13

#define ILI9486_INVOFF         0x20
#define ILI9486_INVON          0x21
#define ILI9486_GAMMASET       0x26
#define ILI9486_DISPOFF        0x28
#define ILI9486_DISPON         0x29

#define ILI9486_CASET          0x2A
#define ILI9486_PASET          0x2B
#define ILI9486_RAMWR          0x2C
#define ILI9486_RAMRD          0x2E

#define ILI9486_PTLAR          0x30
#define ILI9486_VSCRDEF        0x33
#define ILI9486_MADCTL         0x36
#define ILI9486_VSCRSADD       0x37     /* Vertical Scrolling Start Address */
#define ILI9486_PIXFMT         0x3A     /* COLMOD: Pixel Format Set */

#define ILI9486_RGB_INTERFACE  0xB0     /* RGB Interface Signal Control */
#define ILI9486_FRMCTR1        0xB1
#define ILI9486_FRMCTR2        0xB2
#define ILI9486_FRMCTR3        0xB3
#define ILI9486_INVCTR         0xB4
#define ILI9486_DFUNCTR        0xB6     /* Display Function Control */

#define ILI9486_PWCTR1         0xC0
#define ILI9486_PWCTR2         0xC1
#define ILI9486_PWCTR3         0xC2
#define ILI9486_PWCTR4         0xC3
#define ILI9486_PWCTR5         0xC4
#define ILI9486_VMCTR1         0xC5
#define ILI9486_VMCTR2         0xC7

#define ILI9486_RDID1          0xDA
#define ILI9486_RDID2          0xDB
#define ILI9486_RDID3          0xDC
#define ILI9486_RDID4          0xDD

#define ILI9486_GMCTRP1        0xE0
#define ILI9486_GMCTRN1        0xE1
#define ILI9486_DGCTR1         0xE2
#define ILI9486_DGCTR2         0xE3

#define ILI9486_MAD_RGB        0x08
#define ILI9486_MAD_BGR        0x00

#define ILI9486_MAD_VERTICAL   0x20
#define ILI9486_MAD_X_LEFT     0x00
#define ILI9486_MAD_X_RIGHT    0x40
#define ILI9486_MAD_Y_UP       0x80
#define ILI9486_MAD_Y_DOWN     0x00

#define ILI9486_MAD_COLORMODE  ILI9486_MAD_RGB

#define ILI9486_SIZE_X                     ILI9486_LCD_PIXEL_WIDTH
#define ILI9486_SIZE_Y                     ILI9486_LCD_PIXEL_HEIGHT
#define ILI9486_MAD_DATA_RIGHT_THEN_UP     ILI9486_MAD_COLORMODE | ILI9486_MAD_X_RIGHT | ILI9486_MAD_Y_UP
#define ILI9486_MAD_DATA_RIGHT_THEN_DOWN   ILI9486_MAD_COLORMODE | ILI9486_MAD_X_RIGHT | ILI9486_MAD_Y_DOWN
#define ILI9486_MAD_DATA_RGBMODE           ILI9486_MAD_COLORMODE | ILI9486_MAD_X_LEFT  | ILI9486_MAD_Y_DOWN

#define RGB24(val) (((val & 0x00f80000) >> 8 ) | ((val & 0x0000fc00) >> 5) |((val & 0x000000f8) >> 3))

#define LCD_COLOR_BLACK         0x0000
#define LCD_COLOR_GRAY          0xF7DE
#define LCD_COLOR_BLUE          0x001F
#define LCD_COLOR_RED           0xF800
#define LCD_COLOR_GREEN         0x07E0
#define LCD_COLOR_CYAN          0x07FF
#define LCD_COLOR_MAGENTA       0xF81F
#define LCD_COLOR_YELLOW        0xFFE0
#define LCD_COLOR_WHITE         0xFFFF

#define LCD_DEFAULT_TEXTCOLOR    LCD_COLOR_BLACK
#define LCD_DEFAULT_BACKCOLOR    LCD_COLOR_WHITE
// Функция записи данных в порт данных с помощью библиотеки HAL
//				data - данные для записи в порт
void ili9486_WritePort_data(uint8_t data);

//Чтение данных с порта
//Возвращает значение данных с порта
uint8_t ili9486_ReadPort_data(void);

//Функция чтения ID экрана
uint32_t ili9486_ReadID(void);

//Функция инициализации
void ili9486_Init(void);


void ili9486_WriteData(uint8_t data);

void ili9486_WriteCmd(uint8_t cmd);

//Функция задержки
void ili9486_Delay(uint32_t delay);

//Функция установки курсора
void ili9486_SetCursor(uint16_t Xpos, uint16_t Ypos);

//Функция установки пикселя
void ili9486_WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode);


//Функция указания окна для рисования
void ili9486_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);

void ili9486_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint16_t Color);

void ili9486_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint16_t* Color);

void ili9486_DrawText8x5(uint16_t Xpos, uint16_t Ypos, char Text);

#endif // _ILI9486_H
 





