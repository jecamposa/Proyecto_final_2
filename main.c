/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F46K40
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include<stdio.h>
#include "ESTADO.h"
#include "filtro.h"
#define EEPROM_DEVICE_ADDRESS 0x39

/*
                         Main application
 */
char INTEPT=0;
int pp=0;
int PROM =0;
int accionnn;
bool tengo_dato_serial;
char ok;
int CC=0;
int FIL;
float filtrado_iirr;
int sigg_filt;
int select=1;
char bloque[2];
void SPI_W(unsigned int datos);
unsigned int convertedValue;
void fin_adc();
int adc12bits;
void ready_fun();
int datos;
int btemp;
float temp;
long bhum;
float hum;
char mem[3002];
int recor=0;
float lina=65536;
float lina1=256;
float penelope=1048576;
int x1,x2,x3;
int kok=0;
 long humm;
 long mpet;
  uint8_t i=0;
  char dataaaa;
    uint8_t receiveData[15];
    //uint8_t i=0;
    uint8_t sendData[17] = {0xAC,0x33,0,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF};
  
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    //ADPCH=channel_ANB0;
    //SPI1_Open(SPI1_DEFAULT);
    RB4=1;
    RE0=1;
//    adc12bits=convertedValue<<2;
//    datos=0x1000|adc12bits;
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    ADPCH=channel_ANA0;

    TMR2_Start();
    ADCC_SetADIInterruptHandler(fin_adc);
   // recepcion rece;
//   EUSART1_Receive_ISR(ready_fun);
   // inicializarRecepcion(&rece);
  mem[0]=0;
    mem[1]=0;
    while (1)
    {
        if(EUSART1_is_rx_ready()){
        accionnn=EUSART1_Read()-48;
        }
        
   // CLRWDT();
    
       
        if(INTEPT){
            INTEPT=0; 
            PROM = PROM +FIL;
            CC++;
         //printf("%d",convertedValue);
        }
    if(CC==16){
        CC=0;
    PROM = PROM/16;
    mem[recor]=PROM;
    recor++;
  if(accionnn==1){
     EUSART1_Write(65); //A
    EUSART1_Write(PROM>>8);
   EUSART1_Write(PROM & 0x00FF);
  }
      PROM =0;
    }
          if(recor==1002){
            
              recor=2;
              i2c_writeNBytes(EEPROM_DEVICE_ADDRESS,mem,1002);
                // printf("\n OK");
                      
          }
  if(accionnn==3){
      i2c_writeNBytes(EEPROM_DEVICE_ADDRESS,mem,1002);
              for(int po =0; po<1000;po++){
                    EUSART1_Write(10);
                    i2c_readNBytes(EEPROM_DEVICE_ADDRESS,&dataaaa,1);
                    printf("%d", mem[po+2]); 
                }
  }
    if(accionnn==2){
        accionnn=88;
         while(!I2C1_Open(0b00111000)); // sit here until we get the bus..
    I2C1_SetBuffer(sendData,3);
    I2C1_SetAddressNackCallback(NULL,NULL); //NACK polling?
    I2C1_MasterWrite();
//    while(I2C1_BUSY == I2C1_Close()); // sit here until finished.
//    
//      while(!I2C1_Open(0b00111000)); // sit here until we get the bus..
    I2C1_SetBuffer(receiveData,7);
    I2C1_MasterRead();
    while(I2C1_BUSY == I2C1_Close()); 
	    
  humm=receiveData[1];
  humm = humm<<8;
  humm = humm|receiveData[2];
  humm = humm<<4;
  humm = humm|(receiveData[3] >> 4);
  hum = ((float)humm * 100) / 0x100000;
  while(kok<100){
  mpet = receiveData[3]&0x0F;
  mpet= mpet<<8;
  mpet = mpet|receiveData[4];
  mpet = mpet<<8;
  mpet = mpet|receiveData[5];
  temp = ((float)mpet * 200 / 0x100000)-50;
   printf("\n%f", temp);
   kok++;
    }
    }

        
   } 
}
void fin_adc(){
    ADPCH=0;
    FIL =ADCC_GetFilterValue();
    //convertedValue=(adc_result_t)((ADRESH << 8) + ADRESL);
    PIR4bits.TMR2IF=0;
    INTEPT=1;
    PIR1bits.ADIF=0;
}

void ready_fun(){
    tengo_dato_serial=true;
}

/**
 End of File
*/