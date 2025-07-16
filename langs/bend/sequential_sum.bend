def Sum(start, target):
  if start == target:
    return start
  else:
    return start + Sum(start + 1, target)  

def main():
  # Ocorre: (1 + (2 + (3 + (...... + (999999 + 1000000)))))
  return Sum(1, 1_000_000)




