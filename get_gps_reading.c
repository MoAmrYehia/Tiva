#include "LCD_display.h"
#include "ports_init.h"
#include "measure_distance.h"
#include "test.h"
#include "distance_calculator.h"

#define dis 100

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
