def sum(depth, x):
  switch depth:
    case 0:
      return x
    case _:
      fst = sum(depth-1, x*2+0)
      snd = sum(depth-1, x*2+1)
      return fst + snd

def main:
  return sum(20, 0)

