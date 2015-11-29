#include <time.h>
#include <sys/time.h>
#include <stdbool.h>

#ifndef TIMER_H_
#define TIMER_H_

typedef struct {
    struct timeval timeval_start, timeval_end;
    double timeval_diff, timeval_diff_s, timeval_diff_u;
} timer;

typedef struct {
    float tempoA; // TEMPO DA APLICACAO
    float tempoR; // TEMPO DA LEITURA
    float tempoW; // TEMPO DA GRAVACAO
    float tempoS; // TEMPO DO FILTRO
} tempo;

void start_timer(timer* t);
void stop_timer(timer* t);
void total_timer(tempo* t);
void show_timer(tempo* t, int numNodes);

#endif
