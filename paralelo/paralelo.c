#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/imagem.h"
#include "paralelo.h"
#include "main.h"

#include <omp.h>

PPMImageParams* paraleloInitParams(initialParams* ct, PPMImageParams* imageParams) {

    // SETANDO O ARQUIVO DE SAIDA E ENTRADA
    sprintf((char*) &imageParams->fileOut, "%s%s", ct->DIRIMGOUT, ct->filePath);
    sprintf((char*) &imageParams->fileIn, "%s%s", ct->DIRIMGIN, ct->filePath);

    // CARREGANDO OS VALORES INICIAIS
    // DO CABECALHO DA IMAGEM
    getPPMParameters(ct, imageParams);

    imageParams->proxLinha=0;

    // SETANDO O NUMERO DE THREADS
    // CASO NAO INFORMADO
    if (ct->numThreads == 0)
        ct->numThreads = 3;

    // SETANDO O NUMERO MAXIMO DE LINHAS
    // QUE SERAO ENVIADAS PARA CADA NODE
    // CASO NAO TENHA SIDO INFORMADO
    if (ct->numMaxLinhas == 0)
        ct->numMaxLinhas = (int)imageParams->linha/ct->numProcessos;

    if ( ct->numMaxLinhas/ct->numThreads < 20 ) {
        printf("\nAtencao, nao e possivel dividir a imagem em blocos 5x5 "
               " com o numero de processos/threads informados.\n");
        ct->erro = -101;
    }

    //INFO DO PROCESSO ESCOLHIDO:
    printf("\n\nFile PPM %s\ncoluna: %d\nlinha: %d\nTipo: %s\n\n", imageParams->fileIn,
                      imageParams->coluna,
                      imageParams->linha,
                      strcmp(imageParams->tipo, "P6")==0?"COLOR":"GRAYSCALE");
    printf("\nCarga de Trabalho: %d\nCarga Aleatoria: %d\nThreads: %d\nLeitura Individual: %d\n",
           ct->numMaxLinhas,
           ct->cargaAleatoria,
           ct->numThreads,
           ct->leituraIndividual);

    return imageParams;
}

PPMThread* paraleloNodeReadAndSmooth(initialParams* ct, PPMImageParams* imageParams, PPMNode* node, int numNode) {

        PPMThread* thread = getDivisionThreads(ct, imageParams, node, numNode);
int t;
        for(t=0; t<ct->numThreads; t++) {
            // CARREGA PARTE DA IMAGEM PARA CADA THREAD
            if (getImageThreads(ct, imageParams, thread,  t, numNode) == 1) {
                // APLICA O SMOOTH NA IMAGEM PARA CADA THREAD
                //applySmooth(ct, imageParams, thread, t, numNode);
                // GRAVA O RESULTADO DO SMOOTH DE CADA THREAD NO ARQUIVO
                writePPMPixels(ct, imageParams, thread, t, numNode);
            }
        }
    return thread;
}

// ESSA FUNCAO ESCREVE NO ARQUIVO DE SAIDA
// A IMAGEM COM O FILTRO APLICADO
int paraleloNodeWrite(initialParams* ct, PPMImageParams* imageParams, PPMThread* thread, int numNode) {

    int t;


    return 1;
}
