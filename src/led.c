#include "led.h"

void led_on(led_builtin_t led)
{
    switch(led)
    {
        case LED_D3:
            LED_D3_LAT = LED_ON ;
            break ;

        case LED_D4:
            LED_D4_LAT = LED_ON ;
            break ;

        case LED_D5:
            LED_D5_LAT = LED_ON;
            break;

        case LED_D6:
            LED_D6_LAT = LED_ON;
            break;
            
        case LED_D7:
            LED_D7_LAT = LED_ON ;
            break ;

        case LED_D8:
            LED_D8_LAT = LED_ON ;
            break ;

        case LED_D9:
            LED_D9_LAT = LED_ON ;
            break ;

        case LED_D10:
            LED_D10_LAT = LED_ON ;
            break ;

        default:
            break;
    }
}


void led_off(led_builtin_t led)
{
    switch(led)
    {
        case LED_D3:
            LED_D3_LAT = LED_OFF ;
            break ;

        case LED_D4:
            LED_D4_LAT = LED_OFF ;
            break ;

        case LED_D5:
            LED_D5_LAT = LED_OFF;
            break;

        case LED_D6:
            LED_D6_LAT = LED_OFF;
            break;

        case LED_D7:
            LED_D7_LAT = LED_OFF ;
            break ;

        case LED_D8:
            LED_D8_LAT = LED_OFF ;
            break ;

        case LED_D9:
            LED_D9_LAT = LED_OFF ;
            break ;

        case LED_D10:
            LED_D10_LAT = LED_OFF ;
            break ;

        default:
            break;
    }
}


void led_toggle(led_builtin_t led)
{
    switch(led)
    {
        case LED_D3:
            LED_D3_LAT ^= 1 ;
            break ;

        case LED_D4:
            LED_D4_LAT ^= 1 ;
            break ;

        case LED_D5:
            LED_D5_LAT ^= 1;
            break;

        case LED_D6:
            LED_D6_LAT ^= 1;
            break;

        case LED_D7:
            LED_D7_LAT ^= 1 ;
            break ;

        case LED_D8:
            LED_D8_LAT ^= 1 ;
            break ;

        case LED_D9:
            LED_D9_LAT ^= 1 ;
            break ;

        case LED_D10:
            LED_D10_LAT ^= 1 ;
            break ;

        default:
            break;
    }
}

/*********************************************************************
* Function: bool LED_Get(LED led);
*
* Overview: Returns the current state of the requested LED
*
* PreCondition: LED configured via LEDConfigure()
*
* Input: LED led - enumeration of the LEDs available in this
*        demo.  They should be meaningful names and not the names of
*        the LEDs on the silkscreen on the board (as the demo code may
*        be ported to other boards).
*         i.e. - LED_Get(LED_CONNECTION_DETECTED);
*
* Output: true if on, false if off
*
********************************************************************/
bool led_get(led_builtin_t led)
{
    switch(led)
    {
        case LED_D3:
            return ( ( LED_D3_LAT == LED_ON ) ? true : false ) ;

        case LED_D4:
            return ( ( LED_D4_LAT == LED_ON ) ? true : false ) ;

        case LED_D5:
            return ( (LED_D5_LAT == LED_ON) ? true : false );

        case LED_D6:
            return ( (LED_D6_LAT == LED_ON) ? true : false );

        case LED_D7:
            return ( ( LED_D7_LAT == LED_ON ) ? true : false ) ;

        case LED_D8:
            return ( ( LED_D8_LAT == LED_ON ) ? true : false ) ;

        case LED_D9:
            return ( ( LED_D9_LAT == LED_ON ) ? true : false ) ;

        case LED_D10:
            return ( ( LED_D10_LAT == LED_ON ) ? true : false ) ;

        default:
            break;
    }
    return false;
}

void led_set(led_builtin_t led, uint8_t val)
{
    if (!(val == LED_ON || val == LED_OFF)) {
        return;
    }
    switch(led)
    {
        case LED_D3:
            LED_D3_LAT = val ;
            break ;

        case LED_D4:
            LED_D4_LAT = val ;
            break ;

        case LED_D5:
            LED_D5_LAT = val;
            break;

        case LED_D6:
            LED_D6_LAT = val;
            break;
            
        case LED_D7:
            LED_D7_LAT = val ;
            break ;

        case LED_D8:
            LED_D8_LAT = val ;
            break ;

        case LED_D9:
            LED_D9_LAT = val ;
            break ;

        case LED_D10:
            LED_D10_LAT = val ;
            break ;

        default:
            break;
    }
}

/*********************************************************************
* Function: void LED_Enable(LED led);
*
* Overview: Configures the LED for use by the other LED API
*
* PreCondition: none
*
* Input: LED led - enumeration of the LEDs available in this
*        demo.  They should be meaningful names and not the names of
*        the LEDs on the silkscreen on the board (as the demo code may
*        be ported to other boards).
*
* Output: none
*
********************************************************************/
void led_enable(led_builtin_t led)
{
    switch(led)
    {
        case LED_D3:
            LED_D3_TRIS = OUTPUT ;
            break ;

        case LED_D4:
            LED_D4_TRIS = OUTPUT ;
            break ;

        case LED_D5:
            LED_D5_TRIS = OUTPUT;
            break;

        case LED_D6:
            LED_D6_TRIS = OUTPUT;
            break;

        case LED_D7:
            LED_D7_TRIS = OUTPUT ;
            break ;

        case LED_D8:
            LED_D8_TRIS = OUTPUT ;
            break ;

        case LED_D9:
            LED_D9_TRIS = OUTPUT ;
            break ;

        case LED_D10:
            LED_D10_TRIS = OUTPUT ;
            break ;

        default:
            break;
    }
}

void led_init() {
    int i;
    for (i = LED_D3; i <= LED_D10; i++) {
        led_enable(i);
    }
    led_enable(LED_D10);
}
