﻿/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: MCAL *****************************************/
/***************************************** SWC: SysTick ****************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef SysTick_Interface
#define SysTick_Interface

void SysTick_Initialization (void);

void SysTick_SetBusyWait (u32 Ticks);

void SysTick_SetInterval_Single (u32 Ticks, void (*SysTickFunction)(void));
void SysTick_SetInterval_Periodic (u32 Ticks, void (*SysTickFunction)(void));

u32 SysTick_GetElapsedTime (void);
u32 SysTick_GetRemainingTime (void);

#endif
