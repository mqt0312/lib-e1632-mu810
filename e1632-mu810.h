#include <stdbool.h>

#ifndef E1632_MU810_H
#define	E1632_MU810_H
#ifndef _XTAL_FREQ
#define _XTAL_FREQ  128000000UL
#endif

#ifndef PERIPHERAL_CLOCK
#define PERIPHERAL_CLOCK (_XTAL_FREQ / 2)
#endif
// Cycle count presets. Useful for timers
#ifndef CYCLE_PRESETS
#define CYCLE_PRESETS

#define CYCLE_1S (PERIPHERAL_CLOCK)

#if ((CYCLE_1S / 1000)*1000 == CYCLE_1S)
#define CYCLE_1MS (CYCLE_1S / 1000)
#elif ((CYCLE_1S / 100)*100 == CYCLE_1S)
#define CYCLE_10MS (CYCLE_1S / 100)
#elif ((CYCLE_1S / 10)*10 == CYCLE_1S)
#define CYCLE_100MS (CYCLE_1S / 10)
#elif ((CYCLE_1S / 8)*8 == CYCLE_1S)
#define CYCLE_125MS (CYCLE_1S / 8)
#elif ((CYCLE_1S / 4)*4 == CYCLE_1S)
#define CYCLE_250MS (CYCLE_1S / 4)
#elif ((CYCLE_1S / 2)*2 == CYCLE_1S)
#define CYCLE_500MS (CYCLE_1S / 2)
#endif

#ifdef CYCLE_1MS
#if ((CYCLE_1MS / 1000)*1000 == CYCLE_1MS)
#define CYCLE_1US (CYCLE_1MS / 1000)
#elif ((CYCLE_1MS / 100)*100 == CYCLE_1MS)
#define CYCLE_10US (CYCLE_1MS / 100)
#elif ((CYCLE_1MS / 10)*10 == CYCLE_1MS)
#define CYCLE_100US (CYCLE_1MS / 10)
#elif ((CYCLE_1MS / 8)*8 == CYCLE_1MS)
#define CYCLE_125US (CYCLE_1MS / 8)
#elif ((CYCLE_1MS / 4)*4 == CYCLE_1MS)
#define CYCLE_250US (CYCLE_1MS / 4)
#elif ((CYCLE_1MS / 2)*2 == CYCLE_1MS)
#define CYCLE_500US (CYCLE_1MS / 2)
#endif
#endif

#ifdef CYCLE_1US
#if ((CYCLE_1US / 1000)*1000 == CYCLE_1US)
#define CYCLE_1NS (CYCLE_1US / 1000)
#elif ((CYCLE_1US / 100)*100 == CYCLE_1US)
#define CYCLE_10NS (CYCLE_1US / 100)
#elif ((CYCLE_1US / 10)*10 == CYCLE_1US)
#define CYCLE_100NS (CYCLE_1US / 10)
#elif ((CYCLE_1US / 8)*8 == CYCLE_1US)
#define CYCLE_125NS (CYCLE_1US / 8)
#elif ((CYCLE_1US / 4)*4 == CYCLE_1US)
#define CYCLE_250NS (CYCLE_1US / 4)
#elif ((CYCLE_1US / 2)*2 == CYCLE_1US)
#define CYCLE_500NS (CYCLE_1US / 2)
#endif
#endif // CYCLE_1US

#endif // CYCLE_PRESETS

#define SCHEDULER_MAX_TASK 10

// Initialization Routine
void mu810_init(void);

// LCD
bool lcd_init(void);
void lcd_puts(char* inputString, uint16_t length);
void lcd_putc(char);
void lcd_cls(void);
void lcd_cursor(bool enable);

// LED
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

void led_on(led_builtin_t led);
void led_off(led_builtin_t led);
void led_toggle(led_builtin_t led);
bool led_get(led_builtin_t led);
void led_set(led_builtin_t led, uint8_t val);
void led_enable(led_builtin_t led);
void led_init();

// Buttons
typedef enum
{
    BUTTON_S3,
    BUTTON_S4,
    BUTTON_S5,
    BUTTON_S6       
} BUTTON;

bool button_get(BUTTON button);
void button_en(BUTTON button);

bool scheduler_init();
int scheduler_add(void (*new_task_func)(void), unsigned long new_period);
bool scheduler_enable(int index, bool en);
bool scheduler_delete(int index);
bool scheduler_set_period(int index, unsigned long new_period);
unsigned long scheduler_get_period(int index);
bool scheduler_reset_iteration(int index);
unsigned long scheduler_get_iteration(int index);
bool scheduler_start();
bool scheduler_stop();


#endif

