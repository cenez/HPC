## Exemplo de como compilar e executar o cuda (necessário gpu nvidia):
#### Para compilar/executar **SEM GPU**:
    gcc vector_add.c -o cpu ; ./cpu 100000
#### Para compilar/executar **com GPU**:
    nvcc vector_add_threads.cu -o gpu ; ./gpu 100000
#### Para compilar/executar **com OpenMP**:
    gcc -o omp -fopenmp vector_add_omp.c ; ./omp 100000

#### Ou, para rodar os 3 testes:
    ./teste_desempenho.sh 100000




