package hangmanGame;
import javax.swing.JOptionPane;
public class wrappertest {
public static void main(String[] args) {
	int age;
	JOptionPane.showMessageDialog(null, "Test");
	String name = JOptionPane.showInputDialog(null, "Enter Your full name");
	String[] nm = name.split(" ");
	JOptionPane.showMessageDialog(null,"Hello, "+ nm[0]);
	String ageString = JOptionPane.showInputDialog(null, "AGE: ");
	age = Integer.parseInt(ageString);
	JOptionPane.showMessageDialog(null,"Name : "+ name + " Age: "+ age);
	int testscore = 80;
	Integer TestObject = testscore;
	JOptionPane.showMessageDialog(null, "Your Test score is: " + TestObject);
	int choice = JOptionPane.showConfirmDialog(null, "Do you want to change the score");
	if(choice == JOptionPane.YES_OPTION) {
		String scoreString=JOptionPane.showInputDialog(null, "Enter new score: ");
		TestObject = Integer.parseInt(scoreString);
		JOptionPane.showMessageDialog(null,"Your new score is: "+TestObject);
	}else {
		JOptionPane.showMessageDialog(null, "Goodbye");
	}
	
	
	
}
}
