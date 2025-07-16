def fib_recursive(n: u24) -> u24:
  if n < 2:
    return n
  else:
    return fib_recursive(n - 1) + fib_recursive(n - 2)

def main() -> u24:
  n = 35
  return fib_recursive(n)

