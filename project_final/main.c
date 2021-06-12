

/* GPS
 * TX-->PD6
 * RX-->PD7
 * Vcc--> 3.3V
 */
 
 
#include "blutooth.h"
#include "ports_init.h"
#include "LCD_display.h"
#include "measure_distance.h"
#include "test.h"
#include "distance_calculator.h"


#define dis 450


double coordinates[4];
uint32_t t[4];

uint32_t f=0;


char* saatAyarla(char str[]);
void readGPSModule();

int main(void)
{
	double Distance=0.0,display=0.0,v=0.0;
	char arr[sizeof(display)];
	char arr_v[sizeof(v)];
	uint32_t i;
	//double a=2.65;
	//char darr[sizeof(a)];
	//memcpy(darr,&a,sizeof(a));
	
	
	Systic_init();
  portA_init();
	portB_init();
	portD_init();
	portE_init();
	portF_init();
	LCD_INIT();
	HC05_init();
	
    //----------------------------UART initialization------------------------//
		SYSCTL->RCGCUART |=  (1<<0); //enable clock for UART0  port A
    SYSCTL->RCGCGPIO |=   (1<<0);  //  8;
    GPIOA->AFSEL |=        (1<<1)|(1<<0);        //port 1,2
    GPIOA->PCTL |=     (1<<0)|(1<<4);    
    GPIOA->DEN |=       (1<<0)|(1<<1);          

    UART0->CTL &=  ~(1<<0);      
    //after calculationg baudrate
    UART0->IBRD =104;
    UART0->FBRD =11;

    UART0->LCRH |=0x70;//  (0x3<<5)|(1<<4);       
    UART0->CC= 0x0;
    UART0->CTL =	 0x301;//(1<<0)|(1<<8)|(1<<9);			
		
		

    SYSCTL->RCGCUART |=  (1<<2);//4; //enable clock for UART2  port D
    SYSCTL->RCGCGPIO |=   (1<<3);  //  8;
	    
    GPIOD->AFSEL |=   0xC0;//(1<<6)|(1<<7);   //port 6,7
    GPIOD->PCTL |= 0x11000000;//(GPIOD->PCTL& 0x00FFFFFF)+0x22000000;//|=   0xC0;
    GPIOD->DEN |=  0xC0;   // (1<<6)|(1<<7);
		//GPIOD->AMSEL &=~0xC0;
		UART2->CTL &=~(1<<0);      //~(0x20);
	//after calculationg baudrate
    UART2->IBRD =0x00000145;
    UART2->FBRD =0x00000021;

    UART2->LCRH |=  0x70; //(0x3<<5)|(1<<4);       //0x60; //desired serial parameter
    UART2->CC= 0x0;        //select system clock
    UART2->CTL = 0x301;	 //(1<<0)|(1<<8)|(1<<9);			//0x301;  //enable UART by setting UARTEN bi in the UARTCTL REG
		

    
		// configration of leds
		SYSCTL->RCGCGPIO |=0x20;
		GPIOF->DIR |= 0x0E;  //MAKE LEDS
		GPIOF->DEN |=0x0E;
		GPIOF->DATA &=~ 0x0E;  // LEDS OFF
		

    while(Distance<dis)
    {
			/
			LCD_CMD(0x01);
			LCD_CMD(0x80);
			Delay_Milli(500);
			
		
        readGPSModule();
			
				
			if(f==4)
			{
				
				Distance+=distance(coordinates[0],coordinates[1],coordinates[2],coordinates[3]);
				coordinates[0]=coordinates[2];
				coordinates[1]=coordinates[3];
				f=2;
			}
			
			display=Distance;
			
			
			
			
			//memcpy(arr,&display,sizeof(display));
			sprintf(arr,"%f",display);
			for(i=0;i<6;i++)
			{
				
				LCD_WRITE(arr[i]);
				Delay_Milli(1);
			}
			if(Distance>dis)
			{
				
				v=velocity(t[0],t[2],t[1],t[3],Distance);
				sprintf(arr_v,"%f",v);
				
				GPIOF->DATA |=0x02;
				LCD_CMD(0xC0);
				Delay_Milli(500);
				for(i=0;i<6;i++)
				{
						LCD_WRITE(arr_v[i]);
						Delay_Milli(1);
				}
				
				
				
			}
			Delay_Milli(3000);  //30000
			
			
			
    }
		
	
		
		


}



void readGPSModule(void){
    char c0,GPSValues[100],latitudeResult[10],longitudeResult[10],parseValue[12][20],*token,tarih[9],*saat,guncelSaat[9],min[2],sec[2];
		char *C;
	char  send[10];
    double latitude=0.0,longitude=0.0,seconds=0.0,result=0.0,minutes=0.0;
    const char comma[2] = ",";
    int index=0,degrees,i=0,j=0,tt=0;
	int ss=0;
while(c0!='$')
{
    while((UART2->FR &0x10)!=0);
	c0= UART2->DR;
	
}

    //recived data $GPRMC 

    if(c0=='$'){
			
				char c1;
			while(c1!='G')
{
        while((UART2->FR & 0x10)!=0);
			c1=UART2->DR;
			
}
        
        if(c1=='G'){
						char c2;
					while(c2!='P')
{
            while((UART2->FR & 0x10)!=0);
            c2=UART2->DR;
					
}
            if(c2=='P'){
								char c3;
							while(c3!='R')
{
                while((UART2->FR & 0x10)!=0);
                c3=UART2->DR;
							
}
                if(c3=='R'){
										char c4;
									while(c4!='M')
{
                    while((UART2->FR & 0x10)!=0);
                    c4=UART2->DR;
									
}
                    if(c4=='M'){
											char c5;
											while(c5!='C')
{
                        while((UART2->FR & 0x10)!=0);
                        c5=UART2->DR;
										
}
                        if(c5=='C'){
														char c6;
													while(c6!=',')
{
                            while((UART2->FR & 0x10)!=0);
                            c6=UART2->DR;
													
}
                            if(c6==','){
																char c7;
														
															
                                while((UART2->FR & 0x10)!=0);
                                c7=UART2->DR;
															
														

                                //GET  gps values as array and check sum
															
                                while(c7!='*'){
                                    GPSValues[index]=c7;
                                    while((UART2->FR & 0x10)!=0);
                                    c7=UART2->DR;
                                    index++;}

																
                                //GPSValues arrayindeki verileri virgul e gore ayirma
                                index=0;
                                token = strtok(GPSValues, comma);
                                while( token != NULL ) {
                                    strcpy(parseValue[index], token);
                                    token = strtok(NULL, comma);
                                    index++;}


                                for(ss=0;ss<6;ss++)
																		{
																			
																			
																		if(strcmp(parseValue[ss],"A")==0&&(parseValue[ss+1][0]=='3')){
																			latitude =strtod(parseValue[ss+1],&C);
																			longitude=strtod(parseValue[ss+3],&C);
                                    //latitude=atof(parseValue[ss+1]);  MAKE A PROPLEM
                                   // longitude=atof(parseValue[ss+3]);


                                    //latitude calculation
                                    degrees=latitude/100;
                                    minutes=latitude-(double)(degrees*100);
                                    seconds=minutes/60.00;
                                    result=degrees+seconds;
                                    sprintf(latitudeResult,"%f", result);


                                    //longitude calculation
                                    degrees=longitude/100;
                                    minutes=longitude-(double)(degrees*100);
                                    seconds=minutes/60.00;
                                    result=degrees+seconds;
                                    sprintf(longitudeResult, "%f", result);


                                    
                                    for(i=0;i<6;i++){
                                        tarih[j]=parseValue[index-2][i];
                                        if(i==1 || i==3){
                                            j++;
                                            tarih[j]='/';}
                                        j++;}
                                    tarih[8]='\0';


                                    
																				
                                    saat=saatAyarla(parseValue[ss-1]);
                                    j=0;
                                    for(i=0;i<6;i++){
                                        guncelSaat[j]=saat[i];
                                        if(i==1 || i==3){
                                            j++;
                                            guncelSaat[j]=':';}
                                        j++;}
                                    guncelSaat[8]='\0';
																				
																	
																		while(tt<2)
																		{
																			min[tt]=guncelSaat[3+tt];
																			tt++;
																		}
																		tt=0;
																		while(tt<2)
																		{
																			sec[tt]=guncelSaat[6+tt];
																			tt++;
																		}
																				
																		if(f==0)
																		{
																			
																			t[0]=atoi(min);
																			t[1]=atoi(sec);
																		}
																		else
																		{
																			t[2]=atoi(min);
																			t[3]=atoi(sec);
																		}
																				
																				
																		
																			coordinates[f]=atof(latitudeResult);
																				
																				Blutooth_Write(' ');
																				//Delay_Milli(10);
																				sprintf(send,"%f",coordinates[f]);
																				Blutooth_Write('T');
																				Blutooth_Write_String(send);
																				f++;
																			coordinates[f]=atof(longitudeResult);
																				//Delay_Milli(10);
																				
																				Delay_Milli(10);
																				sprintf(send,"%f",coordinates[f]);
																				Blutooth_Write('N');
																				Blutooth_Write_String(send);
																				Delay_Milli(100);
																				f++;
																				
																				Systic_Wait(80000000/6);  /////////////////////change
																				//Delay_Milli(80000000/6);
																					//SysCtlDelay(80000000/6);
																				break;
																				
																				
																		
																				}
                                else{
																	//LCD_WRITE('v');
                                 
																	}}

                             //   printf("");
                        }}}}}}}
		else{
			Print_String("fault");
																
																	}
		
}


char* saatAyarla(char str[]){
    int num10 = str[0]-'0';
    int num1 = str[1]-'0';
    int saatVerisi=num10*10+num1;

    saatVerisi=saatVerisi+3;
    if(saatVerisi>24){
        saatVerisi=saatVerisi%24;
        if(saatVerisi<10){
            str[0]='0';
            str[1]=saatVerisi+'0';}
        else{
            str[0]=(saatVerisi/10)+'0';
            str[1]=(saatVerisi%10)+'0';}}
    else{
        str[0]=(saatVerisi/10)+'0';
        str[1]=(saatVerisi%10)+'0';}
    return str;
}
