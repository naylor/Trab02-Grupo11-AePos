#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

#include "timer.h"

void start_timer(timer* t) {
    gettimeofday(&t->timeval_start, NULL);
}

void stop_timer(timer* t) {
	gettimeofday(&t->timeval_end, NULL);

	//timeval diff
	t->timeval_diff_s += t->timeval_end.tv_sec - t->timeval_start.tv_sec;
	t->timeval_diff_u += t->timeval_end.tv_usec - t->timeval_start.tv_usec;
}

double total_timer(timer* t) {
	//timeval diff
    t->timeval_diff = t->timeval_diff_s * 1000.0; // sec to ms
    t->timeval_diff += t->timeval_diff_u / 1000.0; // us to ms

    return (float)t->timeval_diff;
}

void show_timer(tempo* t, int numNodes) {

    double tempoR=0;
    double tempoS=0;
    double tempoW=0;
    int i;
    for(i=0; i <= numNodes; i++) {
        tempoR += t[i].tempoR;
        tempoS += t[i].tempoS;
        tempoW += t[i].tempoW;
    }

    t[0].tempoR = tempoR/numNodes;
    t[0].tempoS = tempoS/numNodes;
    t[0].tempoW = tempoW/numNodes;

	//timeval diff
    printf("[Time Read] %.2fms\n", t[0].tempoR);
    printf("[Time Smooth] %.2fms\n", t[0].tempoS);
    printf("[Time Write] %.2fms\n", t[0].tempoW);
    printf("[Time App] %.2fms\n", t[0].tempoA);
}
