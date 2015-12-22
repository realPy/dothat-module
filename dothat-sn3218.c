/*
 *  * Copyright 2015-2016
 *  *
 *  * Author: Manuel BARRAUD <manuel.barraud@me.com>
 *  *
 *  * This file is subject to the terms and conditions of version 2 of
 *  * the GNU General Public License.  See the file COPYING in the main
 *  * directory of this archive for more details.
 *
 *		SN3218 
 */
 
 
#include "dothat-sn3218.h"


//u8 gamma_table[256]={0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16, 16, 16, 17, 17, 17, 18, 18, 19, 19, 20, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 26, 26, 27, 27, 28, 29, 29, 30, 30, 31, 32, 33, 33, 34, 35, 36, 36, 37, 38, 39, 40, 41, 41, 42, 43, 44, 45, 46, 47, 48, 49, 51, 52, 53, 54, 55, 56, 58, 59, 60, 62, 63, 64, 66, 67, 69, 70, 72, 73, 75, 77, 78, 80, 82, 84, 86, 87, 89, 91, 93, 95, 98, 100, 102, 104, 106, 109, 111, 114, 116, 119, 121, 124, 127, 130, 132, 135, 138, 141, 144, 148, 151, 154, 158, 161, 165, 168, 172, 176, 180, 184, 188, 192, 196, 200, 205, 209, 214, 219, 223, 228, 233, 238, 244, 249};


int sn3218_enable(struct i2c_client *client,u8 state)
{

 int err = 0;
 struct psn3218 *psn3218=NULL;
 err=i2c_smbus_write_byte_data(client,SN3218_CMD_ENABLE_OUTPUT,state);
	 
 if (err < 0)
  pr_err("%s: SN3218 ENABLE i2c writing failed\n", __func__);
 else {
	psn3218 = i2c_get_clientdata(client);
	if(psn3218)
		psn3218->state=state;

 }
  

 return err;

}

int sn3218_update(struct i2c_client *client)
{

 int err = 0;
 u8 state=0xFF;

 err = i2c_smbus_write_i2c_block_data(client,SN3218_CMD_UPDATE, sizeof(u8), &state);
 if (err < 0)
  pr_err("%s: SN3218 UPDATE i2c writing failed\n", __func__);

 return err;

}





//enable led by masking
int sn3218_enable_leds(struct i2c_client *client,u32 bits)
{


 int err = 0;
 u8 buf[3];
 struct psn3218 *psn3218=NULL;
 
 buf[0] = bits & 0x3F;
 buf[1] = (bits >> 6) & 0x3F;
 buf[2] = (bits >> 12) & 0x3F;


 err=0;
 err = i2c_smbus_write_i2c_block_data(client,SN3218_CMD_ENABLE_LEDS, sizeof(buf), buf);
 if (err < 0)
  pr_err("%s: POWER_REGs i2c writing failed\n", __func__);
  else {
   psn3218 = i2c_get_clientdata(client);
   if(psn3218)
     psn3218->mask=bits;

   sn3218_update(client);

  }
 return err;


}


int sn3218_output(struct i2c_client *client,u8 *ledColor)
{

int err = 0;

err = i2c_smbus_write_i2c_block_data(client,SN3218_CMD_SET_PWM_VALUES, 18, ledColor);
 if (err < 0)
  pr_err("%s: POWER_REGs i2c writing failed\n", __func__);

return sn3218_update(client);


}

int sn3218_output_monocolor(struct psn3218 *pData,u8 *monoColor)
{
	int i;
	
	for(i=0;i<6;i++) {
                pData->ledColor[3*i]=(u8)monoColor[0];
                pData->ledColor[3*i+1]=(u8)monoColor[1];
                pData->ledColor[3*i+2]=(u8)monoColor[2];
	}
     return  sn3218_output(pData->client,pData->ledColor);
		
	
}