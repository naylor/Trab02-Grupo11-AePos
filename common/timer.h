#include <time.h>
#include <sys/time.h>
#include <stdbool.h>

#ifndef TIMER_H_
#define TIMER_H_

typedef struct {
    struct timeval timeval_start, timeval_end;
    double timeval_diff, timeval_diff_s, timeval_diff_u;
} tempoParams;

typedef struct {
    tempoParams* tempoA; // TEMPO DA APLICACAO
    tempoParams* tempoR; // TEMPO DA LEITURA
    tempoParams* tempoW; // TEMPO DA GRAVACAO
    tempoParams* tempoS; // TEMPO DO FILTRO
} tempo;

void start_timer(tempoParams* t);
void stop_timer(tempoParams* t);
void show_timer(tempo* t);

#endif
