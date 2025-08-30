import time

class Fibonacci:
	"""
	 * mem[0] = 0
	 * mem[1] = 1
	 * mem[n]=mem[n-1] + mem[n-2]
	"""
	mem = None
	def __init__(self):
		pass
	def fibI(self, n):
		if(n==0): return 0
		if(n==1): return 1
		    
		a = 0
		b = 1
		c = a+b
		for i in range(n-1):
			c = a + b
			a = b
			b = c
		return c

	def fibR(self, n):
		if (Fibonacci.mem == None): Fibonacci.mem = [0]*(n + 1) # 
		if (Fibonacci.mem[n] != 0): return Fibonacci.mem[n] #memoizacao
		if (n <= 0): return 0
		if (n == 1): return 1

		l1 = self.fibR(n - 1)
		Fibonacci.mem[n - 1] = l1
		l2 = self.fibR(n - 2)
		Fibonacci.mem[n - 2] = l2
		
		return l1 + l2

if __name__ == "__main__":
	app = Fibonacci()
	n = 50
	inicio = time.time()*1000
	f = app.fibR(n)
	tempo = time.time()*1000 - inicio
	print("FIbo: %10d Tempo: %15.2f ms" % (f, tempo))
