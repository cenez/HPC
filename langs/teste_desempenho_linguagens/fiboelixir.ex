defmodule FI do
  def medir_cauda(n) do
    {tempo_microssegundos, resultado} = :timer.tc(fn -> fibo_cauda(n) end)

    IO.puts("Fibo_cauda(#{n}): #{resultado} -> Tempo: #{tempo_microssegundos / 1_000000} segundos")
  end

  def medir_rec(n) do
    {tempo_microssegundos, resultado} = :timer.tc(fn -> fibo_rec(n) end)

    IO.puts("Fibo_rec(#{n}): #{resultado} -> Tempo: #{tempo_microssegundos / 1_000000} segundos")
  end

  # Caso base e recursão de cauda otimizada
  defp fibo_cauda(n), do: fib_calc(n, 0, 1)

  defp fib_calc(0, a, _b), do: a
  defp fib_calc(n, a, b) when n > 0, do: fib_calc(n - 1, b, a + b)

  def fibo_rec(n = 0), do: n
  def fibo_rec(n = 1), do: n
  def fibo_rec(n), do: fibo_rec(n-1)+fibo_rec(n-2)
end

IO.inspect("************************* Elixir *************************")
args = System.argv()
if length(args) > 0 do
  n = String.to_integer(Enum.at(args, 0))
  FI.medir_cauda(n)
  FI.medir_rec(n)
else
  "Fibo(n) ?"
end


