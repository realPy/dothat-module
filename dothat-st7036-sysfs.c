/*
 *  * Copyright 2015-2016
 *  *
 *  * Author: Manuel BARRAUD <manuel.barraud@me.com>
 *  *
 *  * This file is subject to the terms and conditions of version 2 of
 *  * the GNU General Public License.  See the file COPYING in the main
 *  * directory of this archive for more details.
 *
 *		ST7036 SYS FS
 */


#include "dothat-st7036.h"

#include "dothat-st7036-sysfs.h"


#define DOTHATMAJOR 64



static ssize_t show_st7036_lcd_buffer_callback(struct device *dev, struct device_attribute *attr,
                    char *buf) {


   struct pst7036 *pData=dev_get_drvdata(dev);

  
   if(pData) {


    return scnprintf(buf, PAGE_SIZE, "%s",pData->lcd_buffer);
   }

      
   return 0;
}

static ssize_t store_st7036_lcd_buffer_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{
	
    struct pst7036 *pData=dev_get_drvdata(dev);
	char buffer[49];
	
    if(pData) {

		if(count>48)
			count=48;
		memset(buffer,0,49);
		strncpy(buffer,buf,48);
		
		st7036_write_string(pData->spi,buffer);
		

    }
    //kstrtol

   

return count;
}


static ssize_t show_st7036_lcd_clear_callback(struct device *dev, struct device_attribute *attr,
                    char *buf) {


  
   return 0;
}

static ssize_t store_st7036_lcd_clear_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{
	
    struct pst7036 *pData=dev_get_drvdata(dev);
	
	
    if(pData) {

		
		st7036_clear_screen(pData->spi);
		
		
    }
    //kstrtol

   

return count;
}

static ssize_t show_st7036_lcd_cursor_position_callback(struct device *dev, struct device_attribute *attr,
                    char *buf) {

    struct pst7036 *pData=dev_get_drvdata(dev);
	u8 line=0;
	u8 column=0;
	
	
	column=pData->ac_buffer/16;
	line=pData->ac_buffer%16;
	
    if(pData) {


     return scnprintf(buf, PAGE_SIZE, "C:%hhd R:%hhd",column,line);
    }
	
  
   return 0;
}

static ssize_t store_st7036_lcd_cursor_position_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{
	
    struct pst7036 *pData=dev_get_drvdata(dev);
	u8 row,column;
	int cnt;
    if(pData) {

        cnt = sscanf(buf, "%hhd %hhd",&column,&row);
        if(cnt==2) {
			
		 
			if(column>=0&&column<16&&row>=0&&row<3) 
			{

				st7036_set_cursor_position(pData->spi,column,row); 
			}


        }
		
		
		
		
    }
    //kstrtol

   

return count;
}



static ssize_t show_st7036_lcd_enable_callback(struct device *dev, struct device_attribute *attr,
                    char *buf) {


    struct pst7036 *pData=dev_get_drvdata(dev);


   if(pData&&(pData->display&ST7036_DISPLAY_ON)) {


    return scnprintf(buf, PAGE_SIZE, "1");
   }

        return scnprintf(buf, PAGE_SIZE, "0");

}

static ssize_t store_st7036_lcd_enable_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{


    u8 enable;
    int cnt;

    struct pst7036 *pData=dev_get_drvdata(dev);

    if(pData) {



        cnt = sscanf(buf, "%hhd", &enable);
        if(cnt==1) {
			
			st7036_update_display_mode(pData->spi,enable,pData->display&ST7036_BLINK_ON,pData->display&ST7036_CURSOR_ON);

        }

    }

   

return count;
}



static ssize_t show_st7036_lcd_cursor_blink_callback(struct device *dev, struct device_attribute *attr,
                    char *buf) {


    struct pst7036 *pData=dev_get_drvdata(dev);


   if(pData&&(pData->display&ST7036_BLINK_ON)) {


    return scnprintf(buf, PAGE_SIZE, "1");
   }

        return scnprintf(buf, PAGE_SIZE, "0");

}

static ssize_t store_st7036_lcd_cursor_blink_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{


    u8 enable;
    int cnt;

    struct pst7036 *pData=dev_get_drvdata(dev);

    if(pData) {



        cnt = sscanf(buf, "%hhd", &enable);
        if(cnt==1) {
			
			st7036_update_display_mode(pData->spi,pData->display&ST7036_DISPLAY_ON,enable,pData->display&ST7036_CURSOR_ON);

        }

    }

   

return count;
}

static ssize_t show_st7036_lcd_cursor_on_callback(struct device *dev, struct device_attribute *attr,
                    char *buf) {


    struct pst7036 *pData=dev_get_drvdata(dev);


   if(pData&&(pData->display&ST7036_CURSOR_ON)) {


    return scnprintf(buf, PAGE_SIZE, "1");
   }

        return scnprintf(buf, PAGE_SIZE, "0");

}

static ssize_t store_st7036_lcd_cursor_on_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{


    u8 enable;
    int cnt;

    struct pst7036 *pData=dev_get_drvdata(dev);

    if(pData) {



        cnt = sscanf(buf, "%hhd", &enable);
        if(cnt==1) {
			
			st7036_update_display_mode(pData->spi,pData->display&ST7036_DISPLAY_ON,pData->display&ST7036_BLINK_ON,enable);

        }

    }

   

return count;
}

static ssize_t show_st7036_lcd_contrast_callback(struct device *dev, struct device_attribute *attr,
                    char *buf) {


    struct pst7036 *pData=dev_get_drvdata(dev);


   if(pData) {


    return scnprintf(buf, PAGE_SIZE, "%hhd",pData->contrast);
   }

        return 0;

}

static ssize_t store_st7036_lcd_contrast_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{


    u8 contrast;
    int cnt;

    struct pst7036 *pData=dev_get_drvdata(dev);

    if(pData) {



        cnt = sscanf(buf, "%hhd", &contrast);
        if(cnt==1) {
			
			if(contrast>0x3F)
				contrast=0x3F;
			
			st7036_set_contrast(pData->spi,contrast);

        }

    }

   

return count;
}



static ssize_t show_st7036_lcd_shift_display_callback(struct device *dev, struct device_attribute *attr, char *buf) {


   struct pst7036 *pData=dev_get_drvdata(dev);


   if(pData) {


    	return scnprintf(buf, PAGE_SIZE, "%hhd",pData->shift_register);
   }


        return 0;

}

static ssize_t store_st7036_lcd_shift_display_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{


    char display;
    int cnt;

    struct pst7036 *pData=dev_get_drvdata(dev);

    if(pData) {



        cnt = sscanf(buf, "%c", &display);
        if(cnt==1) {
			
			if(display=='>') {
				st7036__shift_right(pData->spi);
			}
			
			if(display=='<') {
				st7036__shift_left(pData->spi);
			}
			
			

        }

    }

   

return count;
}

static DEVICE_ATTR(st7036_lcd_buffer,0660, show_st7036_lcd_buffer_callback,store_st7036_lcd_buffer_callback);
static DEVICE_ATTR(st7036_lcd_clear,0660, show_st7036_lcd_clear_callback,store_st7036_lcd_clear_callback);
static DEVICE_ATTR(st7036_lcd_cursor_position,0660, show_st7036_lcd_cursor_position_callback,store_st7036_lcd_cursor_position_callback);
static DEVICE_ATTR(st7036_lcd_enable,0660, show_st7036_lcd_enable_callback,store_st7036_lcd_enable_callback);
static DEVICE_ATTR(st7036_lcd_cursor_blink,0660, show_st7036_lcd_cursor_blink_callback,store_st7036_lcd_cursor_blink_callback);
static DEVICE_ATTR(st7036_lcd_cursor_on,0660, show_st7036_lcd_cursor_on_callback,store_st7036_lcd_cursor_on_callback);
static DEVICE_ATTR(st7036_lcd_contrast,0660, show_st7036_lcd_contrast_callback,store_st7036_lcd_contrast_callback);
static DEVICE_ATTR(st7036_lcd_shift_display,0660, show_st7036_lcd_shift_display_callback,store_st7036_lcd_shift_display_callback);

void st7036_init_sysfs(struct class *s_pDeviceClass,struct pst7036 *data)
{
	int result;
	
data->sysfsdevice = device_create(s_pDeviceClass, NULL,MKDEV(DOTHATMAJOR,2), NULL, "st7036");
dev_set_drvdata(data->sysfsdevice,data);

dev_attr_st7036_lcd_buffer.attr.name="lcd_buffer";
dev_attr_st7036_lcd_clear.attr.name="clear";
dev_attr_st7036_lcd_cursor_position.attr.name="cursor_position";
dev_attr_st7036_lcd_enable.attr.name="enable";
dev_attr_st7036_lcd_cursor_blink.attr.name="cursor_blink";
dev_attr_st7036_lcd_cursor_on.attr.name="cursor_on";
dev_attr_st7036_lcd_contrast.attr.name="contrast";
dev_attr_st7036_lcd_shift_display.attr.name="shift_display";


result = device_create_file(data->sysfsdevice, &dev_attr_st7036_lcd_buffer);
result = device_create_file(data->sysfsdevice, &dev_attr_st7036_lcd_clear);
result = device_create_file(data->sysfsdevice, &dev_attr_st7036_lcd_cursor_position);
result = device_create_file(data->sysfsdevice, &dev_attr_st7036_lcd_enable);
result = device_create_file(data->sysfsdevice, &dev_attr_st7036_lcd_cursor_blink);
result = device_create_file(data->sysfsdevice, &dev_attr_st7036_lcd_cursor_on);
result = device_create_file(data->sysfsdevice, &dev_attr_st7036_lcd_contrast);
result = device_create_file(data->sysfsdevice, &dev_attr_st7036_lcd_shift_display);

}

void st7036_exit_sysfs(struct pst7036 *data)
{

}
