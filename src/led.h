#ifndef E1632_LED_H
#define E1632_LED_H

#include <stdbool.h>
#include <stdint.h>
#include <xc.h>

typedef enum {
    LED_D3,
    LED_D4,
    LED_D5,
    LED_D6,
    LED_D7,
    LED_D8,
    LED_D9,
    LED_D10
} led_builtin_t;

#define LED_D3_LAT      LATAbits.LATA0
#define LED_D4_LAT      LATAbits.LATA1
#define LED_D5_LAT      LATAbits.LATA2
#define LED_D6_LAT      LATAbits.LATA3
#define LED_D7_LAT      LATAbits.LATA4
#define LED_D8_LAT      LATAbits.LATA5
#define LED_D9_LAT      LATAbits.LATA6
#define LED_D10_LAT     LATAbits.LATA7      //Overlaps with S5

#define LED_D3_TRIS     TRISAbits.TRISA0
#define LED_D4_TRIS     TRISAbits.TRISA1
#define LED_D5_TRIS     TRISAbits.TRISA2
#define LED_D6_TRIS     TRISAbits.TRISA3
#define LED_D7_TRIS     TRISAbits.TRISA4
#define LED_D8_TRIS     TRISAbits.TRISA5
#define LED_D9_TRIS     TRISAbits.TRISA6
#define LED_D10_TRIS    TRISAbits.TRISA7    //Overlaps with S5

#define LED_ON  1
#define LED_OFF 0

#define INPUT  1
#define OUTPUT 0

void led_on(led_builtin_t led);
void led_off(led_builtin_t led);
void led_toggle(led_builtin_t led);
bool led_get(led_builtin_t led);
void led_set(led_builtin_t led, uint8_t val);
void led_enable(led_builtin_t led);
void led_init();


#endif // E1632_LED_H