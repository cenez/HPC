import sys
import time

class Fibonacci:
	"""
	 * mem[0] = 0
	 * mem[1] = 1
	 * mem[n]=mem[n-1] + mem[n-2]
	"""
	def __init__(self, n: int):
		self.mem = [0]*(n + 1)
		self.mem[0] = 0
		self.mem[1] = 1
		self.n = n

	def fibI(self):
		if(self.n <= 1): 
			return self.n
		res = 1
		ultimo = 1
		penultimo = 1
		for i in range(3, self.n+1):
			res = ultimo + penultimo
			penultimo = ultimo
			ultimo = res
		return res

	def fibRMem(self): return self.__fibRMem(self.n)
	def __fibRMem(self, n: int):
		if (n <=1): 
			return n
		if (self.mem[n] != 0): 
			return self.mem[n] #memoizacao

		ultimo = self.__fibRMem(n - 1)
		self.mem[n - 1] = ultimo
		penultimo = self.__fibRMem(n - 2)
		self.mem[n - 2] = penultimo
		return ultimo + penultimo

	def fibR(self): return self.__fibR(self.n)
	def __fibR(self, n: int):
		if (n <= 1): 
			return n
		return self.__fibR(n - 1) + self.__fibR(n - 2)

if __name__ == "__main__":
	n = 30
	if len(sys.argv) > 1:
		n = int(sys.argv[1])

	print("%s %20s %20s %20s" % ("N", "Resultado", "Tipo", "Tempo (ms)"))
	app = Fibonacci(n)
	inicio = time.time()*1000
	f = app.fibI()
	tempo = time.time()*1000 - inicio
	print("%d %20d %20s %20.2f ms" % (n, f, "Iterativo", tempo))

	inicio = time.time()*1000
	f = app.fibRMem()
	tempo = time.time()*1000 - inicio
	print("%d %20d %20s %20.2f ms" % (n, f, "Memoizado", tempo))

	inicio = time.time()*1000
	f = app.fibR()
	tempo = time.time()*1000 - inicio
	print("%d %20d %20s %20.2f ms" % (n, f, "Recursivo", tempo))

