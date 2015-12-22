/*
 *  * Copyright 2015-2016
 *  *
 *  * Author: Manuel BARRAUD <manuel.barraud@me.com>
 *  *
 *  * This file is subject to the terms and conditions of version 2 of
 *  * the GNU General Public License.  See the file COPYING in the main
 *  * directory of this archive for more details.
 *
 *		CAP1166 SYS FS
 */


#include "dothat-cap1166.h"

#include "dothat-cap1166-sysfs.h"


#define DOTHATMAJOR 64


static ssize_t show_cap1166_graph_bar_callback(struct device *dev, struct device_attribute *attr,
                    char *buf) {


    struct pcap1166 *pData=dev_get_drvdata(dev);


   if(pData) {


    return scnprintf(buf, PAGE_SIZE, "%d",pData->graph_bar_value);
   }

      
   return 0;
}

static ssize_t store_cap1166_graph_bar_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{


   
    int cnt;

    struct pcap1166 *pData=dev_get_drvdata(dev);

    if(pData) {



        cnt = sscanf(buf, "%hhd", &pData->graph_bar_value);
        if(cnt==1) {

           cap1166_set_progress_bar(pData->client,pData->graph_bar_value);


        }

    }
    //kstrtol

   

return count;
}




static ssize_t store_cap1166_graph_bar_callback_reverse(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{


   
    int cnt;

    struct pcap1166 *pData=dev_get_drvdata(dev);

    if(pData) {



        cnt = sscanf(buf, "%hhd", &pData->graph_bar_value);
        if(cnt==1) {

           cap1166_set_progress_bar_reverse(pData->client,pData->graph_bar_value);


        }

    }
    //kstrtol

   

return count;
}







static ssize_t show_cap1166_leds_callback(struct device *dev, struct device_attribute *attr,
                    char *buf) {


    struct pcap1166 *pData=dev_get_drvdata(dev);


   if(pData) {


    return scnprintf(buf, PAGE_SIZE, "%d",cap1166_graph_get_leds(pData->client));
   }

      
   return 0;
}

static ssize_t store_cap1166_leds_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{


   
    int cnt;
	u8 value;

    struct pcap1166 *pData=dev_get_drvdata(dev);

    if(pData) {



        cnt = sscanf(buf, "%hhd", &value);
        if(cnt==1) {
           cap1166_graph_set_leds_blink(pData->client,0);
           cap1166_graph_set_leds(pData->client,value);


        }

    }
    //kstrtol

   

return count;
}



static ssize_t show_cap1166_polarity_callback(struct device *dev, struct device_attribute *attr,
                    char *buf) {


    struct pcap1166 *pData=dev_get_drvdata(dev);


   if(pData) {


    return scnprintf(buf, PAGE_SIZE, "%d",cap1166_graph_get_polarity(pData->client));
   }

      
   return 0;
}

static ssize_t store_cap1166_polarity_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{


   
    int cnt;
	u8 value;

    struct pcap1166 *pData=dev_get_drvdata(dev);

    if(pData) {



        cnt = sscanf(buf, "%hhd", &value);
        if(cnt==1) {

           cap1166_graph_set_polarity(pData->client,value);


        }

    }
    //kstrtol

   

return count;
}


static ssize_t show_cap1166_luminosity_callback(struct device *dev, struct device_attribute *attr,
                    char *buf) {


    struct pcap1166 *pData=dev_get_drvdata(dev);


   if(pData) {


    return scnprintf(buf, PAGE_SIZE, "%d",cap1166_graph_get_leds_luminosity(pData->client));
   }

      
   return 0;
}

static ssize_t store_cap1166_luminosity_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{


   
    int cnt;
	u8 value;

    struct pcap1166 *pData=dev_get_drvdata(dev);

    if(pData) {



        cnt = sscanf(buf, "%hhd", &value);
        if(cnt==1) {

           cap1166_graph_set_leds_luminosity(pData->client,value);


        }

    }
    //kstrtol

   

return count;
}


static ssize_t show_cap1166_blink_callback(struct device *dev, struct device_attribute *attr,
                    char *buf) {


    struct pcap1166 *pData=dev_get_drvdata(dev);


   if(pData) {


    return scnprintf(buf, PAGE_SIZE, "%d",pData->leds_blink);
   }

      
   return 0;
}

static ssize_t store_cap1166_blink_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{


   
    int cnt;
	u8 value;

    struct pcap1166 *pData=dev_get_drvdata(dev);

    if(pData) {



        cnt = sscanf(buf, "%hhd", &value);
        if(cnt==1) {
			
		 
		   cap1166_graph_set_leds(pData->client,value);
           cap1166_graph_set_leds_blink(pData->client,value);


        }

    }
    //kstrtol

   

return count;
}

static ssize_t show_cap1166_blink_rate_callback(struct device *dev, struct device_attribute *attr,
                    char *buf) {

   int breathe;
   struct pcap1166 *pData=dev_get_drvdata(dev);

  
   if(pData) {
	breathe=cap1166_graph_get_breath_period(pData->client);

    return scnprintf(buf, PAGE_SIZE, "%d",breathe*32);
   }

      
   return 0;
}

static ssize_t store_cap1166_blink_rate_callback(struct device* dev ,struct device_attribute* attr,const char* buf,size_t count)
{


   
    int cnt;
	int breathe_value;
	u8 value;
    struct pcap1166 *pData=dev_get_drvdata(dev);

    if(pData) {



        cnt = sscanf(buf, "%d", &breathe_value);
        if(cnt==1) {
		   value=breathe_value/32;
		   
		   cap1166_graph_set_breath_period(pData->client,value);
           


        }

    }
    //kstrtol

   

return count;
}

static DEVICE_ATTR(cap1166_graph_bar,0660, show_cap1166_graph_bar_callback,store_cap1166_graph_bar_callback);
static DEVICE_ATTR(cap1166_graph_bar_reverse,0660, show_cap1166_graph_bar_callback,store_cap1166_graph_bar_callback_reverse);
static DEVICE_ATTR(cap1166_leds,0660, show_cap1166_leds_callback,store_cap1166_leds_callback);
static DEVICE_ATTR(cap1166_polarity,0660, show_cap1166_polarity_callback,store_cap1166_polarity_callback);
static DEVICE_ATTR(cap1166_luminosity,0660, show_cap1166_luminosity_callback,store_cap1166_luminosity_callback);
static DEVICE_ATTR(cap1166_blink,0660, show_cap1166_blink_callback,store_cap1166_blink_callback);
static DEVICE_ATTR(cap1166_blink_rate,0660, show_cap1166_blink_rate_callback,store_cap1166_blink_rate_callback);


void cap1166_init_sysfs(struct class *s_pDeviceClass,struct pcap1166 *data)
{
	int result;
	
data->sysfsdevice = device_create(s_pDeviceClass, NULL,MKDEV(DOTHATMAJOR,1), NULL, "cap1166");
dev_set_drvdata(data->sysfsdevice,data);

dev_attr_cap1166_graph_bar.attr.name="graph_bar";
dev_attr_cap1166_graph_bar_reverse.attr.name="graph_bar_reverse";
dev_attr_cap1166_leds.attr.name="leds";
dev_attr_cap1166_polarity.attr.name="polarity";
dev_attr_cap1166_luminosity.attr.name="luminosity";
dev_attr_cap1166_blink.attr.name="blink";
dev_attr_cap1166_blink_rate.attr.name="blink_rate";

result = device_create_file(data->sysfsdevice, &dev_attr_cap1166_graph_bar);
result = device_create_file(data->sysfsdevice, &dev_attr_cap1166_graph_bar_reverse);
result = device_create_file(data->sysfsdevice, &dev_attr_cap1166_leds);
result = device_create_file(data->sysfsdevice, &dev_attr_cap1166_polarity);
result = device_create_file(data->sysfsdevice, &dev_attr_cap1166_luminosity);
result = device_create_file(data->sysfsdevice, &dev_attr_cap1166_blink);
result = device_create_file(data->sysfsdevice, &dev_attr_cap1166_blink_rate);

}

void cap1166_exit_sysfs(struct pcap1166 *data)
{

}
