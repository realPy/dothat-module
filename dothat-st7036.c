/*
 *  * Copyright 2015-2016
 *  *
 *  * Author: Manuel BARRAUD <manuel.barraud@me.com>
 *  *
 *  * This file is subject to the terms and conditions of version 2 of
 *  * the GNU General Public License.  See the file COPYING in the main
 *  * directory of this archive for more details.
 *
 *		SPI support communication
 */
 

#include <linux/delay.h>
#include <linux/string.h>
#include <linux/err.h>

#include "dothat-st7036.h"
#include "dothat-gpio.h"

static inline void *spi_get_clientdata (struct spi_device *spi)
{
return dev_get_drvdata (&spi->dev);
}


void st7036_reset_LCD()
{
//set OFF and ON to reset the LCD
INP_GPIO(12); 
OUT_GPIO(12);
GPIO_CLR = 1<<12;
udelay(1000);
GPIO_SET = 1<<12;
}

void st7036_init_LCD(void)
{

	st7036_reset_LCD();
	//set output GPIO 25 TO HIGH
	INP_GPIO(25); 
	OUT_GPIO(25);
	GPIO_SET = 1<<25;
	
	udelay(60);
}

int st7036_write_instruction_set(struct spi_device *device, u8 instruction_set)
{
int ret;
u8 instruction_template;
//clear the GPIO 25
GPIO_CLR = 1<<25;
//compute the good register 


instruction_template=(ST7036_INSTRUCTION_TEMPLATE|instruction_set);
ret = spi_w8r8 (device,instruction_template);
if(ret<0) 
	pr_info("st7036_write_instruction_set\n");

udelay(60);

return ret;
}

int st7036_write_command(struct spi_device *device,u8 value,u8 instruction_set)
{
int ret;
	
GPIO_CLR = 1<<25;

//function set
st7036_write_instruction_set(device,instruction_set);

ret=spi_w8r8 (device,value);
if(ret<0) 
	pr_info("st7036_write_command\n");

udelay(60);
return ret;

}




int st7036_update_display_mode(struct spi_device *device,u8 display_state,u8 blink_state,u8 cursor_state)
{
int err;
struct pst7036 *pData=NULL;
u8 mask=ST7036_COMMAND_SET_DISPLAY_MODE;

if(display_state)
	mask|=ST7036_DISPLAY_ON;

if(blink_state)
	mask|=ST7036_BLINK_ON;

if(cursor_state)
	mask|=ST7036_CURSOR_ON;

pData=spi_get_clientdata(device);
if(pData) {
	pData->display=mask;
}

err=st7036_write_command(device,mask,0);
udelay(50);

return err;
}

void st7036_set_contrast(struct spi_device *device,u8 contrast)
{
struct pst7036 *pData=NULL;
//  keep comment on piromoni source 
//  # For 3.3v operation the booster must be on, which is
//  # on the same command as the (2-bit) high-nibble of contrast

pData=spi_get_clientdata(device);
if(pData) {
	pData->contrast=contrast;
}


st7036_write_command(device,(0b01010100 | ((contrast >> 4) & 0x03)), 1);

st7036_write_command(device,0b01101011, 1);

// Set low-nibble of the contrast
st7036_write_command(device,(0b01110000 | (contrast & 0x0F)), 1);

}



void reset_shift_register(struct spi_device *device)
{
	struct pst7036 *pData=NULL;
	int i=0;
	
	pData=spi_get_clientdata(device);
	
	if(pData) {


		if(pData->shift_register) {
			if(pData->shift_register>7) {
				while(pData->shift_register) {
					st7036__shift_right(device);
				}
		
			}else {
				while(pData->shift_register) {
					st7036__shift_left(device);
				}
		
			}
			
		}
	}
	
}

int st7036_clear_screen(struct spi_device *device)
{
	int result=0;
	struct pst7036 *pData=NULL;
	
	result=st7036_write_command(device,ST7036_COMMAND_CLEAR,0);
	pData=spi_get_clientdata(device);
	if(pData) {
		memset(pData->lcd_buffer,' ',48);
		pData->ac_buffer=0;
		pData->shift_register=0;
	}
	udelay(1100);//wait 1.1ms
	//reset shift register
	reset_shift_register(device);
	
	
	return 0;
}

void st7036_clear(struct spi_device *device)
{
st7036_clear_screen(device);
//st7036_set_cursor_position(device, 0 ,0);

}

int st7036_set_bias(struct spi_device *device,u8 bias) 
{
	
	return st7036_write_command(device,ST7036_COMMAND_BIAS| (bias << 4) | 1,1);
}




void st7036_write_string(struct spi_device *device, char *string)
{
	int	ret=1;
	struct pst7036 *pData=NULL;
	GPIO_SET = 1<<25;
	udelay(1000);
	pData=spi_get_clientdata(device);
	
	while(*string&&ret>=0) {

	if(pData) {
		
		pData->lcd_buffer[pData->ac_buffer]=*string;
		pData->ac_buffer++;
		
		if(pData->ac_buffer>47)
			pData->ac_buffer=0;
		
	}
	ret = spi_write (device,string,1);
	
	if(ret<0) 
		pr_info("%s write failed\n",__func__);

	;
	udelay(30);

	string++;
	}
	
	udelay(60);
}

u8 get_offset_row(u8 double_value,u8 row) 
{
	if(row==0)
		return 0;
	
	return 1<<(3+row);
	
}




int st7036_set_cursor_position(struct spi_device *device, u8 column ,u8 row) 
{
	u8 offset=0;
	struct pst7036 *pData=NULL;
	/*
	
	([0], [0, 64], [0, 16, 32])	
	*/
	 pData=spi_get_clientdata(device);
	 
	 offset=get_offset_row(0,row)+column;
	 if(pData)
	 	pData->ac_buffer=offset;
	 return st7036_write_command(device,ST7036_DRAM_OFFSET|offset,0);
}

int st7036__cursor_left(struct spi_device *device)
{
	return st7036_write_command(device,ST7036_COMMAND_SCROLL,0);
}

int st7036__cursor_right(struct spi_device *device)
{
	return st7036_write_command(device,ST7036_COMMAND_SCROLL | (1 << 2),0);
}

int st7036__shift_left(struct spi_device *device)
{
	struct pst7036 *pData=NULL;
	pData=spi_get_clientdata(device);
	
	if(pData) {
		
		
		pData->shift_register--;
		if(pData->shift_register<0)
			pData->shift_register=15;
		
	}
	
	return st7036_write_command(device,ST7036_COMMAND_SCROLL | (1 << 3),0);
}

int st7036__shift_right(struct spi_device *device)
{
	struct pst7036 *pData=NULL;
	pData=spi_get_clientdata(device);
	
	if(pData) {
		
		
		pData->shift_register++;
		if(pData->shift_register>15)
			pData->shift_register=0;
		
	}
	
	return st7036_write_command(device,ST7036_COMMAND_SCROLL | (1 << 3)|(1 << 2),0);
}