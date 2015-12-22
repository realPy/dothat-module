/*
 *  * Copyright 2015-2016
 *  *
 *  * Author: Manuel BARRAUD <manuel.barraud@me.com>
 *  *
 *  * This file is subject to the terms and conditions of version 2 of
 *  * the GNU General Public License.  See the file COPYING in the main
 *  * directory of this archive for more details.
 *
 *		ST7036 support header
 */

#ifndef DOTHATST7036_H
#define DOTHATST7036_H	

#include <linux/spi/spi.h>

#define ST7036_COMMAND_CLEAR  0b00000001
#define ST7036_COMMAND_HOME  0b00000010
#define ST7036_COMMAND_SCROLL  0b00010000
#define ST7036_COMMAND_DOUBLE  0b00010000
#define ST7036_COMMAND_BIAS  0b00010100
#define ST7036_COMMAND_SET_DISPLAY_MODE  0b00001000


#define ST7036_INSTRUCTION_TEMPLATE  0b00111000

#define ST7036_BLINK_ON  0b00000001
#define ST7036_CURSOR_ON  0b00000010
#define ST7036_DISPLAY_ON  0b00000100
#define ST7036_DRAM_OFFSET 0b10000000	
	
	
	
	

struct pst7036 {
    struct spi_device *spi;
	struct device *sysfsdevice;
	u8 type_buffer;
	char shift_register;
	u8 ac_buffer;
	u8 display;
	u8 contrast;
	char lcd_buffer[49];//16*3

};

void st7036_reset_LCD(void);
void st7036_init_LCD(void);
int st7036_write_instruction_set(struct spi_device *device, u8 instruction_set);
int st7036_write_command(struct spi_device *device,u8 value,u8 instruction_set);
int st7036_update_display_mode(struct spi_device *device,u8 display_state,u8 blink_state,u8 cursor_state);
//Must be between 0 and 0x40
void st7036_set_contrast(struct spi_device *device,u8 contrast);
int st7036_clear_screen(struct spi_device *device);
int st7036_set_bias(struct spi_device *device,u8 bias);
void st7036_write_string(struct spi_device *device, char *string);
int st7036_set_cursor_position(struct spi_device *device, u8 column ,u8 row);
int st7036__cursor_left(struct spi_device *device);
int st7036__cursor_right(struct spi_device *device);
int st7036__shift_left(struct spi_device *device);
int st7036__shift_right(struct spi_device *device);





#endif