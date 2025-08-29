import javax.swing.JButton;

@SuppressWarnings("serial")
public class Button extends JButton{
	public int i,j,value;
	public Button(int i, int j, int value) {
		this.i = i;
		this.j = j;
		this.value = value;
		if(i!=j) this.setText("["+i+","+j+"]="+"∞");//value);// "∞"
		else this.setText("["+i+","+j+"]="+"0");//value);// "∞"
	}
	public void config(int i, int j, int value) {
		this.i = i;
		this.j = j;
		this.value = value;
	}
}
