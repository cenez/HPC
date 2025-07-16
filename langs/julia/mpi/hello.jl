using MPI

MPI.Init()

comm = MPI.COMM_WORLD
rank = MPI.Comm_rank(comm)
size = MPI.Comm_size(comm)

print("Olá, turma: este é o processo de rank $(rank) of $(size)\n")


########## OBS:
# julia
# using Pkg;
# Pkg.add("MPI")
# using MPI;
# MPI.install_mpiexecjl()



