/*
 *  * Copyright 2015-2016
 *  *
 *  * Author: Manuel BARRAUD <manuel.barraud@me.com>
 *  *
 *  * This file is subject to the terms and conditions of version 2 of
 *  * the GNU General Public License.  See the file COPYING in the main
 *  * directory of this archive for more details.
 *
 *		CAPP1166 
 */
 
 

#include "dothat-cap1166.h"
#include <linux/delay.h>

char *cap1166_state_str[4]={"None","Press","Hold","Release"};


static void pcap1166_timer(unsigned long data)
{
	struct pcap1166 *ptrData = (struct pcap1166*)data;
	schedule_work(&ptrData->work);
}

volatile static int value=0;



/*

int get_twos_comp(u8 delta) 
{
	
	int val=delta;
	
	if (( val & (1<< 7)) != 0){
		val = val - (1 << 8);
	}
	            
 return val;
	
}
*/

int get_twos_comp(u8 delta) 
{
	
	int val=delta;
	
	if (( val & 128)){
		val = val - 256;
	}
	            
 return val;
	
}

/*
static char *binrep (unsigned int val, char *buff, int sz) {
    char *pbuff = buff;

   
    if (sz < 1) return NULL;

    
    if (val == 0) {
        *pbuff++ = '0';
        *pbuff = '\0';
        return buff;
    }

  
    pbuff += sz;
    *pbuff-- = '\0';

   
    while (val != 0) {
        if (sz-- == 0) return NULL;
        *pbuff-- = ((val & 1) == 1) ? '1' : '0';

   
        val >>= 1;
    }
    return pbuff+1;
}


static char *u8_2strbin(u8 val, char *buff, int sz) {

int i;

char *pbuff = buff;

for(i=7;i>=0;i--) {
	
	*pbuff=(val & (1<<i)) ? '1' : '0';
	pbuff++;
}	

*pbuff='\0';

return buff;
	
}
*/

void send_ev_for_button(u8 button,CAP1166_STATE state,struct pcap1166 * data) {
	
	int key=0;
	printk(KERN_INFO "button %d %s!\n",button,cap1166_state_str[state]);
	
	switch(button) {
		case 0:
			key=OFFSET_KEYBOARD+KEY_BACK;
		break;
		case 1:
			key=OFFSET_KEYBOARD+KEY_UP;
		break;
		case 2:
			key=OFFSET_KEYBOARD+KEY_DOWN;
		break;
		case 3:
			key=OFFSET_KEYBOARD+KEY_LEFT;
		break;
		case 4:
		   key=OFFSET_KEYBOARD+KEY_ENTER;
		break;
		case 5:
		   key=OFFSET_KEYBOARD+KEY_RIGHT;
		break;
		   
		
		
	}
	

		if(state==CAP1166_STATE_PRESS) {
			input_report_key(data->idev, key, 1);
			input_sync(data->idev);
		}
		if(state==CAP1166_STATE_RELEASE) {
			input_report_key(data->idev, key, 0);
			input_sync(data->idev);
		}	
		
	 
}


void cap1166_get_inputs_status(struct pcap1166 * data)
{
	u8 touched;
	u8 threshold[6];
	u8 delta[6];
	u8 i;
	int deltaC;
	u8 previousState;
	u8 general_status;

	
	touched = i2c_smbus_read_byte_data(data->client,CAP1166_R_INPUT_STATUS);
	
	general_status = i2c_smbus_read_byte_data(data->client,CAP1166_R_GENERAL_STATUS);
	
	if(general_status & 2) {
		
			
		printk(KERN_INFO "cap1166: MTP warn\n");
	}
	
		
	i2c_smbus_read_i2c_block_data(data->client,CAP1166_R_INPUT_1_THRESH, sizeof(threshold), threshold);
	i2c_smbus_read_i2c_block_data(data->client,CAP1166_R_INPUT_1_DELTA, sizeof(delta), delta);


	
	
	//if(delta[5])
	//printk(KERN_INFO "BUTTON event %d[%s] [%s] %d\n",touched,u8_2strbin(touched,buffer,32),u8_2strbin(general_status,b_gstatus,32),delta[5]);
	
	for(i=0;i<6;i++) {
		
		
        if (((1 << i) & touched)) {

                deltaC = get_twos_comp(delta[i]);
				
                previousState=data->buttonState[i];
                if (deltaC >= threshold[i]) {




                        if(previousState==CAP1166_STATE_PRESS) {
                                //si HOLD ENABLE
                                data->buttonState[i]=CAP1166_STATE_HOLD;
								send_ev_for_button(i,CAP1166_STATE_HOLD,data);
                        }

                        if(previousState==CAP1166_STATE_NONE ||previousState==CAP1166_STATE_RELEASE)
                        {
                              
									data->buttonState[i]=CAP1166_STATE_PRESS;
                                	send_ev_for_button(i,CAP1166_STATE_PRESS,data);
                                                
                        }

                }/*else {

                        if(previousState!=CAP1166_STATE_RELEASE) {

                                data->buttonState[i]=CAP1166_STATE_RELEASE;
								send_ev_for_button(i,CAP1166_STATE_RELEASE);
                        }else
                                data->buttonState[i]=CAP1166_STATE_NONE;


                }*/

                

				
				
        }/* else {
			
			if(data->buttonState[i]!=CAP1166_STATE_NONE) {
				
				data->buttonState[i]=CAP1166_STATE_RELEASE;
				send_ev_for_button(i,CAP1166_STATE_RELEASE);
				
				
			}
			data->buttonState[i]=CAP1166_STATE_NONE;
			
		}*/
	} 

	
}


void check_release(struct pcap1166 * data) 
{
	u8 touched;
	int i;

		
	touched = i2c_smbus_read_byte_data(data->client,CAP1166_R_INPUT_STATUS);
	//printk(KERN_INFO "BUTTON event %d[%s]\n",touched,u8_2strbin(touched,buffer,32));
	for(i=0;i<6;i++) {
		
		
        if ((data->buttonState[i]!=CAP1166_STATE_NONE&&data->buttonState[i]!=CAP1166_STATE_RELEASE)&&(((1 << i) & touched)==0)) {
		
			send_ev_for_button(i,CAP1166_STATE_RELEASE,data);
			data->buttonState[i]=CAP1166_STATE_NONE;
		}


	}
	
	
	
}

void cap1166_ack_new_event(struct pcap1166 * data)
{
	u8 maincontrol=0;
	
	maincontrol = i2c_smbus_read_byte_data(data->client,CAP1166_R_MAIN_CONTROL);
	maincontrol= (maincontrol & 0b11111110);
	i2c_smbus_write_byte_data(data->client,CAP1166_R_MAIN_CONTROL,maincontrol);
}

void cap1166_poll_new_event(struct pcap1166 * data)
{
	
	
	u8 maincontrol;
	
	
	maincontrol=i2c_smbus_read_byte_data(data->client,CAP1166_R_MAIN_CONTROL);
	
	
	
	if((maincontrol & 1)) {
		
		
		
		//printk(KERN_INFO "cap1166: New trigger\n");
		cap1166_get_inputs_status(data);
		data->needCheckRelease=1;	
		//acknownledge event
		cap1166_ack_new_event(data);
	
		
	
		
	}else {
		if(data->needCheckRelease) {
			
			check_release(data);
			data->needCheckRelease=0;
		}
	}
	
}

static void pcap1166_work(struct work_struct *work)
{
	struct pcap1166 *ptrData = container_of(work, struct pcap1166, work);
	 mutex_lock(&ptrData->lock);
	 cap1166_poll_new_event(ptrData);
	 //printk(KERN_INFO "cap1166: Poll\n");
	 if(!ptrData->willUnload) {
		 mod_timer(&ptrData->timer, jiffies+HZ/20);
	 }else
		printk(KERN_INFO "crash prevent\n");
	  
	 mutex_unlock(&ptrData->lock);
	 
}




void cap1166_enable_repeats(struct i2c_client *client,u8 inputs)
{
	
	i2c_smbus_write_byte_data(client,CAP1166_R_REPEAT_ENABLE,inputs);
}


void cap1166_enable_interrupts(struct i2c_client *client,u8 interrupts)
{


	i2c_smbus_write_byte_data(client,CAP1166_R_INTERRUPT_EN ,interrupts);


}


void cap1166_enable_inputs(struct i2c_client *client,u8 inputs)
{


	i2c_smbus_write_byte_data(client,CAP1166_R_INPUT_ENABLE ,inputs);


}


void cap1166_recalibrate(struct pcap1166 *data)
{
	
	i2c_smbus_write_byte_data(data->client,CAP1166_R_RECALIBRATION_REGISTER,0xA);
	
	i2c_smbus_write_byte_data(data->client,CAP1166_R_CALIBRATION,0b00111111);
	printk(KERN_INFO "recalibration...\n");
	while(i2c_smbus_read_byte_data(data->client,CAP1166_R_CALIBRATION)){
		printk(KERN_INFO "recalibration not yet finished\n");
		msleep(10);
	}
	
	
}

void cap1166_touch_init(struct pcap1166 *data)
{
	int i;
	int result;
	//force recalibration
	
	
	
	data->idev=devm_input_allocate_device(&data->client->dev);

		
	data->idev->name = "dot3k touch button";

							

	data->idev->evbit[0] = BIT(EV_KEY);
	set_bit(OFFSET_KEYBOARD+KEY_RIGHT, data->idev->keybit);
	set_bit(OFFSET_KEYBOARD+KEY_LEFT, data->idev->keybit);
	set_bit(OFFSET_KEYBOARD+KEY_UP, data->idev->keybit);
	set_bit(OFFSET_KEYBOARD+KEY_DOWN, data->idev->keybit);
	set_bit(OFFSET_KEYBOARD+KEY_BACK, data->idev->keybit);
	set_bit(OFFSET_KEYBOARD+KEY_ENTER, data->idev->keybit);
	
	cap1166_recalibrate(data);
	cap1166_enable_inputs(data->client,0b111111);
	
	cap1166_enable_interrupts(data->client,0b111111);
	
	

	
	i2c_smbus_write_byte_data(data->client,CAP1166_R_SAMPLING_CONFIG, 0b00001000); // 1sample per measure, 1.28ms time, 35ms cycle
	i2c_smbus_write_byte_data(data->client,CAP1166_R_SENSITIVITY,     0b01100000); // 2x sensitivity
    i2c_smbus_write_byte_data(data->client,CAP1166_R_GENERAL_CONFIG,  0b00111000);
    i2c_smbus_write_byte_data(data->client,CAP1166_R_CONFIGURATION2,  0b01100000);
	cap1166_enable_repeats(data->client,0b00000000);
	
	
	
	
	for(i=0;i<8;i++) {
		
		data->buttonState[i]=CAP1166_STATE_NONE;
	
	}
		
	result=input_register_device(data->idev);
	
	mutex_init(&data->lock);
	INIT_WORK(&data->work, pcap1166_work);
	init_timer(&data->timer);
	data->timer.function = pcap1166_timer;
	data->timer.data     = (unsigned long)data;
	schedule_work(&data->work);

}


void cap1166_touch_detach(struct pcap1166 *data)
{
	
	data->willUnload=1;
	del_timer_sync(&data->timer);
	cancel_work_sync(&data->work);
	//input_unregister_device(data->idev);
	//flush_scheduled_work();
	
}


int cap1166_graph_set_leds(struct i2c_client *client,u8 leds)
{
	
	return i2c_smbus_write_byte_data(client,CAP1166_LED_OUTPUT_CON,leds);
}


u8 cap1166_graph_get_leds(struct i2c_client *client)
{
	
	return i2c_smbus_read_byte_data(client,CAP1166_LED_OUTPUT_CON);
}

int cap1166_graph_set_polarity(struct i2c_client *client,u8 leds)
{
	//inverse polarity
	return i2c_smbus_write_byte_data(client,CAP1166_R_LED_POLARITY,leds);	
		
} 

u8 cap1166_graph_get_polarity(struct i2c_client *client)
{
	
	return i2c_smbus_read_byte_data(client,CAP1166_R_LED_POLARITY);
}

int cap1166_graph_set_leds_luminosity(struct i2c_client *client,u8 duty)
{
	//the luminosity is apply to all leds set logical ON
	
	return i2c_smbus_write_byte_data(client,CAP1166_LED_DIRECT_DUTY,duty);
	
}


u8 cap1166_graph_get_leds_luminosity(struct i2c_client *client)
{
	
	return i2c_smbus_read_byte_data(client,CAP1166_LED_DIRECT_DUTY);
}




void cap1166_graph_set_leds_blink(struct i2c_client *client,u8 leds)
{
	//the luminosity is apply to all leds set logical ON
	int i;
	u8 registerLeds1=0;
	u8 registerLeds2=0;
	struct pcap1166 *data=NULL;
	
	
	for(i=0;i<6;i++) {
		
		if(i<4) {
			
			if(leds & ( 1<<i)) {
				registerLeds1|=((1<<i*2)|(1<<(i*2+1)));
				
			}
			
		}else {
			if(leds & ( 1<<i)) {
				registerLeds2|=((1<<(i-4)*2)|(1<<((i-4)*2+1)));
				
			}
		}
		
	}
	
	data = i2c_get_clientdata(client);
	if(data)
		data->leds_blink=leds;
	
	i2c_smbus_write_byte_data(client,CAP1166_LED_BEHAVIOR1,registerLeds1);
	i2c_smbus_write_byte_data(client,CAP1166_LED_BEHAVIOR2,registerLeds2);
	
}


int cap1166_graph_set_breath_period(struct i2c_client *client,u8 period)
{


	return i2c_smbus_write_byte_data(client,CAP1166_LED_BREATH_PERIOD,period);
}

	
	
u8 cap1166_graph_get_breath_period(struct i2c_client *client)
{
	
	return i2c_smbus_read_byte_data(client,CAP1166_LED_BREATH_PERIOD);
}

int cap1166_graph_off(struct i2c_client *client) 
{



cap1166_graph_set_leds(client,0b00000000);
cap1166_graph_set_polarity(client,0b00000000);
cap1166_graph_set_leds_luminosity(client,0b000000);

return 0;
}





	
//up to down	
int cap1166_set_progress_bar(struct i2c_client *client,u8 value)
{
	//from 0 to 255 use userland to tranpose in pourcentage 
	int step=0;
	u8 full_leds;
	u8 duty_led;
	int i;
	
	u8 polarity=0;
	step=NUM_LEDS*STEP_DUTY*value/255;
	full_leds=step/16;
	duty_led=step%16;
	
	//the tips here is to use polarity to light the full leds and set only the duty leds at the good luminosity
	
	for(i=0;i<full_leds;i++)
		polarity|=1<<i;
	
	 
		 
	if(step>0) {
		cap1166_graph_set_leds_luminosity(client,duty_led <<4);
		cap1166_graph_set_polarity(client,polarity);
		cap1166_graph_set_leds(client,1<<(full_leds));
	}else 
		cap1166_graph_off(client);
	
	
	return 0;	 
}


//down to up
int cap1166_set_progress_bar_reverse(struct i2c_client *client,u8 value)
{
	//from 0 to 255 use userland to tranpose in pourcentage 
	int step=0;
	u8 full_leds;
	u8 duty_led;
	int i;
	
	u8 polarity=0;
	step=NUM_LEDS*STEP_DUTY*value/255;
	full_leds=step/16;
	duty_led=step%16;
	
	//the tips here is to use polarity to light the full leds and set only the duty leds at the good luminosity
	
	for(i=NUM_LEDS;i>=(NUM_LEDS-full_leds);i--)
		polarity|=1<<i;
	
	 
		 
	if(step>0) {
		cap1166_graph_set_leds_luminosity(client,duty_led <<4);
		cap1166_graph_set_polarity(client,polarity);
		cap1166_graph_set_leds(client,1<<(NUM_LEDS-full_leds-1));
	}else 
		cap1166_graph_off(client);
	
return 0;		 
}


u8 cap1166_get_ProductID(struct i2c_client *client)
{
u8 product_id=0;
	
product_id=i2c_smbus_read_byte_data(client,CAP1166_PRODUCT_ID);

return product_id;
}