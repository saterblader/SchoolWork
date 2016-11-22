/* ###################################################################
**     Filename    : main.c
**     Project     : KL05_Robot
**     Processor   : MKL05Z32VLC4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-02-11, 19:48, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "IMU_LCD.h"
#include "WiFi.h"
#include "IR_Range_Out.h"
#include "TU2.h"
#include "Motor_B_En.h"
#include "TU1.h"
#include "Motor_A_En.h"
#include "IR_Range_In.h"
#include "Motor_B_Ph.h"
#include "Motor_A_Ph.h"
#include "Encoder_B1.h"
#include "Encoder_B0.h"
#include "Encoder_A1.h"
#include "Encoder_A0.h"
#include "WiFi_PD.h"
#include "Button.h"
#include "Button_Init.h"
#include "Sample_IR.h"
#include "TU3.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
LDD_TDeviceData *Motor_A_En_Ptr;
LDD_TDeviceData *Motor_A_Ph_Ptr;
LDD_TDeviceData *Motor_B_En_Ptr;
LDD_TDeviceData *Motor_B_Ph_Ptr;
LDD_TDeviceData *IMU_LCD_Ptr;
LDD_TDeviceData *WIFI_PD_Ptr;
LDD_TDeviceData *WIFI_SER_Ptr;
LDD_TError Error;
volatile bool IMU_LCD_DataReceivedFlg = FALSE;
volatile bool IMU_LCD_DataTransmittedFlg = FALSE;
volatile bool WiFi_DataReceivedFlg = FALSE;
volatile bool WiFi_DataTransmitFlg = FALSE;
uint8_t LCD_Out_Data[4] = {0x00U, 0x01U, 0x02U, 0x03U};                /* Initialization of output data buffer */
uint8_t LCD_In_Data[16];
uint8_t i;

void Delay(void)
{
   int i;
   for(i=0;i<5000;i++);
}

void LCDcommand(uint8_t data)
{
	Error=IMU_LCD_SelectSlaveDevice(IMU_LCD_Ptr,LDD_I2C_ADDRTYPE_7BITS,39);
	uint8_t LCD_Out_Data[2];
	// Put data on the data bus Port A
	LCD_Out_Data[0] = 0x12U;
	LCD_Out_Data[1] = data;
	Delay();
    Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, LCD_Out_Data, 2U, LDD_I2C_SEND_STOP);
    while (!IMU_LCD_DataTransmittedFlg) {
    }
    IMU_LCD_DataTransmittedFlg = FALSE;

    // Set RS to zero for command Port B[1]
	LCD_Out_Data[0] = 0x13U;
	LCD_Out_Data[1] = 0x00U;
	Delay();
    Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, LCD_Out_Data, 2U, LDD_I2C_SEND_STOP);
    while (!IMU_LCD_DataTransmittedFlg) {
    }
    IMU_LCD_DataTransmittedFlg = FALSE;
    // Set Enable high Port B[0]
    LCD_Out_Data[0] = 0x13U;
    LCD_Out_Data[1] = 0x01U;
    Delay();
    Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, LCD_Out_Data, 2U, LDD_I2C_SEND_STOP);
    while (!IMU_LCD_DataTransmittedFlg) {
    }
    IMU_LCD_DataTransmittedFlg = FALSE;
    // Return Enable low Port B[0]
	LCD_Out_Data[0] = 0x13U;
	LCD_Out_Data[1] = 0x00U;
	Delay();
    Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, LCD_Out_Data, 2U, LDD_I2C_SEND_STOP);
    while (!IMU_LCD_DataTransmittedFlg) {
    }
    IMU_LCD_DataTransmittedFlg = FALSE;

}

void LCDwrite(uint8_t data)
{
	Error=IMU_LCD_SelectSlaveDevice(IMU_LCD_Ptr,LDD_I2C_ADDRTYPE_7BITS,39);
	uint8_t LCD_Out_Data[2];
	// Put data on the data bus Port A
	LCD_Out_Data[0] = 0x12U;
	LCD_Out_Data[1] = data;
	Delay();
    Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, LCD_Out_Data, 2U, LDD_I2C_SEND_STOP);
    while (!IMU_LCD_DataTransmittedFlg) {
    }
    IMU_LCD_DataTransmittedFlg = FALSE;

    // Set RS to one for character data Port B[1]
	LCD_Out_Data[0] = 0x13U;
	LCD_Out_Data[1] = 0x02U;
	Delay();
    Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, LCD_Out_Data, 2U, LDD_I2C_SEND_STOP);
    while (!IMU_LCD_DataTransmittedFlg) {
    }
    IMU_LCD_DataTransmittedFlg = FALSE;
    // Set Enable high Port B[0]
    LCD_Out_Data[0] = 0x13U;
    LCD_Out_Data[1] = 0x03U;
    Delay();
    Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, LCD_Out_Data, 2U, LDD_I2C_SEND_STOP);
    while (!IMU_LCD_DataTransmittedFlg) {
    }
    IMU_LCD_DataTransmittedFlg = FALSE;
    // Return Enable low Port B[0]
	LCD_Out_Data[0] = 0x13U;
	LCD_Out_Data[1] = 0x02U;
	Delay();
    Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, LCD_Out_Data, 2U, LDD_I2C_SEND_STOP);
    while (!IMU_LCD_DataTransmittedFlg) {
    }
    IMU_LCD_DataTransmittedFlg = FALSE;

}

void LCDinit(void)
{
	Error=IMU_LCD_SelectSlaveDevice(IMU_LCD_Ptr,LDD_I2C_ADDRTYPE_7BITS,39);
	uint8_t LCD_Out_Data[2];
	// Make Port A output
	LCD_Out_Data[0] = 0x00U;
	LCD_Out_Data[1] = 0x00U;
    Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, LCD_Out_Data, 2U, LDD_I2C_SEND_STOP);
    while (!IMU_LCD_DataTransmittedFlg) {
    }
    IMU_LCD_DataTransmittedFlg = FALSE;
	// Make Port B output
	LCD_Out_Data[0] = 0x01U;
	LCD_Out_Data[1] = 0x00U;
	Delay();
    Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, LCD_Out_Data, 2U, LDD_I2C_SEND_STOP);
    while (!IMU_LCD_DataTransmittedFlg) {
    }
    IMU_LCD_DataTransmittedFlg = FALSE;
    for (int j=0;j<100;j++)
    	Delay();                   //Wait >15 msec after power is applied
    LCDcommand(0x30);                //command 0x30 = Wake up
    Delay();                    //must wait 5ms, busy flag not available
    LCDcommand(0x30);                //command 0x30 = Wake up #2
    Delay();                    //must wait 160us, busy flag not available
    LCDcommand(0x30);                //command 0x30 = Wake up #3
    Delay();                    //must wait 160us, busy flag not available
    LCDcommand(0x38);                //Function set: 8-bit/2-line
    LCDcommand(0x10);                //Set cursor
    LCDcommand(0x0c);                //Display ON; Cursor ON
    LCDcommand(0x06);                //Entry mode set
    LCDcommand(0x01);				// Clear Screen
}
void LCDBacklight(void)
{
	//Turn On LCD Backlight
	Error=IMU_LCD_SelectSlaveDevice(IMU_LCD_Ptr,LDD_I2C_ADDRTYPE_7BITS,39);
	uint8_t LCD_Out_Data[2];
	LCD_Out_Data[0] = 0x13U;
	LCD_Out_Data[1] = 0x04U;
	Delay();
	Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, LCD_Out_Data, 2U, LDD_I2C_SEND_STOP);
	while (!IMU_LCD_DataTransmittedFlg) {
	}
	IMU_LCD_DataTransmittedFlg = FALSE;
}
void IMUinit(void)
{
	Delay();
	Error=IMU_LCD_SelectSlaveDevice(IMU_LCD_Ptr,LDD_I2C_ADDRTYPE_7BITS,107);
	//Setup Gyro
	uint8_t IMU_Out_Data[2];
	IMU_Out_Data[0] = 0x20U;
	IMU_Out_Data[1] = 0x0FU;
	Delay();
	Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, IMU_Out_Data, 2U, LDD_I2C_SEND_STOP);
	while (!IMU_LCD_DataTransmittedFlg) {
	}
	IMU_LCD_DataTransmittedFlg = FALSE;
	Delay();
	//Setup Accelerometer & Mag
	Error=IMU_LCD_SelectSlaveDevice(IMU_LCD_Ptr,LDD_I2C_ADDRTYPE_7BITS,29);
	Delay();
	//Enable Accel.
	IMU_Out_Data[0] = 0x20U;//CTRL1
	IMU_Out_Data[1] = 0x17U;
	Delay();
	Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, IMU_Out_Data, 2U, LDD_I2C_SEND_STOP);
	while (!IMU_LCD_DataTransmittedFlg) {
	}
	IMU_LCD_DataTransmittedFlg = FALSE;
	Delay();
	//Enable Temp.
	IMU_Out_Data[0] = 0x24U;//CTRL5
	IMU_Out_Data[1] = 0x98U;
	Delay();
	Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, IMU_Out_Data, 2U, LDD_I2C_SEND_STOP);
	while (!IMU_LCD_DataTransmittedFlg) {
	}
	IMU_LCD_DataTransmittedFlg = FALSE;
	//Enable Mag
	IMU_Out_Data[0] = 0x26U; //CTRL7
	IMU_Out_Data[1] = 0x00U;
	Delay();
	Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, IMU_Out_Data, 2U, LDD_I2C_SEND_STOP);
	while (!IMU_LCD_DataTransmittedFlg) {
	}
	IMU_LCD_DataTransmittedFlg = FALSE;
}
uint8_t IMU_Who_Am_I(void)
{
	Delay();
	Error=IMU_LCD_SelectSlaveDevice(IMU_LCD_Ptr,LDD_I2C_ADDRTYPE_7BITS,107);
	//Query Who Am I
	uint8_t IMU_Out_Data[1],WhoAmI[1];
	IMU_Out_Data[0] = 0x0FU;
	Delay();
	Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, IMU_Out_Data, 1U, LDD_I2C_NO_SEND_STOP);
	while (!IMU_LCD_DataTransmittedFlg) {
	}
	IMU_LCD_DataTransmittedFlg = FALSE;
	Error = IMU_LCD_MasterReceiveBlock(IMU_LCD_Ptr, WhoAmI, 1U, LDD_I2C_SEND_STOP);
	while (!IMU_LCD_DataReceivedFlg) {
	}
	IMU_LCD_DataReceivedFlg = FALSE;
	return WhoAmI[0];
}
void WiFiInit(void)
{
	//Enable WiFi
	WIFI_PD_Ptr = WiFi_PD_Init((LDD_TUserData *)NULL);
	WiFi_PD_PutVal(WIFI_PD_Ptr,1);
	WIFI_SER_Ptr = WiFi_Init((LDD_TUserData *)NULL);
	for (int i=0; i<1000;i++)
		Delay();
	char AT[4]= "AT\r\n";
	char OK[11]="\0\0\0\0";
	Error = WiFi_SendBlock(WIFI_SER_Ptr, AT, 4U);
	while (!WiFi_DataTransmitFlg) {                                      /* Wait until 'e' character is received */
	}
	WiFi_DataTransmitFlg = FALSE;
	Error = WiFi_ReceiveBlock (WIFI_SER_Ptr, OK, 11U);
	while (!WiFi_DataReceivedFlg) {                                      /* Wait until 'e' character is received */
	}
	WiFi_DataReceivedFlg = FALSE;
	char out[4];
	strncpy(out,OK+7,2);
	out[2]='\0';
	for (int i=0; i<strlen(out);i++)
		LCDwrite(out[i]);
	Delay();
	char *setMode="AT+CWMODE=1\r\n";
	char *AP = "AT+CWJAP=\"iot_lab\",\"44FEC4DDB9\"\r\n";
	char *getIP = "AT+CIPSTA?\r\n";
	char IPRaw [39];
	char garbageCollection[20];
	Error = WiFi_SendBlock(WIFI_SER_Ptr, setMode, strlen(setMode));
	while (!WiFi_DataTransmitFlg) {                                      /* Wait until 'e' character is received */
	}
	WiFi_DataTransmitFlg = FALSE;
	Delay();
	Error = WiFi_SendBlock(WIFI_SER_Ptr, AP, strlen(AP));
	while (!WiFi_DataTransmitFlg) {
	}
	WiFi_DataTransmitFlg = FALSE;
	Delay();
	Error = WiFi_ReceiveBlock (WIFI_SER_Ptr, garbageCollection, 2U);
	while (!WiFi_DataReceivedFlg) {
	}
	WiFi_DataReceivedFlg = FALSE;
	for (int i=0; i<2500;i++)
		Delay();
	Error = WiFi_SendBlock(WIFI_SER_Ptr, getIP, strlen(getIP));
	while (!WiFi_DataTransmitFlg) {
	}
	WiFi_DataTransmitFlg = FALSE;
	Error = WiFi_ReceiveBlock (WIFI_SER_Ptr, IPRaw, 39U);
	while (!WiFi_DataReceivedFlg) {
	}
	WiFi_DataReceivedFlg = FALSE;
	char *IPStart;
	char IP[12];
	IPStart=strchr(IPRaw,'1');
	strncpy(IP,IPStart,11);
	IP[11]='\0';
	LCDcommand(0x01);
	LCDwrite('I');
	LCDwrite('P');
	LCDwrite(':');
	for (int i=0; i<strlen(IP);i++)
			LCDwrite(IP[i]);
	Delay();


}
void GyroRead(void)
{
	uint8_t Xaddr[1];
	uint8_t result[6];
	uint16_t X,Y,Z;
	int Xs, Ys, Zs;
	Xaddr[0]=0xA8;
	Delay();
	Error=IMU_LCD_SelectSlaveDevice(IMU_LCD_Ptr,LDD_I2C_ADDRTYPE_7BITS,107);
	Delay();
	Error = IMU_LCD_MasterSendBlock(IMU_LCD_Ptr, Xaddr, 1U, LDD_I2C_NO_SEND_STOP);
	while (!IMU_LCD_DataTransmittedFlg) {
	}
	IMU_LCD_DataTransmittedFlg = FALSE;
	Error = IMU_LCD_MasterReceiveBlock(IMU_LCD_Ptr, result, 6U, LDD_I2C_SEND_STOP);
	while (!IMU_LCD_DataReceivedFlg) {
	}
	IMU_LCD_DataReceivedFlg = FALSE;
	X=(result[1]<<8)+result[0];
	Y=(result[3]<<8)+result[2];
	Z=(result[5]<<8)+result[4];
	Xs=X;
	Ys=Y;
	Zs=Z;
	char Xc[5], Yc[5], Zc[5];
	sprintf(Xc,"%u",Xs);
	sprintf(Yc,"%u",Ys);
	sprintf(Zc,"%u",Zs);
	LCDcommand(0x02);
	LCDwrite('X');
	LCDwrite(':');
	for(int j=0;j<strlen(Xc);j++)
		LCDwrite(Xc[j]);
	LCDwrite(' ');
	LCDwrite('Y');
	LCDwrite(':');
	for(int j=0;j<strlen(Yc);j++)
		LCDwrite(Yc[j]);
	LCDwrite(' ');
	LCDcommand(0xc0);
	LCDwrite('Z');
	LCDwrite(':');
	for(int j=0;j<strlen(Zc);j++)
		LCDwrite(Zc[j]);
	LCDwrite(' ');
	Delay();
}
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

  //Motor Test - Spin in circle
  /*
  Motor_A_Ph_Ptr = Motor_A_Ph_Init((LDD_TUserData *)NULL);
  Motor_A_En_Ptr = Motor_A_En_Init(NULL);
  Motor_A_Ph_PutVal(Motor_A_Ph_Ptr,1);
  Motor_A_En_SetRatio16(Motor_A_En_Ptr,32000);
  Motor_B_Ph_Ptr = Motor_B_Ph_Init((LDD_TUserData *)NULL);
  Motor_B_En_Ptr = Motor_B_En_Init(NULL);
  Motor_B_Ph_PutVal(Motor_B_Ph_Ptr,1);
  Motor_B_En_SetRatio16(Motor_A_En_Ptr,32000);
  */

  IMU_LCD_Ptr = IMU_LCD_Init(NULL);
  //Not Sure if this is still required...
  for(i=0;i<250;i++){
	  Delay();
  }
  LCDinit();
  IMUinit();
  //WiFiInit();

  //Dump Gyro To LCD
  /*
  while(TRUE)
  {
	  GyroRead();
	  //for (int j=0;j<100;j++)
		  //Delay();
  }
  */

  //Print WHOAMI to LCD
  /*
  uint8_t WhoAmI;
  WhoAmI=IMU_Who_Am_I();
  char printout[4];
  char *Text="Who Am I= \0";
  sprintf(printout,"%u",WhoAmI);
  for(int j=0;j<strlen(Text);j++)
	  LCDwrite(Text[j]);
  for(int j=0; j<3;j++)
	  LCDwrite(printout[j]);
   */

  //LCD Hello World!
  /*
  LCDwrite('H');
  LCDwrite('E');
  LCDwrite('L');
  LCDwrite('L');
  LCDwrite('O');
  LCDwrite(' ');
  LCDwrite('W');
  LCDwrite('O');
  LCDwrite('R');
  LCDwrite('L');
  LCDwrite('D');
  LCDwrite('!');
  */


  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
