#ifndef TIME_CAMERA_H
#define TIME_CAMERA_H

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <iostream>

#define TIME_WHEEL_SIZE 8

using namespace std;
typedef void (*func)();

typedef struct timer_node struct_timer_node;

struct timer_node {
    struct timer_node *next;
    int rotation;
    func proc;
    bool flag;
};

struct timer_wheel {
    struct timer_node *slot[TIME_WHEEL_SIZE];
    int current;
};

struct timer_wheel timer = {{0}, 0};

void tick(int signo);
void add_timer(int len, func action);
tm* Get_systemTime();


#endif