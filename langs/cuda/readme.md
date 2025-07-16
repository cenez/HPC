## Exemplo de como compilar e executar o cuda (necessário gpu nvidia):
#### Para compilar/executar **SEM GPU**:
    gcc vector_add.c -o cpu ; time ./cpu 100000
#### Para compilar/executar **com GPU**:
    nvcc vector_add_threads.cu -o gpu ; time ./gpu 100000
#### Para compilar/executar **com OpenMP**:
    gcc -o omp -fopenmp vector_add_omp.c ; time ./omp 100000



