import java.awt.Color;

public class MatrixChainMultiplication {
	public static int INFINITO = Integer.MAX_VALUE;
	public static int[] p = {30, 35, 15, 5, 10, 20, 25}; //{3,4,2,1};
	//public static int[] p = {10, 1, 4, 13};
	public static int[][] m = null;
	public static MatrixView matrixView = null;
	public static int n;
	public static int sleep = 1;
	
	/*
	 * caso 1: m[i,j] = 0, se i==j
	 * caso 2: m[i,j] = min(m[i,k] + m[k+1,j] + p[i-1]*p[k]*p[j]), se 1<=i<=k<j
	 * OBS: nao usada a parte triangular inferior da matriz, quando i>j
	 */
	public static void main(String[] args) {
		n = p.length-1;
		matrixView = new MatrixView(n,n);
		System.out.println("CUSTO TOTAL: "+dinamico());
	}
	public static int dinamico() {
		m = new int[n+1][n+1];
		for(int l = 1; l<=n; l++) {
			for(int i = 1; i<=n-l+1;i++) {
				int j = i+l-1;
				m[i][j] = i==j?0:INFINITO;
				matrixView.setComputeIJ(i, j);
				matrixView.setColorButton(i, j, Color.CYAN);
				for(int k = i; k<j; k++) {
					int min = m[i][k]+m[k+1][j]+ p[i-1]*p[k]*p[j];
					matrixView.setComputeIJKMIN(i, j, k, min); 
					if(min<m[i][j]) {
						m[i][j] = min;
						matrixView.s[i][j] = k;
					}
					matrixView.setColorButtonIJK(i, j, k, Color.BLACK); 
					MatrixChainMultiplication.delay();
					matrixView.setColorButtonIJK(i, j, k, Color.GREEN);
				}
				MatrixChainMultiplication.delay();
				matrixView.setButtonValue(i, j, m[i][j]);
			}
		}
		System.out.println(matrixView.parentizar(1, n));
		return m[1][n];
	}
	public static void delay() {
		for(int i=0; i < MatrixChainMultiplication.sleep; i++) {
			try {
				Thread.sleep(1200);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
