import MPI
MPI.Init()

comm = MPI.COMM_WORLD
N = 5
root = 0
size = MPI.Comm_size(comm)
rank = MPI.Comm_rank(comm)

if MPI.Comm_rank(comm) == root
    print(" Rodando com $(size) processos\n")
end

MPI.Barrier(comm)

if MPI.Comm_rank(comm) == root
    A = [i*(1.0 + im*2.0) for i = 1:N]
else
    A = Array{ComplexF64}(undef, N)
end

MPI.Bcast!(A, root, comm)

print("rank = $(rank), A = $A\n")

if rank == root
    B = Dict("key" => "value")
else
    B = nothing
end

B = MPI.bcast(B, root, comm)
print("rank = $(rank), B = $B\n")

if rank == root
    f = x -> x^2 + 2x - 1
else
    f = nothing
end

f = MPI.bcast(f, root, comm)
print("rank = $(rank), f(3) = $(f(3))\n")

