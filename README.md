Usando MPI e OpenMP para aplicação de Smooth em Imagens PPM
===========================================================

### Dependências
Esse programa divide a imagem em linhas e distribui para os nós pelo MPI.
O rank 0 comanda a comunicação. É responsável por enviar o trabalho para os nós e gerenciar quem pode gravar no disco para não gerar concorrência. Cada nó divide seu trabalho em Threads que realizam a leitura de sua parte da imagem e aplicam a técnica de Smooth. Quando terminado o trabalho, o nó solicita permissão para gravar o resultado no disco.

### Dependências
1. Pacotes necessários:

* sudo apt-get install build-essential
* apt-get install libcr-dev mpich2 mpich2-doc
* sudo apt-get install gcc-multilib

### Instalação

1. Faça o clone deste projeto:
	git clone https://github.com/naylor/Trab02-Grupo11-AePos

2. Entre na pasta do projeto

3. Rode o comando "make"


### Executando a aplicação
1. PPMsequencial (versão sequencial)

* Utilizando o PPMsequencial por menu
   usar: ./PPMsequencial

* Executando o PPMsequencial pelo terminal
   usar: ./PPMsequencial --help
   ou
   usar: ./PPMsequencial -i [IMAGEM] -d [NÍVEL DEBUG]

2. PPMparalelo (versão paralela)

* Executando o PPMparalelo pelo terminal
   usar: ./PPMparalelo --help
   ou
   usar: mpiexec -n [PROCESSOS] -f [NODES] ./PPMparalelo -i [IMAGEM] -t [NÚMERO THREADS] -c [CARGA DE TRABALHO] -a [CARGA ALEATÓRIA] -t [LEITURA INDIVIDUAL] -d [NÍVEL DEBUG]

  * [PROCESSOS]: número de processos que serão gerados.
  * [IMAGEM]: colocar apenas o nome do arquivo (ex. model.ppm, omitir o diretório).
  * [NODES]: substituir pelo arquivo contendo os nodes: nodes.
  * [NUMERO THREADS]: número de threads para cada node local, se omitido, será com base no número de núcleos.
  * [CARGA TRABALHO]: número máximo de linhas, que o Rank0 alocará para cada processo, se omitido, será uma divisão igualitária.
  * [CARGA ALEATÓRIA]: se ativado, as cargas enviadas para os nodes serão aleatórias.
  * [LEITURA INDIVIDUAL]: faz com que cada processo tenha acesso exclusivo a imagem no momento da leitura.
  * [NIVEL DEBUG]: permite monitorar os eventos do sistema, permitido 1: nível do node e 2: nível da imagem.

3. Os resultados são gravados na pasta: resultados

4. Imagens PPM/PGM disponíveis na pasta: images_in
5. Imagens processadas com Smooth na pasta: images_out
