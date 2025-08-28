import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JTextArea;

@SuppressWarnings("serial")
public class MatrixView extends JFrame {
	public static final Font FONT = new Font("SansSerif", Font.BOLD, 32);
	public Button[][] buttons = null;
	public int[][] s = null;
	public String[][] computations = null;
	
	public MatrixView(int rows, int cols) {
		this.setLayout(new GridLayout(rows+1, cols));
		this.setFont(FONT);
		buttons = new Button[rows+1][cols+1];
		s = new int[rows+1][cols+1];
		computations = new String[rows+1][cols+1];
		this.setTitle("Parentizacao de matrizes");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(1280, 720);
		for(int i=1;i<=rows;i++) {
			for(int j=1; j<=cols; j++) {
				int value = i>=j?0:Integer.MAX_VALUE;
				Button button = new Button(i,j,value);
				button.setFont(FONT);
				if(i<j || i==j) button.setBackground(Color.RED);
				this.add(button);
				buttons[i][j] = button;
				if(i<=j) {
					button.addActionListener(new ActionListener() {					
						@Override
						public void actionPerformed(ActionEvent e) {
							String parentizacao = parentizar(button.i,button.j);
							JTextArea textArea = new JTextArea(computations[button.i][button.j]);
							textArea.setFont(FONT);
							JOptionPane.showMessageDialog(null,textArea,parentizacao,JOptionPane.INFORMATION_MESSAGE);
						}
					});
				}
			}
		}
		this.buttonsLastLine(); // Botao de Wait
		this.setLocationRelativeTo(null);
		this.setVisible(true);
	}
	public String parentizar(int i, int j) { 
		return parentizar(i, j, new StringBuffer()); 
	}
	private String parentizar(int i, int j, StringBuffer sb) {
		if(i==j) { 
			sb.append("A"+i);
			return sb.toString();
		}
		sb.append("(");
		parentizar(i, s[i][j],sb);
		parentizar(s[i][j]+1, j,sb);
		sb.append(")");
		return sb.toString();
	}
	public void setButtonValue(int i, int j, int value) {
		buttons[i][j].config(i, j, value);
		String texto = "["+i+","+j+"]="+value;
		buttons[i][j].setBackground(Color.GREEN);
		buttons[i][j].setText(texto);
		if(i<j) {
			computations[i][j] += texto = "MIN=m["+i+","+j+"]="+value+" -> k=s["+i+"]["+j+"]="+s[i][j]+"\n";
			System.out.format("%s", texto);
		}
	}
	public void setComputeIJ(int i, int j) {
		if(computations[i][j]==null || !computations[i][j].equals("")) computations[i][j] = "";
		String texto = "#############################m["+i+","+j+"]#############################\n";
		if(i<j) {
			computations[i][j] = texto+"m[i, j]=MIN{m[i, k] + m[k+1, j] + p[i-1]*p[k]*p[j]}, se 1<=i<=k<j\n";
			computations[i][j] += "m["+i+", "+j+"]=MIN{m["+i+", k] + m[k+1, "+j+"] + p["+(i-1)+"]*p[k]*p["+j+"]}\n";
			computations[i][j] += "m["+i+", "+j+"]=MIN: \n";
		} else {
			computations[i][j] = texto+"m[i,j]=0, se i==j\n";
			computations[i][j] += "m["+i+","+j+"]=0\n";
		}
		System.out.format(computations[i][j]);
	}
	public void setComputeIJKMIN(int i, int j, int k, int min) {
		String par = "(" + parentizar(i, k) + "" + parentizar(k+1, j) + ")";
		String texto = "    m["+i+","+k+"]+m["+(k+1)+","+j+"]+p["+(i-1)+"]*p["+k+"]*p["+j+"]="+min+" -> "+par+"\n";
		computations[i][j]  += texto;
		System.out.format(texto);
	}
	public void setColorButtonIJK(int i, int j, int k, Color cor) {
		buttons[i][k].setBackground(cor); buttons[k+1][j].setBackground(cor);
	}
	public void setColorButton(int i, int j, Color cor) {
		buttons[i][j].setBackground(cor);
	}
	
	// Codigo seguinte para botao de wait
	public JButton waitBtn = new JButton("STOP");
	public static int tmp = MatrixChainMultiplication.sleep;
	public void buttonsLastLine() {
		waitBtn.setFont(FONT);
		waitBtn.setBackground(Color.GREEN);
		this.add(waitBtn);
		waitBtn.addActionListener(new ActionListener() {					
			@Override
			public void actionPerformed(ActionEvent e) {
				if(waitBtn.getText().equals("STOP")) {
					waitBtn.setText("RUN AGAIN!");
					waitBtn.setBackground(Color.GRAY);
					MatrixChainMultiplication.sleep = 100000; 
				} else {
					waitBtn.setText("STOP");
					waitBtn.setBackground(Color.GREEN);
					MatrixChainMultiplication.sleep = MatrixView.tmp;					
				}
				System.out.println("Sleep: "+MatrixChainMultiplication.sleep);
			}
		});
	}
}
