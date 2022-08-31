/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: HAL ******************************************/
/*************************************** Component: CLCD ***************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#include "STD_Types.h"
#include "BitOperations.h"

#include "GPIO_Interface.h"
#include "CLCD_Interface.h"
#include "CLCD_Private.h"
#include "CLCD_Config.h"

void Delay (void)	// Function Delay
{
	for(u32 i = 0 ; i< 10000 ; i++)
	{
		asm("NOP");
	}
}

u8 Counter = 0; // to Count the Number of Characters in the line

void CLCD_SendCommand (u8 Command)
{
	GPIO_ControlPinValue (ControlPort, CLCD_RS, Reset);	// Set RS to Low for Command
	GPIO_ControlPinValue (ControlPort, CLCD_RW, Reset); // Set RS to Low for Write

	// Set Command to Data Pins
	GPIO_SetPinValue( DataPort, CLCD_D0 , GET_BIT(Command,0) );
	GPIO_SetPinValue( DataPort, CLCD_D1 , GET_BIT(Command,1) );
	GPIO_SetPinValue( DataPort, CLCD_D2 , GET_BIT(Command,2) );
	GPIO_SetPinValue( DataPort, CLCD_D3 , GET_BIT(Command,3) );
	GPIO_SetPinValue( DataPort, CLCD_D4 , GET_BIT(Command,4) );
	GPIO_SetPinValue( DataPort, CLCD_D5 , GET_BIT(Command,5) );
	GPIO_SetPinValue( DataPort, CLCD_D6 , GET_BIT(Command,6) );
	GPIO_SetPinValue( DataPort, CLCD_D7 , GET_BIT(Command,7) );
	
	// Send Enable Pulse
	GPIO_ControlPinValue (ControlPort, CLCD_E, Set);

	/****************************************************/
	Delay();
	/****************************************************/

	GPIO_ControlPinValue (ControlPort, CLCD_E, Reset);
}

void CLCD_SendData (u8 Data)
{
	GPIO_ControlPinValue (ControlPort, CLCD_RS, Set); // Set RS to High for Data
	GPIO_ControlPinValue (ControlPort, CLCD_RW, Reset); // Set RS to Low for Write

	// Set Data to Data Pins
	GPIO_SetPinValue( DataPort, CLCD_D0 , GET_BIT(Data,0) );
	GPIO_SetPinValue( DataPort, CLCD_D1 , GET_BIT(Data,1) );
	GPIO_SetPinValue( DataPort, CLCD_D2 , GET_BIT(Data,2) );
	GPIO_SetPinValue( DataPort, CLCD_D3 , GET_BIT(Data,3) );
	GPIO_SetPinValue( DataPort, CLCD_D4 , GET_BIT(Data,4) );
	GPIO_SetPinValue( DataPort, CLCD_D5 , GET_BIT(Data,5) );
	GPIO_SetPinValue( DataPort, CLCD_D6 , GET_BIT(Data,6) );
	GPIO_SetPinValue( DataPort, CLCD_D7 , GET_BIT(Data,7) );
	
	// Send Enable Pulse
	GPIO_ControlPinValue (ControlPort, CLCD_E, Set);

	/****************************************************/
	Delay();
	/****************************************************/

	GPIO_ControlPinValue (ControlPort, CLCD_E, Reset);
	
	Counter++;
	if (Counter == 16)  // Go to the Second Line
		CLCD_SetCursor(1,0);

	if (Counter == 32)  // Go Back to the First Line
	{
		CLCD_SetCursor(0,0);
		Counter = 0;
	}

}

void CLCD_SendString (const char* String)
{
	// Set The Array of String to Data Pins
	int i = 0;
	while (String[i] != '\0')
	{
		CLCD_SendData (String[i]);
		i++;
	}
}

void CLCD_SendNumber (u16 Number)
{
	
	u16 ReversedNumber = 0;
	u16 Temp = Number;
	u8 digit;

	u8 Counter1 = 0;
	u8 Counter2 = 0;
	
	while (Number > 0)
	{
		// Count the Number's Digits
		digit = Number % 10;
		Number = Number/10;
		
		Counter1++;
	}

	Counter2 = Counter1;
	
	while (Counter1 > 0)
	{
		// Reverse the Number
		ReversedNumber = ReversedNumber*10 + Temp%10;

		if (ReversedNumber == 0)
			ReversedNumber =+ 10;  // to count the Zeros (will create a little bit different number but we will solve it)

		Temp = Temp/10;

		Counter1--;
	}

	while (Counter2 > 0)
	{
		// Split the Number into its Digits
		digit = ReversedNumber % 10;
		
		// Add 48 into the digit so the LCD can read its ASCII and send it
		CLCD_SendData (digit+48);
		
		ReversedNumber = ReversedNumber/10;

		Counter2--;
	}
}

void CLCD_WriteSpecialChars (u8* Pattern, u8 OverwriteBlockNumber /*Just 8 Blocks*/, u8 XPosition, u8 YPosition)
{
	u8 Address = 0;
	Address = OverwriteBlockNumber*8; // Get CGRAM Address
	
	// Set bit 6 for CGRAM Address Command then send the Command
	CLCD_SendCommand (Address + 64);
	
	// Write the Pattern into CGRAM
	for(int i=0; i<8; i++)
	CLCD_SendData (Pattern[i]);
	
	// Go Back to DDRAM to Display the Pattern
	CLCD_SetCursor (XPosition, YPosition);
	
	// Display the Pattern written in the CGRAM
	CLCD_SendData (OverwriteBlockNumber);
}

void CLCD_Initialization (void)
{
	// Wait for more than 30ms
	/****************************************************/
	Delay();
	/****************************************************/
	
	// Function Set Command: 2 Lines(bit 3), 5*7 Font Size(bit 2)
	CLCD_SendCommand (0b00111100);
	
	// Display On/Off Control: Display Enable(bit 2), Display Cursor(bit 1), Blink Cursor(bit 0)
	CLCD_SendCommand (0b00001111);
	
	// Clear Display
	CLCD_SendCommand (0b00000001);
}

void CLCD_SetCursor(u8 XPosition, u8 YPosition)
{
	u8 Address = 0;
	if (XPosition == 0)  // Location at First Line
	Address = YPosition;
	else if (XPosition == 1)  // Location at Second Line
	Address = 0x40 + YPosition;
	
	// Set bit 7 for DDRAM Address Command then send the Command
	CLCD_SendCommand(Address + 128);
}
