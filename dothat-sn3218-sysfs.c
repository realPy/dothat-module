/*
 *  * Copyright 2015-2016
 *  *
 *  * Author: Manuel BARRAUD <manuel.barraud@me.com>
 *  *
 *  * This file is subject to the terms and conditions of version 2 of
 *  * the GNU General Public License.  See the file COPYING in the main
 *  * directory of this archive for more details.
 *
 *		SN3218 SYS FS
 */

#include "dothat-sn3218.h"

#include "dothat-sn3218-sysfs.h"

#define DOTHATMAJOR 64
static ssize_t show_sn3218_enable_callback(struct device *dev, struct device_attribute *attr,
                    char *buf) {


    struct psn3218 *pData=dev_get_drvdata(dev);


   if(pData&&pData->state) {


    return scnprintf(buf, PAGE_SIZE, "1");
   }

        return scnprintf(buf, PAGE_SIZE, "0");

}

static ssize_t store_sn3218_enable_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{


   u8 enable;
    int cnt;

    struct psn3218 *pData=dev_get_drvdata(dev);

    if(pData) {



        cnt = sscanf(buf, "%hhd", &enable);
        if(cnt==1) {

            sn3218_enable(pData->client,enable);


        }

    }
    //kstrtol

   

return count;
}


static ssize_t show_sn3218_lcd_callback(struct device *dev, struct device_attribute *attr,
                            char *buf) {


int color,i,cnt;
char BGR[]= {'B','G','R'};

        struct psn3218 *pData=dev_get_drvdata(dev);
	
	if(pData) {
          buf[0]=0;
          for(color=0;color<3;color++) {

		
	         cnt=scnprintf(buf,PAGE_SIZE,"%s %c:",buf,BGR[color]);
         	 for(i=0;i<6;i++) {

               	 cnt=scnprintf(buf,PAGE_SIZE,"%s 0x%02x",buf,pData->ledColor[i*3+color]);
          	}

	  cnt=scnprintf(buf,PAGE_SIZE,"%s \n",buf);
	  }

          return cnt;

        }



return 0;
}



static ssize_t store_sn3218_lcd_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{
    u8 segment;
    int b,g,r;
    int cnt;

    struct psn3218 *pData=dev_get_drvdata(dev);

    if(pData) {

	
    	cnt = sscanf(buf, "%hhd %02x%02x%02x", &segment,&b,&g,&r);
	if(segment>=0&&segment<6) {


		pData->ledColor[3*segment]=(u8)b;
		pData->ledColor[3*segment+1]=(u8)g;
		pData->ledColor[3*segment+2]=(u8)r;
		sn3218_output(pData->client,pData->ledColor);
		return count;
	}

    }



return count;
}




static ssize_t store_sn3218_lcd_raw_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{
    int i;
    u8 b,g,r;
    int cnt;
    char data[7];	
    struct psn3218 *pData;

    memset(data,0,7);
    pData=dev_get_drvdata(dev);

    if(pData) {
		//pr_info("store raw: %s %d",buf,count);
		//cnt = sscanf(buf, "%02hhx%02hhx%02hhx",&b,&g,&r);
		//pr_info("info: %d %d %d",b,g,r);
		if(count>=36) {
			for(i=0;i<6;i++) {
				memcpy(data,buf+6*i,6);
				//pr_info("info data : %s",data);
				cnt = sscanf(data, "%02hhx%02hhx%02hhx",&b,&g,&r);
				pData->ledColor[3*i]=(u8)b;
				pData->ledColor[3*i+1]=(u8)g;
				pData->ledColor[3*i+2]=(u8)r;
				//pr_info("RGB:%d %d %d %d",i,b,g,r);
			
			}
			
			sn3218_output(pData->client,pData->ledColor);
			return count;
		}
 
    }



return count;
}




static ssize_t store_sn3218_lcd_monocolor_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{
   
    int cnt;
	u8 color[3];
    struct psn3218 *pData=dev_get_drvdata(dev);

    if(pData) {


        cnt = sscanf(buf,"%02hhx%02hhx%02hhx",color,color+1,color+2);

		sn3218_output_monocolor(pData,color);
        return count;

    }



return count;
}


static ssize_t show_sn3218_lcd_mask_callback(struct device *dev, struct device_attribute *attr,
                            char *buf) {


struct psn3218 *pData=dev_get_drvdata(dev);

    if(pData) {

	return scnprintf(buf,PAGE_SIZE,"%05x\n",pData->mask);

    }

return 0;
}

static ssize_t store_sn3218_lcd_mask_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{


    int cnt;
    u32 value;
    struct psn3218 *pData=dev_get_drvdata(dev);

    if(pData) {


        cnt = sscanf(buf,"%05x",&value);


        sn3218_enable_leds(pData->client,value);
        return count;

    }





return count;
}






static DEVICE_ATTR(sn3218_enable,0660, show_sn3218_enable_callback,store_sn3218_enable_callback);
static DEVICE_ATTR(sn3218_lcd,0660, show_sn3218_lcd_callback,store_sn3218_lcd_callback);
static DEVICE_ATTR(sn3218_lcd_raw,0660, show_sn3218_lcd_callback,store_sn3218_lcd_raw_callback);
static DEVICE_ATTR(sn3218_lcd_monocolor,0660, show_sn3218_lcd_callback,store_sn3218_lcd_monocolor_callback);
static DEVICE_ATTR(sn3218_lcd_mask,0660, show_sn3218_lcd_mask_callback,store_sn3218_lcd_mask_callback);

void sn3218_init_sysfs(struct class *s_pDeviceClass,struct psn3218 *data)
{
	int result;
	
	data->sysfsdevice = device_create(s_pDeviceClass, NULL, MKDEV(DOTHATMAJOR,0), NULL, "sn3218");
	dev_set_drvdata(data->sysfsdevice,data);
	dev_attr_sn3218_enable.attr.name="enable";
	dev_attr_sn3218_lcd.attr.name="lcd";
	dev_attr_sn3218_lcd_raw.attr.name="lcd_raw";
	dev_attr_sn3218_lcd_monocolor.attr.name="monocolor";
	dev_attr_sn3218_lcd_mask.attr.name="mask";

	result = device_create_file(data->sysfsdevice, &dev_attr_sn3218_enable);

	result = device_create_file(data->sysfsdevice, &dev_attr_sn3218_lcd);
	result = device_create_file(data->sysfsdevice, &dev_attr_sn3218_lcd_raw);
	result = device_create_file(data->sysfsdevice, &dev_attr_sn3218_lcd_monocolor);
	result = device_create_file(data->sysfsdevice, &dev_attr_sn3218_lcd_mask);
	
}
void sn3218_exit_sysfs(struct psn3218 *data)
{

}

