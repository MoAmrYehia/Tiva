

/* GPS
 * TX-->PD6
 * RX-->PD7
 * Vcc--> 3.3V
 */
 
 

//Include Libraries
#include "LCD_display.h"
#include "ports_init.h"
#include "measure_distance.h"
#include "test.h"
#include "distance_calculator.h"

#define dis 100


double coordinates[4];
uint32_t f=0;


char* saatAyarla(char str[]);
void readGPSModule();

int main(void)
{
	double Distance=0.0,display=0.0;
	char arr[6];
	
	Systic_init();
  portA_init();
	portB_init();
	portD_init();
	portE_init();
	portF_init();
	LCD_INIT();
	
    //----------------------------UART0 initialization------------------------//
		SYSCTL->RCGCUART |=  (1<<0); //enable clock for UART0  port A
    SYSCTL->RCGCGPIO |=   (1<<0);  
    GPIOA->AFSEL |=        (1<<1)|(1<<0);     //port PA0,PA1
    GPIOA->PCTL |=     (1<<0)|(1<<4);    
    GPIOA->DEN |=       (1<<0)|(1<<1);         

    UART0->CTL &=  ~(1<<0);      
    //after calculationg baudrate
    UART0->IBRD =104;
    UART0->FBRD =11;

    UART0->LCRH |=0x70;//  (0x3<<5)|(1<<4);       
    UART0->CC= 0x0;
    UART0->CTL =	 0x301;//(1<<0)|(1<<8)|(1<<9);			
		
		
 //----------------------------UART2 initialization------------------------//
    SYSCTL->RCGCUART |=  (1<<2);//4; //enable clock for UART2  port D
    SYSCTL->RCGCGPIO |=   (1<<3);  //  8;
	    
    GPIOD->AFSEL |=   0xC0; //(1<<6)|(1<<7);   //port 6,7
    GPIOD->PCTL |= 0x11000000; //(GPIOD->PCTL& 0x00FFFFFF)+0x22000000;//|=   0xC0;
    GPIOD->DEN |=  0xC0;   // (1<<6)|(1<<7);
		//GPIOD->AMSEL &=~0xC0;
		UART2->CTL &=~(1<<0);      //~(0x20);
	//after calculationg baudrate
    UART2->IBRD =0x00000145;
    UART2->FBRD =0x00000021;

    UART2->LCRH |=  0x70;         //desired serial parameter
    UART2->CC= 0x0;        //select system clock
    UART2->CTL = 0x301;	 //(1<<0)|(1<<8)|(1<<9);			//0x301;  //enable UART by setting UARTEN bi in the UARTCTL REG
		

    
		// configration of leds
		SYSCTL->RCGCGPIO |=0x20;
		GPIOF->DIR |= 0x0E;  //MAKE LEDS
		GPIOF->DEN |=0x0E;
		GPIOF->DATA &=~ 0x0E;  // LEDS OFF
		

    while(Distance<dis)
    {
			//int n=7;
			//char ccc=n+'0';
		
		//Delay_Milli(500);
		//LCD_WRITE(ccc);
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
			Delay_Milli(30000);
			
			memcpy(arr,&display,sizeof(display));
			for(uint32_t i=0;i<6;i++)
			{
				
				LCD_WRITE(arr[i]);
				Delay_Milli(1);
			}
			
			
			
    }
		
	/*
		LCD_CMD(0x01);
		LCD_CMD(0x80);
		Delay_Milli(500);
		LCD_WRITE('H');
		Delay_Milli(1);
		LCD_WRITE('E');
		Delay_Milli(1);
		LCD_WRITE('L');
		Delay_Milli(1);
		LCD_WRITE('O');
		Delay_Milli(1);
		LCD_WRITE('O');
		Delay_Milli(1);
		LCD_WRITE(' ');
		Delay_Milli(1);
		LCD_WRITE('W');
		Delay_Milli(1);
		LCD_WRITE('O');
		Delay_Milli(1);
		LCD_WRITE('R');
		Delay_Milli(1);
		LCD_WRITE('L');
		Delay_Milli(1);
		LCD_WRITE('D');
		Delay_Milli(1);*/
		/*
		LCD_WRITE(4);
		Delay_Milli(1);*/
		
		
GPIOF->DATA |=0x02;

}



void readGPSModule(void){
    char c0,GPSValues[100],latitudeResult[10],longitudeResult[10],parseValue[12][20],*token,tarih[9],*saat,guncelSaat[9];
	
    double latitude=0.0,longitude=0.0,seconds=0.0,result=0.0,minutes=0.0;
    const char comma[2] = ",";
    int index=0,degrees,i=0,j=0;
while(c0!='$')
{
    while((UART2->FR &0x10)!=0);
	c0= UART2->DR;
	//Print_Char(c0);
}

    //recived data $GPRMC 

    if(c0=='$'){
			
				char c1;
			while(c1!='G')
{
        while((UART2->FR & 0x10)!=0);
			c1=UART2->DR;
			//Print_Char(c1);
}
        
        if(c1=='G'){
						char c2;
					while(c2!='P')
{
            while((UART2->FR & 0x10)!=0);
            c2=UART2->DR;
					//Print_Char(c2);
}
            if(c2=='P'){
								char c3;
							while(c3!='R')
{
                while((UART2->FR & 0x10)!=0);
                c3=UART2->DR;
							//Print_Char(c3);
}
                if(c3=='R'){
										char c4;
									while(c4!='M')
{
                    while((UART2->FR & 0x10)!=0);
                    c4=UART2->DR;
									//Print_Char(c4);
}
                    if(c4=='M'){
											char c5;
											while(c5!='C')
{
                        while((UART2->FR & 0x10)!=0);
                        c5=UART2->DR;
										//	Print_Char(c5);
}
                        if(c5=='C'){
														char c6;
													while(c6!=',')
{
                            while((UART2->FR & 0x10)!=0);
                            c6=UART2->DR;
													//Print_Char(c6);
}
                            if(c6==','){
																char c7;
														
															
                                while((UART2->FR & 0x10)!=0);
                                c7=UART2->DR;
															
														//	Print_Char(c7);

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


                                //parseValue[1] = A ise veri gecerli - V ise gecerli degil
                                if(strcmp(parseValue[1],"A")==0){
																	
                                    latitude=atof(parseValue[2]);
                                    longitude=atof(parseValue[4]);


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


                                    //printf("https://www.google.com/maps/place/%s+%s \n",latitudeResult,longitudeResult);
                                    //tarih duzeltme
                                    for(i=0;i<6;i++){
                                        tarih[j]=parseValue[index-2][i];
                                        if(i==1 || i==3){
                                            j++;
                                            tarih[j]='/';}
                                        j++;}
                                    tarih[8]='\0';


                                    //saat düzeltme +3 UTC ayarlama
                                    saat=saatAyarla(parseValue[0]);
                                    j=0;
                                    for(i=0;i<6;i++){
                                        guncelSaat[j]=saat[i];
                                        if(i==1 || i==3){
                                            j++;
                                            guncelSaat[j]=':';}
                                        j++;}
                                    guncelSaat[8]='\0';
																				
																		Print_String(latitudeResult);
																		Print_String("\n\r");
																		Print_String(longitudeResult);
																			Print_String("\n\r");
																		Print_String(tarih);
																				Print_String("\n\r");
																				
																		
																			coordinates[f]=atof(latitudeResult);
																				f++;
																			coordinates[f]=atof(longitudeResult);
																				f++;
																					
																				
																				
																				
																		
																				}
                                else{
																	LCD_WRITE('v');
                                 
																	}

                             //   printf("");
                        }}}}}}}
		else{
																Delay_Milli(500);
																	LCD_WRITE('v');
                                    //printf("  GPS Verileri Okunuyor\n\n\n");
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
