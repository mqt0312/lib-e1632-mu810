#include <p33EP512MU810.h>
#include <stdbool.h>
#include <string.h>
#include "mu810.h"
#include "scheduler.h"

static scheduler_task_t st_list[SCHEDULER_MAX_TASK];



bool scheduler_init() {
    T9CONbits.TON = 0;
    T8CONbits.TON = 0;
    T8CONbits.T32 = 1; // Enable 32-bit mode
    T8CONbits.TCS = 0;

    T8CONbits.TCKPS = 0b00;

    TMR8 = 0;
    TMR9 = 0;
    PR9 = (CYCLE_1MS >> 16) & 0x00FFFF;
    PR8 = CYCLE_1MS & 0x00FFFF;

    _T9IP = 0x01;
    _T9IF = 0;
//    _T9IE = 1;
//    T8CONbits.TON = 1;
    return true;
}

int scheduler_add(void (*new_task_func)(void), unsigned long new_period) {
    int i;
    for (i = 0; i < SCHEDULER_MAX_TASK; i++) {
        if (!st_list[i].task_func) {
            st_list[i].task_func = new_task_func;
            st_list[i].period = new_period;
            st_list[i].is_enabled = true;
            st_list[i].iteration = 0;
            return i;
        }
    }
    return -1;
}

bool scheduler_enable(int index, bool en) {
    if (index >= SCHEDULER_MAX_TASK || index < 0) {
        return false;
    }
    st_list[index].is_enabled = en;
    return true;
}

bool scheduler_delete(int index) {
    if (index >= SCHEDULER_MAX_TASK || index < 0) {
        return false;
    }
    memset(&st_list[index], 0, sizeof(scheduler_task_t));
    return true;
}

bool scheduler_set_period(int index, unsigned long new_period) {
    if (index >= SCHEDULER_MAX_TASK || index < 0) {
        return false;
    }
    st_list[index].period = new_period;
    return true;
}

unsigned long scheduler_get_period(int index) {
    if (index >= SCHEDULER_MAX_TASK || index < 0) {
        return 0;
    }
    return st_list[index].period;
}

bool scheduler_reset_iteration(int index) {
    if (index >= SCHEDULER_MAX_TASK || index < 0) {
        return false;
    }
    st_list[index].iteration = 0;
    return true;
}

unsigned long scheduler_get_iteration(int index) {
    if (index >= SCHEDULER_MAX_TASK || index < 0) {
        return false;
    }
    return st_list[index].iteration;
}

bool scheduler_start() {
    if (_T9IE && T8CONbits.TON) return false;
    _T9IE = 1;
    T8CONbits.TON = 1;
    return true;
}

bool scheduler_stop() {
    if (!(_T9IE && T8CONbits.TON)) return false;
    _T9IE = 0;
    T8CONbits.TON = 0;
    return true;
}

void scheduler_tick() {
    int i;
    for (i = 0; i < SCHEDULER_MAX_TASK; i++) {
        if (!st_list[i].is_enabled || !st_list[i].task_func) continue;
        st_list[i].iteration++;
        if (st_list[i].iteration == st_list[i].period) {
            st_list[i].iteration = 0;
            st_list[i].task_func();
        }
    }
}

void __attribute__((__interrupt__, no_auto_psv)) _T9Interrupt(void) {
    scheduler_tick();
    //    led_toggle(LED_D8);
    _T9IF = 0;
}

