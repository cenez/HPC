#### Exemplo de como compilar e executar o cuda (necessário gpu nvidia):
gcc vector_add.c -o cpu ; time ./cpu 100000
nvcc vector_add_threads.cu -o gpu ; time ./gpu 100000


