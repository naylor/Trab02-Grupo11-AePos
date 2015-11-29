#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../common/timer.h"
#include "../common/imagem.h"

#include "sequencial.h"
#include "main.h"

int main (int argc, char *argv[]){

    // VERIFICAR SE O USUARIO
    // CONTINUA OU SAI DO PROGRAMA
    char op=NULL;
    do {

        PPMImageParams* imageParams;

        imageParams = (PPMImageParams *)malloc(sizeof(PPMImageParams));

        // CARREGA O MENU OU SETA AS OPCOES
        // CASO INSERIDAS NA LINHA DE COMANDO
        initialParams* ct = (initialParams *)calloc(1,sizeof(initialParams));

        ct->DIRIMGIN = "images_in/";
        ct->DIRIMGOUT = "images_out/";
        ct->DIRRES = "resultados/";
        ct->typeAlg = 'S';
        menu(ct, argc, argv);

        sprintf((char*) &imageParams->fileOut, "%s%s", ct->DIRIMGOUT, ct->filePath);
        sprintf((char*) &imageParams->fileIn, "%s%s", ct->DIRIMGIN, ct->filePath);

        if (ct->filePath != NULL) {
            // RELOGIA PARA CADA NODE
            tempo* tempos = (tempo* )malloc(sizeof(tempo));

            //CARREGA O RELOGIO
            //start_timer(tempo);

            sequencial(imageParams, ct);

            //PARA O RELOGIO
            //stop_timer(tempoA);

            // ESCREVENDO OS RESULTADOS
            // NO ARQUIVO /resultados/
            writeFile(imageParams, tempos, ct);

            // LIMPANDO A MEMORIA
            cleanMemory(imageParams, tempos, ct);

        } else {
            printf("\nOpcao invalida!\n\n");
        }

        if (!argv[1]) {
            printf("\nPressione 's' para voltar ao menu ou 'n' para sair...\n");
            int ret = scanf(" %c", &op);
            if (ct->debug >= 1) printf("\nRet OP: %d", ret);
        } else {
            op = 'n';
        }

    } while (op != 'n');

    return 0;
}
