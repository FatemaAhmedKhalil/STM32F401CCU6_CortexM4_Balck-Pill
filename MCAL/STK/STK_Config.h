/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: STK *******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef STK_Config
#define STK_Config

/************************************************************************/
/* Initialize Counter Enable or Disable									*/
/*		- STK_Interrupt:												*/
/*			--> Counter Enable		1									*/
/*			--> Counter Disable		0									*/
/************************************************************************/
#define STK_Counter	1

/************************************************************************/
/* Initialize Clock Source												*/
/*			-->  Processor clock (AHB)		1							*/
/*			-->  AHB/8						0							*/
/************************************************************************/
#define STK_ClkSource	1

#endif