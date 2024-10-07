package hangmanGame;
import javax.swing.*;
import java.awt.event.*;
public class TimerExample {
	private static final int TIMER_DELAY = 1000;
	private Timer timer;
	private int counter;
	
	public TimerExample() {
		counter = 0;
		timer = new Timer(TIMER_DELAY, new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				counter++;
				System.out.println(counter);
			}
		});
	}
	public void startTimer() {
		timer.start();
	}
	public void stopTimer() {
		timer.stop();
	}
	public static void main(String[] args) {
		TimerExample timerExample = new TimerExample();
		timerExample.startTimer();
		try {
			Thread.sleep(1000000);
		}catch (InterruptedException e) {
			e.printStackTrace();
		}
		timerExample.stopTimer();
		
	}
}
