import sys
import time

class Troco:
	def __init__(self):
		self.c = None

	def memoization_vector(self, troco):
		qtde = [-1] * (troco + 1)
		return qtde

	def trocoGuloso(self, caixa, troco):
		if troco==0: 
			return 0

		tmp_t, conta, sair = troco, 0, False
		last_id = len(caixa) - 1

		while (sair!=True):
			sair = True
			for t in range(last_id, -1, -1):
				if(tmp_t - caixa[t]>=0):
					tmp_t = tmp_t - caixa[t]
					conta += 1
					last_id = t
					sair = False
					break

			if (sair == True and tmp_t > 0): 
				conta = sys.maxsize
		return conta

	def trocoRecursivo(self, caixa, troco):
		if (troco != 0):
			qMin = sys.maxsize
			for i in range(len(caixa)):
				if (troco - caixa[i] >= 0):
					q = self.trocoRecursivo(caixa, troco - caixa[i]) + 1
					if (q < 0): # Estouro de Integer MaxValue
						q = sys.maxsize
					if (q < qMin):
						qMin = q
			return qMin
		return 0

	def trocoMemoization(self, caixa, troco, qtde):
		qMin = 0
		if (troco != 0):
			qMin = sys.maxsize
			for i in range(len(caixa)):
				if (troco - caixa[i] >= 0):
					q = 0
					if(qtde[troco]!=-1):
						q = qtde[troco]
					else:
						q = self.trocoMemoization(caixa, troco - caixa[i], qtde) + 1
					if (q < 0): # Estouro de Integer MaxValue
						q = sys.maxsize
					if (q < qMin):
						qMin = q
		qtde[troco] = qMin
		return qMin

	"""
	 * inicio: q[t..troco]=INFINITO, onde 0<t<=troco
	 * q[0] = 0
	 * q[t]=min(q[t], q[t-caixa[k]]+1), se (t-caixa[k])>=0
	"""
	def trocoDinamico(self, caixa, troco):
		q = [0] * (troco + 1)
		self.c = [0] * (troco + 1)
		q[0] = 0
		for t in range(1, troco+1):
			q[t] = sys.maxsize
			for p in range(len(caixa)):
				if(t-caixa[p]>=0):
					if(q[t-caixa[p]]+1>0):
						if(q[t]>(q[t-caixa[p]]+1)):
							self.c[t] = caixa[p]
						q[t] = min(q[t], q[t-caixa[p]]+1)
		return q[troco]

	def imprime(self, troco):
		if (self.c is None):
			print("Nenhum calculo realizado")
			return
		sub, soma, maxv = troco, 0, 0
		print("moedas: [ ", end="")
		while (sub > 0 and (maxv<=troco)):
			print(f'{self.c[sub]} ', end="")
			soma += self.c[sub]
			sub = sub - self.c[sub]
			maxv += 1
		print(f'] Soma({troco})={(soma==troco)}')

if __name__ == "__main__":
	app = Troco()
	inicio, tempo = 0.0, 0.0
	q = 0
	troco = 37
	caixa = [2, 3, 4, 5, 7]
	ms = 1000

	inicio = time.time()*ms
	q = app.trocoDinamico(caixa, troco)
	tempo = time.time()*ms - inicio
	app.imprime(troco)
	print("%15s %30s %15s" % ("Metodo", "Qtde", "Tempo"))
	print("%15s %30d %15.2f ms" % ("Dinamico", q, tempo))

	inicio = time.time()*ms
	q = app.trocoGuloso(caixa, troco)
	tempo = time.time()*ms - inicio
	print("%15s %30d %15.2f ms" % ("Guloso", q, tempo))
		
	inicio = time.time()*ms
	q = app.trocoMemoization(caixa, troco, app.memoization_vector(troco))
	tempo = time.time()*ms - inicio
	print("%15s %30d %15.2f ms" % ("Memoization", q, tempo))

	inicio = time.time()*ms
	q = app.trocoRecursivo(caixa, troco)
	tempo = time.time()*ms - inicio
	print("%15s %30d %15.2f ms" % ("Recursivo", q, tempo))

