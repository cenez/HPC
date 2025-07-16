## Exemplo de como executar o script julia (necessário instalar o ambiente mpi):
    cd mpi/
#### Hello:
    mpiexec -n 4 julia hello.jl
#### Broadcast:
    mpiexec -n 4 julia broadcast.jl
