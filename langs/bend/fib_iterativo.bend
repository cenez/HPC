def fib_iterative(n: u24) -> u24:
  bend a=0, b=1, n:
    when n != 0:
      return fork(b, a + b, n - 1)
    else:
      return a

def main() -> u24:
  n = 35
  return fib_iterative(n)

