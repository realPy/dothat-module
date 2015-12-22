/*
 *  * Copyright 2015-2016
 *  *
 *  * Author: Manuel BARRAUD <manuel.barraud@me.com>
 *  *
 *  * This file is subject to the terms and conditions of version 2 of
 *  * the GNU General Public License.  See the file COPYING in the main
 *  * directory of this archive for more details.
 *
 */

#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/err.h>
#include <linux/i2c.h>
#include <linux/fcntl.h>

#include <linux/kernel.h>
#include <linux/fs.h>
 
#include <linux/interrupt.h>

#include <linux/spi/spi.h>


#include "dothat-st7036.h"
#include "dothat-st7036-sysfs.h"
#include "dothat-gpio.h"
#include "dothat-sn3218.h"
#include "dothat-sn3218-sysfs.h"
#include "dothat-cap1166.h"
#include "dothat-cap1166-sysfs.h"

static inline void *spi_get_clientdata (struct spi_device *spi)
{
return dev_get_drvdata (&spi->dev);
}

static inline void spi_set_clientdata (struct spi_device *spi, void *data)
{
dev_set_drvdata (&spi->dev, data);
}
		
/* define constant here */


#define DOTHATMAJOR 64



enum dothat_type {
        sn3218,
        cap1166,

};

static struct class *s_pDeviceClass;
//static struct device *s_pDeviceDot3KObject;




static struct i2c_client *dothat_clients[] = {
	[sn3218] = NULL,
	[cap1166] = NULL,
	
};

static const struct i2c_device_id dothat_id[] = {
            { "sn3218", sn3218 },
            { "cap1166", cap1166},
	    {}
};









MODULE_DEVICE_TABLE(i2c, dothat_id);

static int dothat_probe(struct i2c_client *client,const struct i2c_device_id *id) {

 //u8 color[3]={0x00,0xFF,0xFF};
 printk(KERN_INFO "dothat: Using %s  driver at slave address 0x%02x\n",
                                                         id->name, client->addr);


 if(id->driver_data==sn3218) {

	struct psn3218 * pData = devm_kzalloc(&client->dev, sizeof(struct psn3218), GFP_KERNEL);
        if (!pData)
                return -ENOMEM;
    

	memset(pData,0,sizeof(struct psn3218));
	pData->client=client;
	
	i2c_set_clientdata(client, pData);

 
	sn3218_init_sysfs(s_pDeviceClass,pData);
	

        //set maski activate led 	
 	sn3218_enable_leds(client,0b111111111111111111);
 	sn3218_output(client,pData->ledColor);

 	sn3218_enable(client,1);
	
	//sn3218_output_monocolor(pData,color);
 }else {

 	struct pcap1166 * pData = devm_kzalloc(&client->dev, sizeof(struct pcap1166), GFP_KERNEL);
    if (!pData)
        return -ENOMEM;
	
	memset(pData,0,sizeof(struct pcap1166));
	pData->client=client;
	i2c_set_clientdata(client, pData);
    cap1166_init_sysfs(s_pDeviceClass,pData);
	cap1166_touch_init(pData);
	
		 
	
 }

return 0;
}




static int dothat_remove(struct i2c_client *client)
{

struct pcap1166 * pData=NULL;


if(client ==  dothat_clients[sn3218]) {
	struct psn3218 * pData =i2c_get_clientdata(client);
	sn3218_enable(client,0);
	sn3218_exit_sysfs(pData);
	
}

if(client ==  dothat_clients[cap1166]) {
        cap1166_graph_off(client);
		
		pData =i2c_get_clientdata(client);
		
		cap1166_touch_detach(pData);
		cap1166_exit_sysfs(pData);
		printk(KERN_INFO "remove dot 1166\n");
		//kfree(pData);
		
		
}   

    return 0;
}










static struct i2c_driver dothat_driver = {
            	     .driver = {
                        .name   = "dothat",
                        .owner  = THIS_MODULE,
                      },
                      .probe  = dothat_probe,
                      .remove = dothat_remove,
                      .id_table = dothat_id,
};





 
static struct i2c_board_info __initdata dothat_i2c_board_info[] = {
        {
                I2C_BOARD_INFO("sn3218", 0x54),
                .platform_data= NULL,
        },
	{
                I2C_BOARD_INFO("cap1166", 0x2C),
                .platform_data= NULL,
        },


};
 





static struct spi_board_info st7036spidriver_info[] = {
       {
               .modalias      = "st7036",
               .max_speed_hz  = 1000000,
               .bus_num       = 1,
               .chip_select   = 0,
               .mode          = SPI_MODE_0,
       },
};

#define __devinit

static int st7036_remove(struct spi_device *spi)
{

    return 0;
}

static int __devinit st7036_probe(struct spi_device *spi)
{
struct pst7036 * pData=NULL;
printk(KERN_INFO "st7036: ok \n");
pr_info("st7036 :      %s  %dkHz %d bits mode=0x%02X\n",
		spi->modalias, spi->max_speed_hz/1000,
		spi->bits_per_word, spi->mode);


pData = devm_kzalloc(&spi->dev, sizeof(struct pst7036), GFP_KERNEL);
if (!pData)
    return -ENOMEM;

memset(pData,0,sizeof(struct pst7036));

pData->spi=spi;

spi_set_clientdata(spi, pData);	

st7036_update_display_mode(spi,1,0,0);


st7036_clear_screen(spi);

st7036_set_contrast(spi,40);

//st7036_write_string(spi,"Hello manu, hello my world");
//mdelay(100);
st7036_init_sysfs(s_pDeviceClass,pData);

//st7036_read_screen(spi);

return 0;
}



static struct spi_driver st7036_spi_driver = {
    .driver = {
        .name = "st7036",
        .owner = THIS_MODULE,
    },
    .probe = st7036_probe,
    .remove = st7036_remove,
};



static struct spi_device *spi_device=NULL;


static int __init
dothat_init(void)
{
struct i2c_adapter* adap=NULL;
struct spi_master * master=NULL;

setupGPIO();
st7036_init_LCD();




adap = i2c_get_adapter(1);
dothat_clients[sn3218] = i2c_new_device(adap, &dothat_i2c_board_info[0]);

dothat_clients[cap1166] = i2c_new_device(adap, &dothat_i2c_board_info[1]);

	
s_pDeviceClass = class_create(THIS_MODULE, "dothat");




 
i2c_add_driver(&dothat_driver);


master=spi_busnum_to_master(0);
if(master) {
spi_device=spi_new_device (master,&st7036spidriver_info[0]);
spi_master_put(master);


spi_register_driver(&st7036_spi_driver);

}
return 0; 
}

static void __exit dothat_exit(void)
{


     
      device_destroy(s_pDeviceClass, MKDEV(DOTHATMAJOR,0));
	  device_destroy(s_pDeviceClass, MKDEV(DOTHATMAJOR,1));
	  device_destroy(s_pDeviceClass, MKDEV(DOTHATMAJOR,2));
	  class_unregister(s_pDeviceClass);
      class_destroy(s_pDeviceClass);

      i2c_unregister_device(dothat_clients[sn3218]);
    
      i2c_unregister_device(dothat_clients[cap1166]);
	
      i2c_del_driver(&dothat_driver);

	  
      spi_unregister_driver(&st7036_spi_driver);
	  spi_dev_put(spi_device);
	  
	  /*
	  if (spi_device) {
	  	device_del(&spi_device->dev);
	    kfree(spi_device);
	  }
	  */
	  

	   st7036_reset_LCD();
      unsetupGPIO();
	  
}

module_init(dothat_init);
module_exit(dothat_exit);

MODULE_AUTHOR("Manuel BARRAUD <manuel.barraud@me.com>");
MODULE_DESCRIPTION("Dothat driver");
MODULE_LICENSE("GPL v2");
