#include "main.h"
#include "ILI9486.h"
extern const uint8_t Font24_Table[];

void ili9486_Init(void)
{
	ILI9486_CS_0();
	ili9486_WriteCmd(ILI9486_SWRESET);
	HAL_Delay(150);
	ili9486_WriteCmd(ILI9486_RGB_INTERFACE);
	ili9486_WriteData(0x00);
	ili9486_WriteCmd(ILI9486_SLPOUT);
	HAL_Delay(10);
	ili9486_WriteCmd(ILI9486_PIXFMT);
	ili9486_WriteData(0x55);
	ili9486_WriteCmd(ILI9486_MADCTL);
	ili9486_WriteData(ILI9486_MAD_DATA_RGBMODE);
	ili9486_WriteCmd(ILI9486_PWCTR3);
	ili9486_WriteData(0x44);
	ili9486_WriteCmd(ILI9486_VMCTR1);
	ili9486_WriteData(0x00);
	ili9486_WriteData(0x00);
	ili9486_WriteData(0x00);
	ili9486_WriteData(0x00);
	ili9486_WriteCmd(ILI9486_GMCTRP1);
	ili9486_WriteData(0x0F);
	ili9486_WriteData(0x1F);
	ili9486_WriteData(0x1C);
	ili9486_WriteData(0x0C);
	ili9486_WriteData(0x0F);
	ili9486_WriteData(0x08);
	ili9486_WriteData(0x48);
	ili9486_WriteData(0x98);
	ili9486_WriteData(0x37);
	ili9486_WriteData(0x0A);
	ili9486_WriteData(0x13);
	ili9486_WriteData(0x04);
	ili9486_WriteData(0x11);
	ili9486_WriteData(0x0D);
	ili9486_WriteData(0x00);
	ili9486_WriteCmd(ILI9486_GMCTRN1);
	ili9486_WriteData(0x0F);
	ili9486_WriteData(0x32);
	ili9486_WriteData(0x2E);
	ili9486_WriteData(0x0B);
	ili9486_WriteData(0x0D);
	ili9486_WriteData(0x05);
	ili9486_WriteData(0x47);
	ili9486_WriteData(0x75);
	ili9486_WriteData(0x37);
	ili9486_WriteData(0x0A);
	ili9486_WriteData(0x13);
	ili9486_WriteData(0x04);
	ili9486_WriteData(0x11);
	ili9486_WriteData(0x0D);
	ili9486_WriteData(0x00);
	ili9486_WriteCmd(ILI9486_DGCTR1);
	ili9486_WriteData(0x0F);
	ili9486_WriteData(0x32);
	ili9486_WriteData(0x2E);
	ili9486_WriteData(0x0B);
	ili9486_WriteData(0x0D);
	ili9486_WriteData(0x05);
	ili9486_WriteData(0x47);
	ili9486_WriteData(0x75);
	ili9486_WriteData(0x37);
	ili9486_WriteData(0x0A);
	ili9486_WriteData(0x13);
	ili9486_WriteData(0x04);
	ili9486_WriteData(0x11);
	ili9486_WriteData(0x0D);
	ili9486_WriteData(0x00);
	ili9486_WriteCmd(ILI9486_NORON);
	ili9486_WriteCmd(ILI9486_INVOFF);
	ili9486_WriteCmd(ILI9486_SLPOUT);
	HAL_Delay(200);
	ili9486_WriteCmd(ILI9486_DISPON);
	ILI9486_CS_1();
	HAL_Delay(10);
	
}
void ili9486_WriteData(uint8_t data)
{
	ili9486_WritePort_data(data);
	ILI9486_WR_0();
	ili9486_Delay(2);
	ILI9486_WR_1();
}

void ili9486_WriteCmd(uint8_t cmd)
{	
	ILI9486_DC_0();
	ili9486_WriteData(cmd);
	ILI9486_DC_1();
}


void ili9486_WritePort_data(uint8_t data)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		if (data  & (1 << i))
		{
			HAL_GPIO_WritePin(ILI9486_DATA_Port, (1 << i), GPIO_PIN_SET);
		} 
		else
		{
			HAL_GPIO_WritePin(ILI9486_DATA_Port, (1 << i), GPIO_PIN_RESET);
		}
	}
}

uint8_t ili9486_ReadPort_data(void)
{
	return (HAL_GPIO_ReadPin(ILI9486_DATA_Port, ILI9486_D7_Pin) << 7) | (HAL_GPIO_ReadPin(ILI9486_DATA_Port, ILI9486_D6_Pin) << 6) 
		 | (HAL_GPIO_ReadPin(ILI9486_DATA_Port, ILI9486_D5_Pin) << 5) | (HAL_GPIO_ReadPin(ILI9486_DATA_Port, ILI9486_D4_Pin) << 4) 
		 | (HAL_GPIO_ReadPin(ILI9486_DATA_Port, ILI9486_D3_Pin) << 3) | (HAL_GPIO_ReadPin(ILI9486_DATA_Port, ILI9486_D2_Pin) << 2) 
		 | (HAL_GPIO_ReadPin(ILI9486_DATA_Port, ILI9486_D1_Pin) << 1) | HAL_GPIO_ReadPin(ILI9486_DATA_Port, ILI9486_D0_Pin);
}


uint32_t ili9486_ReadID(void)
{
	uint8_t data[4] = { 0 };
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin =  TFT_D0_Pin | TFT_D1_Pin | TFT_D2_Pin
                          | TFT_D3_Pin | TFT_D4_Pin | TFT_D5_Pin | TFT_D6_Pin
                          | TFT_D7_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	ILI9486_CS_0();
	ili9486_WriteCmd(0xD3);
	
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	ILI9486_RD_0();
	ili9486_Delay(10);
	data[3] = ili9486_ReadPort_data();
	ILI9486_RD_1();
	ili9486_Delay(10);
	ILI9486_RD_0();
	ili9486_Delay(10);
	data[2] = ili9486_ReadPort_data();
	ILI9486_RD_1();
	ili9486_Delay(10);
	ILI9486_RD_0();
	ili9486_Delay(10);
	data[1] = ili9486_ReadPort_data();
	ILI9486_RD_1();
	ili9486_Delay(10);
	ILI9486_RD_0();
	ili9486_Delay(10);
	data[0] = ili9486_ReadPort_data();
	ILI9486_RD_1();
	ILI9486_CS_1();
	GPIO_InitStruct.Pin = TFT_D0_Pin | TFT_D1_Pin | TFT_D2_Pin
                          | TFT_D3_Pin | TFT_D4_Pin | TFT_D5_Pin | TFT_D6_Pin
                          | TFT_D7_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	return data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);

}


//Функция установки курсора
void ili9486_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
	ili9486_WriteCmd(ILI9486_CASET);
	ili9486_WriteData(Xpos >> 8);
	ili9486_WriteData(Xpos);
	ili9486_WriteData(Xpos >> 8);
	ili9486_WriteData(Xpos);
	ili9486_WriteCmd(ILI9486_PASET);
	ili9486_WriteData(Ypos  >> 8) ;
	ili9486_WriteData(Ypos);
	ili9486_WriteData(Ypos >> 8);
	ili9486_WriteData(Ypos);
}

//Функция установки пикселя
void ili9486_WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode)
{
	ILI9486_CS_0();
	ili9486_SetCursor(Xpos, Ypos);
	ili9486_WriteCmd(ILI9486_RAMWR);
	ili9486_WriteData((RGBCode & 0xFF00)>>8);
	ili9486_WriteData(RGBCode & 0x00FF);
	ILI9486_CS_1();
}


void ili9486_Delay(uint32_t delay)
{
	while (delay)
	{
		delay--;
	}
}


void ili9486_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
	ILI9486_CS_0();
	ili9486_WriteCmd(ILI9486_CASET);
	ili9486_WriteData(Xpos >> 8);
	ili9486_WriteData(Xpos);
	ili9486_WriteData((Xpos + Width - 1) >> 8);
	ili9486_WriteData((Xpos + Width - 1));
	ili9486_WriteCmd(ILI9486_PASET);
	ili9486_WriteData(Ypos >> 8);
	ili9486_WriteData(Ypos);
	ili9486_WriteData((Ypos + Height - 1) >> 8);
	ili9486_WriteData((Ypos + Height - 1));
	ILI9486_CS_1();
}



void ili9486_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint16_t Color)
{
	uint32_t Size = Width * Height;
	ili9486_SetDisplayWindow(Xpos, Ypos, Width, Height);
	ILI9486_CS_0();
	ili9486_WriteCmd(ILI9486_RAMWR);
	while (Size--)
	{
		ili9486_WriteData(Color >> 8);
		ili9486_WriteData(Color);
	}
	ILI9486_CS_1();
}




void ili9486_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint16_t* Color)
{
	uint32_t Size = Width * Height;
	uint16_t lcd_data;
	ili9486_SetDisplayWindow(Xpos, Ypos, Width, Height);
	ILI9486_CS_0();
	ili9486_WriteCmd(ILI9486_RAMWR);
	while (Size--)
	{
		lcd_data = *Color;
		ili9486_WriteData(lcd_data >> 8);
		ili9486_WriteData(lcd_data);
		Color++;
	}
	ILI9486_CS_1();
}

void ili9486_DrawText8x5(uint16_t Xpos, uint16_t Ypos, char Text)
{
	ili9486_SetDisplayWindow(Xpos, Ypos, Xpos + 17, Ypos + 24);
	uint16_t Size = 17 * 24;
	uint8_t bit;
	ILI9486_CS_0();
	ili9486_WriteCmd(ILI9486_RAMWR);
	for (uint8_t i = 0; i < 24 * 3; i += 3)
	{
		for (uint8_t j = 0; j < 8; j++)
		{
			if (Font24_Table[2016 + i ] & (1 << j))
			{
				ili9486_WriteData(LCD_DEFAULT_TEXTCOLOR >> 8);
				ili9486_WriteData(LCD_DEFAULT_TEXTCOLOR);
			}
			else
			{
				ili9486_WriteData(LCD_DEFAULT_BACKCOLOR >> 8);
				ili9486_WriteData(LCD_DEFAULT_BACKCOLOR);
			}
		}
		for (uint8_t j = 0; j < 8; j++)
		{
			if (Font24_Table[2016 + i + 1] & (1 << j))
			{
				ili9486_WriteData(LCD_DEFAULT_TEXTCOLOR >> 8);
				ili9486_WriteData(LCD_DEFAULT_TEXTCOLOR);
			}
			else
			{
				ili9486_WriteData(LCD_DEFAULT_BACKCOLOR >> 8);
				ili9486_WriteData(LCD_DEFAULT_BACKCOLOR);
			}
		}
		if (Font24_Table[2016 + i + 2] & (1 << 7))
		{
			ili9486_WriteData(LCD_DEFAULT_TEXTCOLOR >> 8);
			ili9486_WriteData(LCD_DEFAULT_TEXTCOLOR);
		}
		else
		{
			ili9486_WriteData(LCD_DEFAULT_BACKCOLOR >> 8);
			ili9486_WriteData(LCD_DEFAULT_BACKCOLOR);
		}
	}
	
	ILI9486_CS_1();
}