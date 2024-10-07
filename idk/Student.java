package idk;

public class Student {
	private String id;
	private String name;
	private int age;
	private String course;
	private String gender;
	
	public Student(String id, String name, int age, String course, String gender) {
		this.id = id;
		this.name = name;
		this.age = age;
		this.course = course;
		this.gender = gender;
	}
	public String getID() {
		return id;
	}
	public void setID(String id) {
		this.id = id;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public int getAge() {
		return age;
	}
	public void setAge(int age) {
		this.age = age;
	}
	public String getCourse() {
		return course;
	}
	public void setCourse(String course) {
		this.course = course;
	}
	public String getGender() {
		return gender;
	}
	public void setGender(String gender) {
		this.gender = gender;
	}
	
	@Override
	public String toString() {
		return id + "," + name + "," + age + "," + gender + "," + course;
	}
}
