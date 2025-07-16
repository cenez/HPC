def Sum(start, target):
  if start == target:
    return start
  else:
    half = (start + target) / 2
    left = Sum(start, half)  # (Start -> Half)
    right = Sum(half + 1, target)
    return left + right

# Um soma paralelizave de numeros: 1 a 1000000
def main():
  # O que ocorre: (((1 + 2) + (3 + 4)) + ... (999999 + 1000000)...)
  return Sum(1, 1_000_000)


# No exemplo, (3 + 4) não depende de (1 + 2). Portanto, computações podem ocorrer ao mesmo tempo.

