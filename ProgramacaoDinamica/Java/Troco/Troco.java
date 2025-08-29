public class Troco {
	public static int[] qtde;
	public static int[] c;
	public static void main(String[] args) {
		if (args.length<1) {
			System.out.println("Parametro: Qtd troco?");
			System.exit(0);
		}
		int troco = Integer.parseInt(args[0]);
		/*
		
		int troco = 8;
		int[] padrao = {2, 4, 6};
		//int[] padrao = {5, 7, 17, 25};
		//int[] padrao = {98,99,100};//para 33:[ 7 7 7 7 4 1 ]
		//int[] padrao = {7,17,25};
		
		*/
		double inicio, tempo;
		int q;		
		
		/*
		int troco = 11;
		int[] caixa = {2, 3, 4, 6};
		
		int troco = 107;
		int[] caixa = {1, 2, 3, 4, 5, 7};
		 */

		int[] caixa = {2, 3, 4, 5, 7};

		qtde = new int[troco+1];
		for (int i=0; i<qtde.length; i++) { qtde[i] = -1; }
		
		inicio = System.currentTimeMillis();
		q = trocoDinamico(caixa, troco);
		tempo = System.currentTimeMillis() - inicio;
		imprime(c, troco);
		System.out.printf("%-15s%10s%10s\n", "Metodo", "Qtde", "Tempo");
		System.out.printf("%-15s%10d%10.2f\n", "Dinamico", q, tempo);

		inicio = System.currentTimeMillis();
		q = trocoGuloso(caixa, troco);
		tempo = System.currentTimeMillis() - inicio;
		System.out.printf("%-15s%10d%10.2f\n", "Guloso", q, tempo);
		
		inicio = System.currentTimeMillis();
		q = trocoMemoization(caixa, troco);
		tempo = System.currentTimeMillis() - inicio;
		System.out.printf("%-15s%10d%10.2f\n", "Memoization", q, tempo);
		
		inicio = System.currentTimeMillis();
		q = trocoRecursivo(caixa, troco);
		tempo = System.currentTimeMillis() - inicio;
		System.out.printf("%-15s%10d%10.2f\n", "Recursivo", q, tempo);
	}
	private static int trocoGuloso(int[] caixa, int troco) {
		if (troco==0) return 0;
		int tmp_t = troco;
		int conta = 0;
		int last_id = caixa.length-1;
		boolean sair = false;
		while(sair!=true) {
			sair = true;
			for (int t = last_id; t>=0; t--) {
				if(tmp_t-caixa[t]>=0) {
					tmp_t = tmp_t - caixa[t];
					conta++;
					last_id = t;
					sair = false;
					break;
				}
			}
			if (sair == true && tmp_t > 0) 
				conta = Integer.MAX_VALUE;
		}
		return conta;
	}
	public static int trocoRecursivo(int[] caixa, int troco) {
		if (troco != 0) {
			int qMin = Integer.MAX_VALUE;
			for (int i = 0; i < caixa.length; i++) {
				if (troco - caixa[i] >= 0) {
					int q = trocoRecursivo(caixa, troco - caixa[i]) + 1;
					if (q < 0) { q = Integer.MAX_VALUE; }//Estouro de Integer MaxValue
					if (q < qMin) qMin = q;
				}
			}
			return qMin;
		}
		return 0;
	}
	public static int trocoMemoization(int[] caixa, int troco) {
		int qMin = 0;
		if (troco != 0) {
			qMin = Integer.MAX_VALUE;
			for (int i = 0; i < caixa.length; i++) {
				if (troco - caixa[i] >= 0) {
					int q = 0;
					if(qtde[troco]!=-1) { 
						q = qtde[troco];
					}
					else {
						q = trocoMemoization(caixa, troco - caixa[i]) + 1;
					}
					// int q = trocoRecursivo(caixa, troco - caixa[i]) + 1;
					if (q < 0) { q = Integer.MAX_VALUE; } // Estouro de Integer MaxValue
					if (q < qMin) qMin = q;
				}
			}
		}
		qtde[troco] = qMin;
		return qMin;
	}
	/*
	 * inicio: q[t..troco]=INFINITO, onde 0<t<=troco
	 * q[0] = 0
	 * q[t]=min(q[t], q[t-caixa[k]]+1), se (t-caixa[k])>=0
	 */
	public static int trocoDinamico(int[] caixa, int troco) {
		int[] q = new int[troco + 1];
		c = new int[troco + 1];
		q[0] = 0;
		for (int t = 1; t <= troco; t++) {
			q[t] = Integer.MAX_VALUE;
			for (int p = 0; p < caixa.length; p++) {
				if(t-caixa[p]>=0) {
					if(q[t-caixa[p]]+1>0) {
		            	if(q[t]>(q[t-caixa[p]]+1)) {
		            		c[t] = caixa[p];
		            	}
						q[t] = Math.min(q[t], q[t-caixa[p]]+1);
					}
				}
			}
		}
		return q[troco];
	}
	public static void imprime(int[] c, int troco) {
		int sub = troco, soma = 0, max = 0;
		System.out.print("moedas: [ ");
		while (sub > 0 && (max<=troco)) {
			System.out.print(c[sub] + " ");
			soma += c[sub];
			sub = sub - c[sub];
			max++;
		}
		System.out.println("] Soma("+troco+")="+(soma==troco));
	}
}

