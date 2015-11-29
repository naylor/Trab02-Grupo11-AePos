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

void total_timer(tempo* t, timer* a, timer* r, timer* s, timer* w, int numNode) {
	//timeval diff
    a->timeval_diff = a->timeval_diff_s * 1000.0; // sec to ms
    a->timeval_diff += a->timeval_diff_u / 1000.0; // us to ms
    r->timeval_diff = r->timeval_diff_s * 1000.0; // sec to ms
    r->timeval_diff += r->timeval_diff_u / 1000.0; // us to ms
    s->timeval_diff = s->timeval_diff_s * 1000.0; // sec to ms
    s->timeval_diff += s->timeval_diff_u / 1000.0; // us to ms
    w->timeval_diff = w->timeval_diff_s * 1000.0; // sec to ms
    w->timeval_diff += w->timeval_diff_u / 1000.0; // us to ms
}

void show_timer(tempo* t, int numNodes) {

    double tempoR=0;
    double tempoS=0;
    double tempoW=0;
    double tempoA=0;
    int i;
    for(i=0; i <= numNodes; i++) {
        tempoR += t[i].tempoR;
        tempoS += t[i].tempoS;
        tempoW += t[i].tempoW;
        tempoA += t[i].tempoA;
    }

	//timeval diff
    printf("[Time Read] %.0fms\n", tempoR);
    printf("[Time Smooth] %.0fms\n", tempoS);
    printf("[Time Write] %.0fms\n", tempoW);
    printf("[Time App] %.0fms\n", tempoA);
}
