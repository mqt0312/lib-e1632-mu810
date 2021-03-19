/* 
 * File:   scheduler.h
 * Author: mintron
 *
 * Created on March 15, 2021, 11:58 PM
 */

#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include <stdbool.h>

#define SCHEDULER_MAX_TASK 10

typedef struct {
    void (*task_func)();
    unsigned long period;
    unsigned long iteration;
    bool is_enabled;
} scheduler_task_t;

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


#endif	/* SCHEDULER_H */

