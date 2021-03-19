/* 
 * File:   lcd.h
 * Author: mintron
 *
 * Created on March 11, 2021, 10:23 AM
 */

#include "mu810.h"

#ifndef E1632_LCD_H
#define	E1632_LCD_H

#ifndef _XTAL_FREQ // No clock frequency = no go
#error "ERROR - No Clock Frequency Specified - Please specify _XTAL_FREQ"
#endif

#ifndef PERIPHERAL_CLOCK
#define PERIPHERAL_CLOCK (_XTAL_FREQ / 2)
#endif

/* This defines the number of cycles per loop through the delay routine.  Spans
 * between 12-18 depending on optimization mode.*/
#define CYCLES_PER_DELAY_LOOP 12

/* Private Definitions ***********************************************/

/* Define a delay for the various time intervals required between various signal
 * transitions (E pulse, R/W setup, etc.).  This will be rounded up to 1us for 
 * the sake of easy calculation though all of these are less than that
 * typically 60-300ns. */
#define LCD_SIGNAL_TIMING         (((PERIPHERAL_CLOCK/1000)*1)/1000)/CYCLES_PER_DELAY_LOOP

// Define a fast instruction execution time in terms of loop time
// typically > 40us
#define LCD_F_INSTR         (((PERIPHERAL_CLOCK/1000)*40)/1000)/CYCLES_PER_DELAY_LOOP

// Define a slow instruction execution time in terms of loop time
// typically > 1.64ms
#define LCD_S_INSTR         (((PERIPHERAL_CLOCK/1000)*1640)/1000)/CYCLES_PER_DELAY_LOOP

// Define the startup time for the LCD in terms of loop time
// typically > 60ms (double than 8 bit mode)
#define LCD_STARTUP         (((PERIPHERAL_CLOCK/1000)*60000)/1000)/CYCLES_PER_DELAY_LOOP

#define LCD_MAX_COLUMN      16

#define LCD_SendData(data) { PMADDR = 0x0001; PMDIN1 = data; LCD_Wait(LCD_F_INSTR); }
#define LCD_SendCommand(command, delay) { PMADDR = 0x0000; PMDIN1 = command; LCD_Wait(delay); }
#define LCD_COMMAND_CLEAR_SCREEN        0x01
#define LCD_COMMAND_RETURN_HOME         0x02
#define LCD_COMMAND_ENTER_DATA_MODE     0x06
#define LCD_COMMAND_CURSOR_OFF          0x0C
#define LCD_COMMAND_CURSOR_ON           0x0F
#define LCD_COMMAND_MOVE_CURSOR_LEFT    0x10
#define LCD_COMMAND_MOVE_CURSOR_RIGHT   0x14
#define LCD_COMMAND_SET_MODE_8_BIT      0x38
#define LCD_COMMAND_ROW_0_HOME          0x80
#define LCD_COMMAND_ROW_1_HOME          0xC0

/*********************************************************************
* Function: bool LCD_Initialize(void);
*
* Overview: Initializes the LCD screen.  Can take several hundred
*           milliseconds.
*
* PreCondition: none
*
* Input: None
*
* Output: true if successful, false otherwise
*
********************************************************************/
bool lcd_init(void);

/*********************************************************************
* Function: void LCD_PutString(char* inputString, uint16_t length);
*
* Overview: Puts a string on the LCD screen.  Unsupported characters will be
*           discarded.  May block or throw away characters is LCD is not ready
*           or buffer space is not available.  Will terminate when either a
*           null terminator character (0x00) is reached or the length number
*           of characters is printed, which ever comes first.
*
* PreCondition: already initialized via LCD_Initialize()
*
* Input: char* - string to print
*        uint16_t - length of string to print
*
* Output: None
*
********************************************************************/
void lcd_puts(char* inputString, uint16_t length);

/*********************************************************************
* Function: void LCD_PutChar(char);
*
* Overview: Puts a character on the LCD screen.  Unsupported characters will be
*           discarded.  May block or throw away characters is LCD is not ready
*           or buffer space is not available.
*
* PreCondition: already initialized via LCD_Initialize()
*
* Input: char - character to print
*
* Output: None
*
********************************************************************/
void lcd_putc(char);

/*********************************************************************
* Function: void LCD_ClearScreen(void);
*
* Overview: Clears the screen, if possible.
*
* PreCondition: already initialized via LCD_Initialize()
*
* Input: None
*
* Output: None
*
********************************************************************/
void lcd_cls(void);

/*********************************************************************
* Function: void LCD_CursorEnable(bool enable)
*
* Overview: Enables/disables the cursor
*
* PreCondition: None
*
* Input: bool - specifies if the cursor should be on or off
*
* Output: None
*
********************************************************************/
void lcd_cursor(bool enable);

#endif	// E1632_LCD_H

