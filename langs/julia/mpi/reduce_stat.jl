# Este exemplo mostra como usar tipos de dados personalizados e operadores de redução
# Ele calcula a variância em paralelo de forma numericamente estável
using MPI, Statistics

MPI.Init()
const comm = MPI.COMM_WORLD
const root = 0

# Defina uma estrutura personalizada
# Contém as estatísticas resumidas (média, variância, comprimento) de um vetor
struct SummaryStat
    mean::Float64
    var::Float64
    n::Float64
end
function SummaryStat(X::AbstractArray)
    m = mean(X)
    v = varm(X,m, corrected=false)
    n = length(X)
    SummaryStat(m,v,n)
end

# Defina um operador de redução personalizado
# Isso calcula a média combinada, a variância combinada e o comprimento total
function pool(S1::SummaryStat, S2::SummaryStat)
    n = S1.n + S2.n
    m = (S1.mean*S1.n + S2.mean*S2.n) / n
    v = (S1.n * (S1.var + S1.mean * (S1.mean-m)) +
         S2.n * (S2.var + S2.mean * (S2.mean-m)))/n
    SummaryStat(m,v,n)
end

# Registre o operador de redução personalizado. Isso é necessário apenas em plataformas
# onde Julia não suporta fechamentos como cfunctions (por exemplo, ARM), mas pode ser usado
# em todas as plataformas para consistência.
MPI.@RegisterOp(pool, SummaryStat)

X = randn(10,3) .* [1,3,7]'

# Executar uma redução escalar
summ = MPI.Reduce(SummaryStat(X), pool, comm; root)

if MPI.Comm_rank(comm) == root
    @show summ.var
end

# Executar uma redução de vector:
# o operador de redução é aplicado elemento a elemento
col_summ = MPI.Reduce(mapslices(SummaryStat,X,dims=1), pool, comm; root)

if MPI.Comm_rank(comm) == root
    col_var = map(summ -> summ.var, col_summ)
    @show col_var
end
