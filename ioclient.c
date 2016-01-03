#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
#include <sys/select.h>
#include <time.h>
#include <math.h>

#define NET_INTERFACE "tun0"

#define YELLOW "00FFFF"
#define BLUE "FF0000"
#define RED "0000FF"
#define LIME "00FF00"
#define AQUA "FFFF00"
#define GREEN "008000"
#define GRAY "808080"
#define MARRON "000080"
#define NAVY "800000"
#define SILVER "C0C0C0"
#define TEAL "808000"
#define NOCOLOR "000000"

static const char *const evval[3] = {
    "RELEASED",
    "PRESSED",
    "REPEATED"
};


unsigned char gamma_table_blue[256]={0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16, 16, 16, 17, 17, 17, 18, 18, 19, 19, 20, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 26, 26, 27, 27, 28, 29, 29, 30, 30, 31, 32, 33, 33, 34, 35, 36, 36, 37, 38, 39, 40, 41, 41, 42, 43, 44, 45, 46, 47, 48, 49, 51, 52, 53, 54, 55, 56, 58, 59, 60, 62, 63, 64, 66, 67, 69, 70, 72, 73, 75, 77, 78, 80, 82, 84, 86, 87, 89, 91, 93, 95, 98, 100, 102, 104, 106, 109, 111, 114, 116, 119, 121, 124, 127, 130, 132, 135, 138, 141, 144, 148, 151, 154, 158, 161, 165, 168, 172, 176, 180, 184, 188, 192, 196, 200, 205, 209, 214, 219, 223, 228, 233, 238, 244, 249};
unsigned char gamma_table_red[256]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 10, 10, 10, 10, 10, 10, 11, 11, 11, 12, 12, 12, 12, 12, 13, 13, 14, 14, 14, 15, 15, 15, 15, 16, 16, 17, 17, 17, 18, 18, 19, 19, 20, 20, 20, 21, 21, 22, 22, 23, 23, 24, 25, 25, 25, 26, 27, 27, 28, 29, 29, 30, 30, 31, 32, 32, 33, 34, 35, 36, 37, 37, 38, 39, 40, 41, 42, 42, 44, 45, 45, 47, 47, 49, 50, 51, 52, 53, 55, 55, 57, 58, 60, 61, 62, 63, 65, 66, 67, 70, 71, 72, 74, 75, 77, 79, 81, 82, 85, 86, 88, 90, 92, 94, 96, 98, 100, 102, 105, 107, 110, 112, 115, 117, 120, 122, 125, 128, 131, 134, 137, 140, 142, 146, 149, 152, 156, 159, 162, 166, 170, 174, 177};
unsigned char gamma_table_green[256]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 9, 9, 9, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 13, 13, 13, 13, 14, 14, 15, 15, 15, 16, 16, 16, 16, 17, 18, 18, 18, 18, 19, 20, 20, 20, 21, 21, 22, 22, 23, 23, 24, 25, 25, 25, 26, 26, 27, 28, 28, 29, 30, 30, 31, 32, 33, 33, 34, 35, 36, 36, 37, 38, 39, 40, 41, 41, 43, 43, 45, 45, 46, 48, 48, 50, 51, 52, 53, 54, 55, 56, 58, 59, 61, 62, 63, 65, 66, 68, 69, 71, 72, 74, 75, 77, 79, 81, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 103, 105, 107, 110, 112, 115, 117, 120, 122, 125, 128, 130, 133, 136, 139, 142, 145, 148, 152, 155};

/*
 *                      T V S U B
 *
 * Subtract 2 timeval structs:  out = out - in.
 *
 * Out is assumed to be >= in.
 */
void tvsub( struct timeval *out, struct timeval *in )
{
        if( (out->tv_usec -= in->tv_usec) < 0 )   {
                out->tv_sec--;
                out->tv_usec += 1000000;
        }
        out->tv_sec -= in->tv_sec;
}



void
hsvtorgb(unsigned char *r, unsigned char *g, unsigned char *b, unsigned char h, unsigned char s, unsigned char v)
{
    unsigned char region, fpart, p, q, t;
    
    if(s == 0) {
        /* color is grayscale */
        *r = *g = *b = v;
        return;
    }
    
    /* make hue 0-5 */
    region = h / 43;
    /* find remainder part, make it from 0-255 */
    fpart = (h - (region * 43)) * 6;
    
    /* calculate temp vars, doing integer multiplication */
    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * fpart) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - fpart)) >> 8))) >> 8;
        
    /* assign temp vars based on color cone region */
    switch(region) {
        case 0:
            *r = v; *g = t; *b = p; break;
        case 1:
            *r = q; *g = v; *b = p; break;
        case 2:
            *r = p; *g = v; *b = t; break;
        case 3:
            *r = p; *g = q; *b = v; break;
        case 4:
            *r = t; *g = p; *b = v; break;
        default:
            *r = v; *g = p; *b = q; break;
    }
    

}




void
hsv2rgb(float *r, float *g, float *b, float h, float s, float v)
{
	float   F, M, N, K;
	int     i;

	if (s == 0.0) {
		*r = *g = *b = v;
	} else {
		if (h == 1.0)
			h = 0.0;
		h *= 6.0;
		i = floorf(h);
		F = h - i;
		M = v * (1 - s);
		N = v * (1 - s * F);
		K = v * (1 - s * (1 - F));

		switch (i) {
		case 0: *r = v; *g = K; *b = M; break;
		case 1: *r = N; *g = v; *b = M; break;
		case 2: *r = M; *g = v; *b = K; break;
		case 3: *r = M; *g = N; *b = v; break;
		case 4: *r = K; *g = M; *b = v; break;
		case 5: *r = v; *g = M; *b = N; break;
		}
	}
}


float modone(float value)
{
	float int_part;
	
	return modff(value, &int_part);
	
}


void set_segment_color(unsigned char segment,unsigned char R,unsigned char G,unsigned char B)
{
	

int fd;
int value;

	fd = open("/sys/class/dothat/sn3218/lcd", O_WRONLY | O_APPEND);
	if(fd>0) {



		    dprintf(fd,"%d %02x%02x%02x",segment,gamma_table_blue[B],gamma_table_green[G],gamma_table_red[R]);
			//dprintf(fd,"%d %02x%02x%02x",segment,B,G,R);
	        close(fd);
	}

}

void set_all_leds(unsigned char *leds)
{
	

int fd;
int value;
int i;
char str_leds[36];
char color_str[7];

	fd = open("/sys/class/dothat/sn3218/lcd_raw", O_WRONLY | O_APPEND);
	if(fd>0) {

		memset(color_str,0,7);
		for(i=0;i<6;i++) {
			
			sprintf(color_str,"%02x%02x%02x",gamma_table_blue[leds[i*3]],gamma_table_green[leds[i*3+1]],gamma_table_red[leds[i*3+2]]);
			memcpy(str_leds+6*i,color_str,6);
			
		}
		
		    write(fd,str_leds,36);
			
	        close(fd);
	}

}

void sweep(float hue) 
{
	int i;
	float r,g,b;
	float sweep_range=0.0833;
	unsigned char leds[18];
	//float sweep_range=0.05;
	
	for(i=0;i<6;i++) {
		
		hsv2rgb(&r, &g, &b, modone(hue+(sweep_range * i)), 1.0, 1.0);
		leds[i*3]=(unsigned char)(b*255);
		leds[i*3+1]=(unsigned char)(g*255);
		leds[i*3+2]=(unsigned char)(r*255);
		
		
	}
	
    set_all_leds(leds);
}


void set_monocolor(char *dev,char *color)
{
	
int fd;
fd = open(dev, O_WRONLY | O_APPEND);
if(fd>0) {
	
	write(fd,color, 6);

	close(fd);
}

}

void setGraphValue(char *dev,int pourcentage)
{
	
int fd;
int value;

fd = open(dev, O_WRONLY | O_APPEND);
if(fd>0) {
	
	value=pourcentage*255/100;
	
				
	dprintf(fd,"%d", value);

	close(fd);
}

}

void return_pos(void)
{

int fd;
int value;

fd = open("/sys/class/dothat/st7036/cursor_position", O_WRONLY | O_APPEND);
if(fd>0) {



        dprintf(fd,"%s","0 0");

        close(fd);
}

}


void gotoline(int line)
{

int fd;
int value;

	fd = open("/sys/class/dothat/st7036/cursor_position", O_WRONLY | O_APPEND);
	if(fd>0) {



	        dprintf(fd,"0 %d",line);

	        close(fd);
	}

}





void write_str(char *dev,char *str)
{
	/*
int fd;
int value;

fd = open(dev, O_WRONLY | O_APPEND);
if(fd>0) {



        dprintf(fd,"%s", str);

        close(fd);
}
*/
	
	FILE *file;
	
	file = fopen(dev,"wb");
	if(file) {

	

	        fprintf(file,"%s", str);

	        fclose(file);
	}
	
	
}



void convertSpeedToHumanRead(char *buffer,int size_buffer,float speed)
{
	
        if(speed<0)
                snprintf(buffer,size_buffer,"N/A");
        else if(speed<(1024))
                snprintf(buffer,size_buffer,"%d o/s",(int)speed);
        else if(speed<(1048576))
                snprintf(buffer,size_buffer,"%.2f Ko/s",speed/(1024));
        else {
                snprintf(buffer,size_buffer,"%.2f Mo/s",speed/(1048576));

        }
		
        buffer[size_buffer]='\0';

}


unsigned long long getRxBytesForInterface(char *interface) {
	
	const char *rx_str_fmt="/sys/class/net/%s/statistics/rx_bytes";
	char *rx_str=NULL;
	FILE *file;
	long long rxValue=-1; 
	
	if(interface) {
		asprintf(&rx_str,rx_str_fmt,interface);
		
		
		if(rx_str) {
			
			file = fopen(rx_str,"r");
			if(file) {

			

			        fscanf(file,"%lld", &rxValue);

			        fclose(file);
			}
			
			
			free(rx_str);
		}

	}
	return rxValue;		
	
}


unsigned long long getTxBytesForInterface(char *interface) 
{
	
	const char *tx_str_fmt="/sys/class/net/%s/statistics/tx_bytes";
	char *tx_str=NULL;
	FILE *file;
	long long txValue=-1; 
	
	if(interface) {
		asprintf(&tx_str,tx_str_fmt,interface);
		
		
		if(tx_str) {
			
			file = fopen(tx_str,"r");
			if(file) {

			

			        fscanf(file,"%lld", &txValue);

			        fclose(file);
			}
			
			
			free(tx_str);
		}

	}
	return txValue;		
	
}


int main(void)
{
    const char *dev = "/dev/input/by-path/platform-3f804000.i2c-event";
    char *screenMonocolor = "/sys/class/dothat/sn3218/monocolor";
    char *graphBar="/sys/class/dothat/cap1166/graph_bar_reverse";
    char *lcd="/sys/class/dothat/st7036/lcd_buffer";
    int timeu=0;
    char buffer_str[16];

    struct tm *tm_struct;	
    time_t rawtime;
    struct input_event ev;
    ssize_t n;
    int fd;
	struct timeval tv_input;
	struct timezone tz;
	unsigned char screen_shutdown=0;
	struct timeval tvOld,tvSpeed,tvNow,tvScreen;
	long msElapsed,msElapsedSpeed,msElapsedScreen;
	long long bytesRx=0,bytesTx=0;
	
	long long totalRx,totalTx;
	float speedRx,speedTx;
	char speedTx_str[14];
	char speedRx_str[14];
	char lineBuffer[17];
	char *ptr,*ptr2;
	int rainbow_count=0;
	
	fd_set fds;
	FD_ZERO(&fds);
	
    tv_input.tv_sec = 0;
    tv_input.tv_usec = 10;
	  
    fd = open(dev, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
        return EXIT_FAILURE;
    }
	
	
	set_monocolor(screenMonocolor,YELLOW);

	gettimeofday( &tvNow, &tz );
	memcpy(&tvOld,&tvNow,sizeof(struct timeval));
	memcpy(&tvScreen,&tvNow,sizeof(struct timeval));
	
	bytesTx=getTxBytesForInterface(NET_INTERFACE);
	bytesRx=getRxBytesForInterface(NET_INTERFACE);
	memcpy(&tvSpeed,&tvNow,sizeof(struct timeval));
	
    while (1) {
		FD_ZERO(&fds);
		FD_SET(fd , &fds);
		
		if(!screen_shutdown) {
		  	gettimeofday( &tvNow, &tz );
		  	tvsub( &tvNow, &tvScreen );
			
			
			sweep(((float)360.0 - rainbow_count) / (float)360.0); 
			rainbow_count+=3;
			rainbow_count %= 360;
			msElapsedScreen=tvNow.tv_sec*1000+((float)tvNow.tv_usec/1000);//elapsed time in ms
		
			if(msElapsedScreen>20000) {
				//12 second
				set_monocolor(screenMonocolor,NOCOLOR);
				screen_shutdown=1;
			}
			
			
		}
	  	
		
		
	  	gettimeofday( &tvNow, &tz );
	  	tvsub( &tvNow, &tvOld );
		msElapsed=tvNow.tv_sec*1000+((float)tvNow.tv_usec/1000);//elapsed time in ms
		
		if(msElapsed>100){
			
			
			//refresh clock :)
			time ( &rawtime );
			tm_struct = localtime ( &rawtime );

			sprintf(buffer_str,"        %02d:%02d:%02d",tm_struct->tm_hour,tm_struct->tm_min,tm_struct->tm_sec);
		        //printf("\r%s",buffer_str);
			gotoline(0);
		    write_str(lcd,buffer_str);
			gettimeofday( &tvOld, &tz );
		
		}
		
		gettimeofday( &tvNow, &tz );
		tvsub( &tvNow, &tvSpeed );
		msElapsedSpeed=tvNow.tv_sec*1000+((float)tvNow.tv_usec/1000);//elapsed time in ms
			
	    if(msElapsedSpeed>1000) {
	    	totalTx=getTxBytesForInterface(NET_INTERFACE);
			totalRx=getRxBytesForInterface(NET_INTERFACE);
			
			speedTx=(float)(((totalTx-bytesTx)*1000)/msElapsedSpeed);
			speedRx=(float)(((totalRx-bytesRx)*1000)/msElapsedSpeed);
			convertSpeedToHumanRead(speedTx_str,14,speedTx);
			convertSpeedToHumanRead(speedRx_str,14,speedRx);
			
			
			memset(lineBuffer,' ',16);
			snprintf(lineBuffer,17,"DOWN:%s",speedRx_str);
		    lineBuffer[strlen(lineBuffer)]=' ';  
			lineBuffer[16]=0; 
			printf("%s|%s- %d\n",speedRx_str,lineBuffer,strlen(lineBuffer));
			
			
	
			gotoline(1);
			write_str(lcd,lineBuffer);
			
			
			memset(lineBuffer,' ',16);
			snprintf(lineBuffer,17," UP :%s",speedTx_str);
			lineBuffer[strlen(lineBuffer)]=' ';
			lineBuffer[16]=0; 
		    printf("%s|%s- %d\n",speedTx_str,lineBuffer,strlen(lineBuffer));
			
			gotoline(2);
			write_str(lcd,lineBuffer);
			
			 
			
			bytesTx=totalTx;
			bytesRx=totalRx;
			gettimeofday( &tvSpeed, &tz );
	    }
		
		if (select(fd+1, &fds,NULL,NULL,&tv_input)==1) {
		
		 n = read(fd, &ev, sizeof ev);
	        if (n == (ssize_t)-1) {
	            if (errno == EINTR)
	                break;
	            else
	                continue;
	        } else
	        if (n != sizeof ev) {
	            errno = EIO;
	            break;
	        }
		
		 
		
		  if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2) {
		  	printf("%s 0x%04x (%d)\n", evval[ev.value], (int)ev.code, (int)ev.code);
			
			
			if(ev.code==KEY_ENTER&&ev.value==1) {
			
			
				set_monocolor(screenMonocolor,RED);
			}
		
			if(ev.code==KEY_BACK&&ev.value==1) {
			
			
				set_monocolor(screenMonocolor,BLUE);
			}
		
			if(ev.code==KEY_UP&&ev.value==1) {
			
			
				set_monocolor(screenMonocolor,SILVER);
			}
		
			if(ev.code==KEY_DOWN&&ev.value==1) {
			
			
				set_monocolor(screenMonocolor,AQUA);
			}
		
		
			if(ev.code==KEY_LEFT&&ev.value==1) {
			
			
				set_monocolor(screenMonocolor,GREEN);
			}
	
			
            if(ev.code==KEY_RIGHT&&ev.value==1) {

			   
               set_monocolor(screenMonocolor,YELLOW);
            }	
		
		    if(ev.value==1) {
				screen_shutdown=1;
			}
			if(ev.value==0) {
			
			
				//set_monocolor(screenMonocolor,TEAL);
				sweep(0.0); 
				
				gettimeofday( &tvScreen, &tz );
				screen_shutdown=0;
			}
			
			
		  }
		
		}
		usleep(10000);
	}
		

		
//fflush(stdout);
//fprintf(stderr, "%s.\n", strerror(errno));
//return EXIT_FAILURE;
}
		
