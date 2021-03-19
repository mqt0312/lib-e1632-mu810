#ifndef E1632_MU810_H
#define E1632_MU810_H

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

#endif


//typedef enum {
//    ACH_EXPLORER_TEMP = 4,
//    ACH_EXPLORER_POT = 5
//} ADC_CHANNEL;


void mu810_init(void);


#endif