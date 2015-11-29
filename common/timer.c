#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

#include "timer.h"

void start_timer(tempoParams* t) {
    gettimeofday(&t->timeval_start, NULL);
}

void stop_timer(tempoParams* t) {
	gettimeofday(&t->timeval_end, NULL);

	//timeval diff
	t->timeval_diff_s += t->timeval_end.tv_sec - t->timeval_start.tv_sec;
	t->timeval_diff_u += t->timeval_end.tv_usec - t->timeval_start.tv_usec;
}

void total_timer(tempo* t, int numNode) {
	//timeval diff
    t[numNode].tempoA->timeval_diff = t[numNode].tempoA->timeval_diff_s * 1000.0; // sec to ms
    t[numNode].tempoA->total += t[numNode].tempoA->timeval_diff_u / 1000.0; // us to ms
    t[numNode].tempoR->timeval_diff = t[numNode].tempoR->timeval_diff_s * 1000.0; // sec to ms
    t[numNode].tempoR->total += t[numNode].tempoR->timeval_diff_u / 1000.0; // us to ms
    t[numNode].tempoS->timeval_diff = t[numNode].tempoS->timeval_diff_s * 1000.0; // sec to ms
    t[numNode].tempoS->total += t[numNode].tempoS->timeval_diff_u / 1000.0; // us to ms
    t[numNode].tempoW->timeval_diff = t[numNode].tempoW->timeval_diff_s * 1000.0; // sec to ms
    t[numNode].tempoW->total += t[numNode].tempoW->timeval_diff_u / 1000.0; // us to ms
}

void show_timer(tempo* t, int numNodes) {

    float tempoR;
    for(i=1; i <= numNodes; i++) {
        tempoR += t[i].tempoR->total;
    }

	//timeval diff
    printf("[Time Read] %.0fms\n", tempoR);
    printf("[Time Smooth] %.0fms\n", t->tempoS->total);
    printf("[Time Write] %.0fms\n", t->tempoW->total);
    printf("[Time App] %.0fms\n", t->tempoA->total);
}
