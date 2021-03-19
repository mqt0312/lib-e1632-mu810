
/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/

#include <xc.h>

#include <stdbool.h>

#include "buttons.h"

/*********************************************************************
* Function: bool BUTTON_IsPressed(BUTTON button);
*
* Overview: Returns the current state of the requested button
*
* PreCondition: button configured via BUTTON_SetConfiguration()
*
* Input: BUTTON button - enumeration of the buttons available in
*        this demo.  They should be meaningful names and not the names 
*        of the buttonsBUTTON_NONE, on the silk-screen on the board (as the demo 
*        code may be ported to other boards).
*         i.e. - ButtonIsPressed(BUTTON_SEND_MESSAGE);
*
* Output: TRUE if pressed; FALSE if not pressed.
*
********************************************************************/
bool button_get(BUTTON button)
{
    switch(button)
    {
        case BUTTON_S3:
            return ( (S3_PORT == BUTTON_PRESSED) ? true : false);

        case BUTTON_S6:
            return ( (S6_PORT == BUTTON_PRESSED) ? true : false);

        case BUTTON_S5:
            return ( (S5_PORT == BUTTON_PRESSED) ? true : false);

        case BUTTON_S4:
            return ( (S4_PORT == BUTTON_PRESSED) ? true : false);

        default:
            return false;
    }
    
    return false;
}

/*********************************************************************
* Function: void BUTTON_Enable(BUTTON button);
*
* Overview: Returns the current state of the requested button
*
* PreCondition: button configured via BUTTON_SetConfiguration()
*
* Input: BUTTON button - enumeration of the buttons available in
*        this demo.  They should be meaningful names and not the names
*        of the buttons on the silk-screen on the board (as the demo
*        code may be ported to other boards).
*         i.e. - ButtonIsPressed(BUTTON_SEND_MESSAGE);
*
* Output: None
*
********************************************************************/
void button_en(BUTTON button)
{
    switch(button)
    {
        case BUTTON_S3:
            S3_TRIS = PIN_INPUT;
            S3_ANSEL = PIN_DIGITAL ;
            break;

        case BUTTON_S6:
            S6_TRIS = PIN_INPUT;
            S6_ANSEL = PIN_DIGITAL ;
            break;

        case BUTTON_S5:
            S5_TRIS = PIN_INPUT;
            S5_ANSEL = PIN_DIGITAL ;
            break;
            
        case BUTTON_S4:
            S4_TRIS = PIN_INPUT;
            break;

        default:
            break;
    }
}

void button_init(){
    int i;
    for (i = BUTTON_S3; i <= BUTTON_S6; i++) {
        button_en(i);
    } 
}
