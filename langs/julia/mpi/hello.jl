using MPI
MPI.Init()

comm = MPI.COMM_WORLD
print("Olá, meu rank id é: $(MPI.Comm_rank(comm)) de $(MPI.Comm_size(comm))\n")
MPI.Barrier(comm)

