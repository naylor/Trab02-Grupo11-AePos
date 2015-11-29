#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include "funcao.h"
#include "imagem.h"

// FUNCAO PARA RETORNAR UM VALOR DENTRO
// DE UM RANGE
unsigned int rand_interval(unsigned int min, unsigned int max)
{
    unsigned int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

// FUNCAO QUE CAPTURA AS ENTRADAS
// DO USUARIO E REGISTRA OS VALORES
void getCommandLineOptions(initialParams* ct, files* f, int argc, char *argv[]) {
    int i;

    for (i = 1; i < argc; i++) {

        if (argv[i] && argv[i+1] && strcmp(argv[i], "-i")==0) {
            // VERIFICA SE O NOME DIGITADO
            // É UM ARQUIVO VÁLIDO
            if (!in_array(f->names, f->total, argv[i+1])) {
                printf("Nome do arquivo da imagem esta incorreto.\nVerifique os nomes no diretorio.\n\n");
                ct->erro = -101;
                return;
            } else {
                ct->filePath = (char *) argv[i+1];
            }
        }

        //PEGA O NUMERO DE THREADS
        //E O NUMERO MAIS DE LINHAS
        if (argv[i] && strcmp(argv[i], "-t")==0)
            if (argv[i+1]) sscanf (argv[i+1],"%d",&ct->numThreads);
        if (argv[i] && strcmp(argv[i], "-c")==0)
            if (argv[i+1]) sscanf (argv[i+1],"%d",&ct->numMaxLinhas);
        if (argv[i] && strcmp(argv[i], "-a")==0)
            if (argv[i+1]) sscanf (argv[i+1],"%d",&ct->cargaAleatoria);
        if (argv[i] && strcmp(argv[i], "-l")==0)
            sscanf (argv[i+1],"%d",&ct->leituraIndividual);
        if (argv[i] && strcmp(argv[i], "-d")==0)
            if (argv[i+1]) sscanf (argv[i+1],"%d",&ct->debug);
    }
}

// FUNCAO QUE VERIFICA SE O USUARIO
// DIGITOU O NOME CORRETO DA IMAGEM
int in_array(char *array[], int size, void *lookfor)
{
    int i;

    for (i = 0; i < size; i++)
        if (strcmp(lookfor, array[i]) == 0)
            return 1;
    return 0;
}

// LIMPAR MEMORIA
void cleanMemory(PPMImageParams* imageParams, tempo* t, initialParams* ct) {
    if(imageParams != NULL)
        free(imageParams);
    if(ct != NULL)
        free(ct);
    if(t != NULL)
        free(t);
}

// FUNCAO PARA GERAR O ARQUIVO DE LOG
void writeFile(PPMImageParams* imageParams, tempo* t, initialParams* ct) {

	//filename
	char filename[200];
    sprintf((char*) &filename, "%s%c_%s.txt", ct->DIRRES, ct->typeAlg, ct->filePath);

   	//write to file
	FILE* f = fopen(filename, "a");
	if (f == NULL) {
        printf("\nNao foi possivel gravar o arquivo no diretorio dos resultados: %s\n\n", filename);
		ct->erro = -101;
	}
	fprintf(f, "%c\t%i\t%i\t%i\t%s\t%s\t%ix%i\t%.2f\t%.2f\t%.2f\t%.2f\n",
        ct->typeAlg,
		ct->numProcessos,
		ct->numThreads,
        ct->numMaxLinhas,
        ct->leituraIndividual?"yes":"no",
        ct->cargaAleatoria?"yes":"no",
        imageParams->linha,
        imageParams->coluna,
		t[0].tempoR,
		t[0].tempoF,
		t[0].tempoW,
		t[0].tempoA);

	fclose(f);
}

// LISTA OS ARQUIVOS DE UM DIRETORIO
files* listDir(char *dir) {
    int n, i;
    i=0;

    struct dirent **namelist;
    files* f = (files*)calloc(1,sizeof(files));

    n = scandir(dir, &namelist, 0, alphasort);

    if (n < 0)
        printf("\nNao foi possivel achar o diretorio: %s\n\n", dir);
    else {
        while(n--) {
            if ((strcmp(namelist[n]->d_name, ".")!=0)
            && (strcmp(namelist[n]->d_name, "..")!=0)) {
                f->names[i] =  namelist[n]->d_name;
                i++;
                free(namelist[n]);
            }
        }
        free(namelist);
    }

    f->total = i;
    return f;
}
