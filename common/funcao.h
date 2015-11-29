#ifndef FUNCAO_H_INCLUDED
#define FUNCAO_H_INCLUDED
#include "timer.h"

typedef struct {
    int total;
    char *names[20];
} files;

typedef struct {
    char* filePath;
    char typeAlg;
    char* DIRIMGIN;
    char* DIRIMGOUT;
    char* DIRRES;
    int numMaxLinhas;
    int numProcessos;
    int numThreads;
    int leituraIndividual;
    int debug;
    int erro;
    int cargaAleatoria;
} initialParams;

#include "imagem.h"

unsigned int rand_interval(unsigned int min, unsigned int max);
void getCommandLineOptions(initialParams* ct, files* f, int argc, char *argv[]);
void cleanMemory(PPMImageParams* imageParams, tempo* t, initialParams* ct);
void writeFile(PPMImageParams* imageParams, tempo* t, initialParams* ct);
files* listDir();
int in_array(char *array[], int size, void *lookfor);

#endif // FUNCAO_H_INCLUDED
