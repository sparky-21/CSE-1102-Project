// new_func.h
#ifndef NEW_FUNC_H
#define NEW_FUNC_H

// Headers
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>


//Macros
#define MAX_EV 10000
#define clr system("cls");



// Function Declaration
void exit_program(void);
void load_events(void);
void nav_menu(void);
void view_cal(void);
bool has_event(int day, int month, int year);
void view_today(int day, int month, int year);
void add(void);
void del(void);
void notific(void);
bool is_valid_date(int day, int month, int year);
void progress_tracker(void);
void ad_xm(void);
void view_progress(void);

#endif

