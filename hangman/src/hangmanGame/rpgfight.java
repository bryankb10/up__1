package hangmanGame;

import java.util.Random;
import java.util.Scanner;

public class rpgfight {
	public static void fight() {
		String Enemy;
		Enemy = "Goblin";
		int health, enemyHealth, attack, enemyAttack, chance, defense, enemyDefense;
		health = 100;
		attack = 10;
		defense = 10;
		enemyHealth = 50;
		enemyAttack = 5;
		enemyDefense = 5;
		Random rand = new Random();
		Scanner input = new Scanner(System.in);
		while (health>0 && enemyHealth>0) {
			chance = rand.nextInt(100);
			System.out.println("1. Attack");
			System.out.println("2. Defend");
			int choice = input.nextInt();
			if (choice==1) {
				if(chance >= 30) {
					System.out.println("You attacked "+Enemy);
					enemyHealth -= attack;
					System.out.println("You did " + attack + " damage");
				}
				else{
				System.out.println("Enemy attacked you for "+enemyAttack+" damage");
				}

			} else {
				if(defense>enemyAttack) {
					System.out.println("You Blocked the attack");
				} else {
					System.out.println("You failed to block the attack");
				}
			}
			if(enemyHealth<=0) {
				System.out.println("You have defeated "+Enemy);
				break;
			}
			if(health<=0) {
				System.out.println("You have been defeated by "+Enemy);
				break;
			}
		}
	}
	public static void TreasureChest() {
		String[]weapons = {"Sword","Dagger","Staff","Scythe"};
		Random rng = new Random();
		int chestContent = rng.nextInt(3);
		switch(chestContent) {
		case 0:
			String weapon = weapons[(int) (Math.random()* weapons.length)];
			//weapon nnti gw masukin +attack brp
			System.out.println("You found a "+weapon);
			break;
		case 1:
			System.out.println("You found a bag of gold coins");
			//masukin codingnya buat ksh uang(kl mau)
			break;
		case 2:
			System.out.println("You obtained a health potion");
			//ini jg tsrah
			break;
		default:
			System.out.println("The chest was empty.");
			break;
			
		}
	}
	public static void main(String[] args) {
		fight();
	}
}
	
