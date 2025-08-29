public class Fibonacci {
	/*
	 * mem[0] = 0
	 * mem[1] = 1
	 * mem[n]=mem[n-1] + mem[n-2]
	 */
	public static long[] mem = null;

	public static void main(String[] args) {
		int n = 40;
		long t = System.currentTimeMillis();
		long f = fibR(n);
		t = (System.currentTimeMillis() - t);
		System.out.format("Fibo: %d : Tempo: %d ms \n", f, t);
	}
	public static long fibI(long n){
		if(n==0) return 0;
		if(n==1) return 1;
		    
		long a = 0;
		long b = 1;
		long c = a+b;
		for(int i = 0; i<n-1; i++){
			c = a + b;
			a = b;
			b = c;
		}
		return c;
	}
	public static long fibR(int n) {
		//if (mem == null) mem = new long[n + 1]; 
		//if (mem[n] != 0) return mem[n]; //memoizacao
		if (n <= 0) return 0;
		if (n == 1) return 1;

		long l1 = fibR(n - 1);
		//mem[n - 1] = l1;
		long l2 = fibR(n - 2);
		//mem[n - 2] = l2;
		
		return l1 + l2;
	}
}
