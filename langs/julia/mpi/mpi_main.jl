# julia
# using Pkg;
# Pkg.add("MPI")
# using MPI;
# MPI.install_mpiexecjl()

using MPI, Statistics
MPI.Init()
root = 0

comm = MPI.COMM_WORLD
rank = MPI.Comm_rank(comm)
size = MPI.Comm_size(comm)
print("Olá, turma: este é o processo de rank $(rank) of $(size)\n")

valor = MPI.Reduce(rank+1, *, root, comm)

if MPI.Comm_rank(comm) == root
    println("Valor processado = $valor")
end
