/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: STK *******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#include "STD_Types.h"
#include "BitOperations.h"

#include "STK_Config.h"
#include "STK_Private.h"
#include "STK_Register.h"
#include "STK_Interface.h"

// Global Pointer to Function to Hold STK ISR Address
void (*STK_CallBackFunction)(void) = NULL;

static u8 Global_SingleFlag; // Single Interval Flag

void STK_Initialization (void)
{
	// Initialize Clock Source
	#if STK_ClkSource == 1
		SET_BIT(STK->CTRL, CLKSOURCE);
	#elif STK_ClkSource == 0
		CLR_BIT(STK->CTRL, CLKSOURCE);
	#endif
	
	// Counter Enable or Disable
	#if STK_Counter == 1
		SET_BIT(STK->CTRL, TICKINT);
	#elif STK_ClkSource == 0
		CLR_BIT(STK->CTRL, TICKINT);
	#endif
}

void STK_SetBusyWait (u32 Ticks)
{
	// Reset Timer value
	STK->VAL = 0 ;
	// Load Timer with value
	STK->LOAD = Ticks-1;
	// Start the Timer
	SET_BIT(STK->CTRL, ENABLE);
	
	//  Wait for Timer flag to be Raised
	while( GET_BIT(STK->CTRL, COUNTFLAG) != 1 ) {}
	
	//  Stop the Timer
	CLR_BIT(STK->CTRL, ENABLE);
}

void STK_SetInterval_Single (u32 Ticks, void (*STKFunction)(void))
{
	// Callback function
	STK_CallBackFunction = STKFunction;
	Global_SingleFlag = 1; // Single Flag is Set
	
	// Reset Timer value
	STK->VAL = 0;
	
	// Load Timer with value
	STK->LOAD = Ticks-1;
	
	// Start the Timer
	SET_BIT(STK->CTRL, ENABLE);
}

void STK_SetInterval_Periodic (u32 Ticks, void (*STKFunction)(void))
{
	// Callback function
	STK_CallBackFunction = STKFunction;
	Global_SingleFlag = 0; // Single Flag is Cleared
	
	// Reset Timer value
	STK->VAL = 0;
	
	// Load Timer with value
	STK->LOAD = Ticks-1;
	
	// Start the Timer
	SET_BIT(STK->CTRL, ENABLE);
}

u32  STK_GetElapsedTime (void)
{
	return ( (STK->LOAD) - (STK->VAL) );
}

u32  STK_GetRemainingTime (void)
{
	return (STK->VAL);
}

/** ISR of STK **/
void SysTick_Handler(void)
{
	if(STK_CallBackFunction != NULL)
		STK_CallBackFunction();
	else
	{
		/* Do Nothing */
	}
		
	if(Global_SingleFlag) // Check if Single Interval
	{
		Global_SingleFlag = 0;
		// Stop the Timer
		CLR_BIT(STK->CTRL, ENABLE);
	}
}