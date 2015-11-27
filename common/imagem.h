#ifndef IMAGEM_H_INCLUDED
#define IMAGEM_H_INCLUDED

typedef struct {
    unsigned char red,green,blue;
} PPMPixel;

typedef struct {
    unsigned char gray;
} PGMPixel;

typedef struct {
    PPMPixel *ppmIn;
    PGMPixel *pgmIn;
    int li, lf;
} PPMThreadIn;

typedef struct {
    PPMPixel *ppmOut;
    PGMPixel *pgmOut;
    int li, lf;
} PPMThreadOut;

typedef struct {
    int li, lf;
} PPMNode;

typedef struct {
    int linha, coluna;
    int proxLinha;
    int posIniFileIn;
    int posIniFileOut;
    char fileIn[200];
    char fileOut[200];
    char tipo[2];
} PPMImageParams;

#include "funcao.h"

void getPPMParameters(initialParams* ct, PPMImageParams* imageParams);
void writePPMHeader(initialParams* ct, PPMImageParams* imageParams);
int getDivisionNodes(initialParams* ct, PPMImageParams* imageParams, PPMNode* node, int numNodes, int numNode, int numMaxLinhas);
PPMThreadIn* getDivisionThreads(initialParams* ct, PPMImageParams* imageParams, PPMNode* node, int numNode);
int getImageThreads(initialParams* ct, PPMImageParams* imageParams, PPMThreadIn* threadIn, int numThread, int numNode);
void writePPMPixels(initialParams* ct, PPMImageParams* imageParams, PPMThreadOut* threadOut, int numThread, int numNode);
void applySmooth(initialParams* ct, PPMImageParams* imageParams, PPMThreadIn* threadIn, PPMThreadOut* threadOut, int numThread, int numNode);

#define CREATOR "NGB"
#define RGB_COMPONENT_COLOR 255

#endif // IMAGEM_H_INCLUDED
