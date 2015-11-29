#include <time.h>
#include <sys/time.h>
#include <stdbool.h>

#ifndef TIMER_H_
#define TIMER_H_

#ifdef __linux__ // || _unix_ || _unix
	typedef struct timer_t {
		struct timeval timeval_start, timeval_end;
		struct timespec timespec_start, timespec_end;
		clock_t clock_start, clock_end, clock_diff;
		double timeval_diff, timeval_diff_s, timeval_diff_u, timespec_diff, clock_diff_time;
	} timer;
#else
	typedef struct timer_t {
		struct timeval timeval_start, timeval_end;
		clock_t clock_start, clock_end, clock_diff;
		double timeval_diff, timeval_diff_s, timeval_diff_u, timespec_diff, clock_diff_time;
	} timer;
#endif

typedef struct {
    float tempoA; // TEMPO DA APLICACAO
    float tempoR; // TEMPO DA LEITURA
    float tempoF; // TEMPO DA LEITURA
    float tempoW; // TEMPO DA GRAVACAO
} tempo;

void start_timer(timer* t);
void stop_timer(timer* t);
double total_timer(timer* t);
void show_timer(tempo* t, int numNodes);

#endif
