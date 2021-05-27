#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

/* GPS
 * TX-->PD6
 * RX-->PD7
 * Vcc--> 3.3V
 */

#include<ports_init.h>

char* saatAyarla(char str[]);
void readGPSModule();

int main(void)
{
    //----------------------------UART initialization------------------------//
    SYSCTL->RCGCUART |= 4; //enable clock for UART2  port D
    SYSCTL->RCGCGPIO |= 8;
    GPIOD->AFSEL |= 0xC0;   //port 6,7
    GPIOD->PCTL |= 0xC0;
    GPIOD->DEN |= 0xC0;

    UART2->CTL &= ~(0x20);
    //after calculationg baudrate
    UART2->IBRD =104;
    UART2->FBRD =11;

    UART2->LCRH =0x60; //desired serial parameter
    UART2->CC= 0x00;
   // UART2->CTL =0x301;

    while(1)
    {
        readGPSModule();
    }


}


void readGPSModule(void){
    char c0,GPSValues[100],latitudeResult[10],longitudeResult[10],parseValue[12][20],*token,tarih[9],*saat,guncelSaat[9];
    double latitude=0.0,longitude=0.0,seconds=0.0,result=0.0,minutes=0.0;
    const char comma[2] = ",";
    int index=0,degrees,i=0,j=0;

    while((UART2->FR &0x20)!=0);
    c0= UART2->DR

    //gelen data $GPRMC mi?
    if(c0=='$'){
        while((UART2->FR & 0x20)!=0);
        char c1=UART2->DR;
        if(c1=='G'){
            while((UART2->FR & 0x20)!=0);
            char c2=UART2->DR;
            if(c2=='P'){
                while((UART2->FR & 0x20)!=0);
                char c3=UART2->DR;
                if(c3=='R'){
                    while((UART2->FR & 0x20)!=0);
                    char c4=UART2->DR;
                    if(c4=='M'){
                        while((UART2->FR & 0x20)!=0);
                        char c5=UART2->DR;
                        if(c5=='C'){
                            while((UART2->FR & 0x20)!=0);
                            char c6=UART2->DR;
                            if(c6==','){
                                while((UART2->FR & 0x20)!=0);
                                char c7=UART2->DR;

                                //GET  gps values as array and check sum
                                while(c7!='*'){
                                    GPSValues[index]=c7;
                                    while((UART2->FR & 0x20)!=0);
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




                                    printf("Saat  = %s\n",guncelSaat);
                                    printf("Tarih = %s\n",tarih);
                                    printf("Enlem = %s\n",latitudeResult);
                                    printf("Boylam= %s\n\n\n",longitudeResult);
                                    //SysCtlDelay(SysCtlClockGet()/6);}
                                else{
                                    printf("  GPS Verileri Okunuyor\n\n\n");}

                                printf("");
                        }}}}}}}
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
