package idk;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import javax.swing.*;

public class studentManagement extends JFrame {
    private JTextField idField, nameField, ageField, courseField, genderField;
    private JTextArea displayArea;

    public studentManagement() {
        setTitle("Student Management System");
        setSize(750, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(8, 3));

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
        

        JButton addButton = new JButton("Add Student");
        panel.add(addButton);
        addButton.addActionListener(new AddButtonListener());

        JButton viewButton = new JButton("View Students");
        panel.add(viewButton);
        viewButton.addActionListener(new ViewButtonListener());

        JButton editButton = new JButton("Edit data");
        panel.add(editButton);
        editButton.addActionListener(new EditButtonListener());

        displayArea = new JTextArea();
        displayArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(displayArea);

        add(panel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
    }

    private class AddButtonListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String id = idField.getText();
            String name = nameField.getText();
            int age = Integer.parseInt(ageField.getText());
            String course = courseField.getText();
            String gender = genderField.getText();
            Student student = new Student(id, name, age, course, gender);
            saveStudent(student);
            clearFields();
        }
    }

    private class ViewButtonListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            DisplayStudents();
        }
    }

    private class EditButtonListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            editStudent Editfeature = new editStudent();
        }
    }

    private void saveStudent(Student student) {
	    try (BufferedWriter writer = new BufferedWriter(new FileWriter("students.txt", true))) {
	        writer.write(student.toString());
	        writer.newLine();
	    } catch (IOException e) {
	        e.printStackTrace();
	    }
	}


    private void DisplayStudents() {
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
    

    private void clearFields() {
        idField.setText("");
        nameField.setText("");
        ageField.setText("");
        courseField.setText("");
        genderField.setText("");
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            new studentManagement().setVisible(true);
        });
    }
}
