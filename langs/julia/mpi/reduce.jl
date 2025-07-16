using MPI, Statistics
MPI.Init()
root = 0
comm = MPI.COMM_WORLD
rank = MPI.Comm_rank(comm)
size = MPI.Comm_size(comm)

struct Compra
  valor::Float64
  imposto::Float64
end
function PrecoMedio(X::AbstractArray)
  v = mean(X)
  i =  v*0.15
  Compra(v, i)
end
function soma_funtion(S1::Compra, S2::Compra)
  v = S1.valor + S2.valor
  i = (S1.imposto + S2.imposto)
  Compra(v, i)
end
MPI.@RegisterOp(soma_funtion, Compra)

item_a = (rank+1)*100
item_b = item_a*(rank+1)/2
imposto = (item_a+item_b)*0.15
compra = Compra(item_a+item_b, imposto)
X = Float64[item_a, item_b]
print("$X\n")

somatorio = MPI.Reduce(compra, soma_funtion, comm; root)
medio = MPI.Reduce(PrecoMedio(X), soma_funtion, comm; root)

if MPI.Comm_rank(comm) == root
  @show somatorio.valor
  @show somatorio.imposto
  @show medio.valor
  @show medio.imposto
end
