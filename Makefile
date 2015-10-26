# MAKEFILE #

#INFORMANDO O COMPILADOR,
#DIRETÓRIOS E O
#NOME DO PROGRAMA
CC=gcc
G=g++
MPICC=mpicc
MPIG=mpic++
SRCCOMMON=common/
SRCSEQ=sequencial/
SRCPAR=paralelo/
SEQ=PPMsequencial
PAR=PPMparapelo

# FLAGS NECESSARIAS
# PARA COMPILACAO
CFLAGS=-Wall -Wextra -fopenmp
LIB=-fopenmp

#-------------------------------
# CARREGA AUTOMATICAMENTE OS
# ARQUIVOS .C E .H
#-------------------------------

SOURCESEQ=$(wildcard $(SRCSEQ)*.c $(SRCCOMMON)*.c)
HEADERSEQ=$(wildcard $(SRCSEQ)*.h $(SRCCOMMON)*.h)

SOURCEPAR=$(wildcard $(SRCPAR)*.c $(SRCCOMMON)*.c)
HEADERPAR=$(wildcard $(SRCPAR)*.h $(SRCCOMMON)*.h)

all: $(SEQ) $(PAR)

$(PAR): $(SOURCEPAR:.c=.o)
	$(MPIG) -o $@ $^ $(LIB)

%.o: %.c $(HEADERPAR)
	$(MPICC) -g -c $< -o $@ $(CFLAGS)

$(SEQ): $(SOURCESEQ:.c=.o)
	$(G) -o $@ $^ $(LIB)

%.o: %.c $(HEADERSEQ)
	$(CC) -g -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(SRCSEQ)*.o $(SRCPAR)*.o $(SRCCOMMON)*.o
	rm -f $(SEQ) $(PAR)
