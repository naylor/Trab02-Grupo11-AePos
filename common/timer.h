#include <time.h>
#include <sys/time.h>
#include <stdbool.h>

#ifndef TIMER_H_
#define TIMER_H_

typedef struct {
    struct timeval timeval_start, timeval_end;
    double timeval_diff_s, timeval_diff_u;
} timer;

typedef struct {
    double tempoA; // TEMPO DA APLICACAO
    double tempoR; // TEMPO DA LEITURA
    double tempoW; // TEMPO DA GRAVACAO
    double tempoS; // TEMPO DO FILTRO
} tempo;

void start_timer(timer* t);
void stop_timer(timer* t);
void total_timer(tempo* t, timer* a, timer* r, timer* s, timer* w, int numNode);
void show_timer(tempo* t, int numNodes);

#endif
