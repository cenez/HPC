using Printf
function fib(n::Int)
  #n<0 && error("n must be non negative")
  n==0 && return 0
  n==1 && return 1
  fib(n-1) + fib(n-2)
end

params = map(x->string(x), ARGS)
n = try
    parse(Int64,params[1])
  catch
    10
end;

print("****************************************** Julia ******************************************\n")
t1 = time();
print("fibo(", n, ")=", fib(n))
elapsed_time = time() - t1
@printf("\nTime: %.2f seconds.\n", elapsed_time);


