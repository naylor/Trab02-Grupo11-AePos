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

void show_timer(tempo* t) {
	//timeval diff
    t->tempoA->timeval_diff = t->tempoA->timeval_diff_s * 1000.0; // sec to ms
    t->tempoA->timeval_diff += t->tempoA->timeval_diff_u / 1000.0; // us to ms
    t->tempoR->timeval_diff = t->tempoA->timeval_diff_s * 1000.0; // sec to ms
    t->tempoR->timeval_diff += t->tempoA->timeval_diff_u / 1000.0; // us to ms
    t->tempoS->timeval_diff = t->tempoA->timeval_diff_s * 1000.0; // sec to ms
    t->tempoS->timeval_diff += t->tempoA->timeval_diff_u / 1000.0; // us to ms
    t->tempoW->timeval_diff = t->tempoA->timeval_diff_s * 1000.0; // sec to ms
    t->tempoW->timeval_diff += t->tempoA->timeval_diff_u / 1000.0; // us to ms

    printf("[Time Read] %.0fms\n", t->tempoR->timeval_diff);
    printf("[Time Smooth] %.0fms\n", t->tempoS->timeval_diff);
    printf("[Time Write] %.0fms\n", t->tempoW->timeval_diff);
    printf("[Time App] %.0fms\n", t->tempoA->timeval_diff);
}
