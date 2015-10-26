#! /bin/bash

echo -e "Iniciando as coletas de dados";

echo -e "Testando Pthreads, 10 execucoes com varios numeros de threads.";
for mat in `ls matrizes/`
  do
  for i in {2,3,5,6,7,8,9,10,15,20,50}
  do
    for j in $(seq 10);
    do
       ./trabalho-prog-conc $mat p $i
      sleep 5
    done
  done
done

echo -e "Testando OpenMP, 10 execucoes com varios numeros de threads.";
for mat in `ls matrizes/`
  do
  for i in {2,3,5,6,7,8,9,10,15,20,50}
  do
    for j in $(seq 10);
    do
       ./trabalho-prog-conc $mat o $i
      sleep 5
    done
  done
done

echo -e "Testando Sequencial.";
for mat in `ls matrizes/`
do
  for j in $(seq 10);
  do
    ./trabalho-prog-conc $mat s
    sleep 5
  done
done

