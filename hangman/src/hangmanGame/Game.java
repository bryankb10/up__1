package hangmanGame;
import java.util.Scanner;
public class Game {
	//ARRAY OF WORDS AVAILABLE
	private static String[]words = {"hamburger", "steak", "spaghetti", "pizza", "salmon", "hentai", "cheeseburger", "ice cream"};
	//RNG to pick the word
	private static String word = words[(int) (Math.random()* words.length)];
	//HIde the words
	private static String hiddenWord = new String(new char[word.length()]).replace("\0", "-");
    private static int remainingAttempts = 5;
    public static int score = 0;
    
    public static void main(String[] args) {
    	//to scan the letter(i want it to be able to directly read the answer)
    	Scanner scanner = new Scanner(System.in);
    	while(remainingAttempts > 0 && hiddenWord.contains("-")) {
    		 System.out.println("Guess a letter (you have " + remainingAttempts + " attempts left):");
             System.out.println(hiddenWord);
             String guess = scanner.next();
             if (guess.length()== 1) {
            	 if (word.contains(guess)) {
                	 hiddenWord = updateHiddenWord(guess);
                 }
            	 else {
                	 remainingAttempts--;
            	 }
             }
             else if(guess.equals(word)) {
            	 hiddenWord = word;
             }
             else {
            	 remainingAttempts--;
             }

    	}
    	scanner.close();
    	System.out.println("The word was: " + word);
    	if(remainingAttempts == 0) {
    		System.out.println("Sheesh, You suck");
    	}
    	else {
    		System.out.println("Congrats");
    		score++;
    		System.out.println("Score: " + score);
    		}
    	}
    private static String updateHiddenWord(String guess) {
    	StringBuilder newHiddenWord = new StringBuilder(hiddenWord);
    	for(int i = 0; i<word.length(); i++) {
    		if(word.charAt(i)==guess.charAt(0)) {
    			newHiddenWord.setCharAt(i, guess.charAt(0));
    		}
    	}
    	return newHiddenWord.toString();
    }
}
