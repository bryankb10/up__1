package idk;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import javax.swing.*;
public class editStudent extends JFrame {
    private JTextField idField, nameField, ageField, courseField, genderField;
    private JTextArea displayArea;

    public editStudent() {
        setTitle("Edit Students window");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(8, 2));

        panel.add(new JLabel("ID:"));
        idField = new JTextField();
        panel.add(idField);

        panel.add(new JLabel("Name:"));
        nameField = new JTextField();
        panel.add(nameField);
        
        panel.add(new JLabel("Gender:"));
        genderField = new JTextField();
        panel.add(genderField);

        panel.add(new JLabel("Age:"));
        ageField = new JTextField();
        panel.add(ageField);

        panel.add(new JLabel("Course:"));
        courseField = new JTextField();
        panel.add(courseField);
        

        JButton addButton = new JButton("Edit Student");
        panel.add(addButton);
        addButton.addActionListener(new EditButtonListener_2());

        displayArea = new JTextArea();
        displayArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(displayArea);

        add(panel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);

        displayArea.setText("");
	    try (BufferedReader reader = new BufferedReader(new FileReader("students.txt"))) {
	        String line;
	        while ((line = reader.readLine()) != null) {
	            displayArea.append(line);
	            displayArea.append("\n");
	        }
	    } catch (IOException e) {
	        e.printStackTrace();
	    }
    }
    private class EditButtonListener_2 implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            JPanel s_ = new JPanel();
            s_.add(new JLabel("test"));
        }
    }
}
