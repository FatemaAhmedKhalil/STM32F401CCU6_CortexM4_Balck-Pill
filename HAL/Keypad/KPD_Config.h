/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: HAL ******************************************/
/************************************** Component: Kaypad **************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

/****************************************************************/
/* Define The KPD Port		-->		PORT_A or PORT_B		    */
/*         ** From GPIO Interface **							*/
/*																*/
/* Define The KPD Pins for Columns and Rows					    */
/* Define The KPD Values Array					   			    */
/* Define The Initial Value of Keys ( No Press State)		    */
/****************************************************************/

#ifndef KPD_Config
#define KPD_Config

#define KPD_PORT	 GPIO_B

#define NoPressedKeys	0xff

#define KPD_Array		 {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}}

#define KPD_Column0PIN	PIN5
#define KPD_Column1PIN	PIN2
#define KPD_Column2PIN	PIN1
#define KPD_Column3PIN	PIN0

#define KPD_Row0PIN		PIN6
#define KPD_Row1PIN		PIN7
#define KPD_Row2PIN		PIN8
#define KPD_Row3PIN		PIN9

#endif
