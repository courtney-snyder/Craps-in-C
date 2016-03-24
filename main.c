/*
Programmer: Courtney Snyder
Last Updated: 10/7/15
Description: A game of craps, using loops and user defined functions.
Credits: Rules copy & pasted from PA4 description. We wrote the roll_die function in class on 9/30.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "PA4_functions.h"

int main (void)
{
	double starting_balance = 0, wager = 0, check = 0, current_balance = 0;
	int die1 = 0, die2 = 0, first_sum_die = 0, reroll_sum_die = 0, result = 0, number_rolls = 0;
	FILE *input = NULL;
	FILE *output = NULL;
	srand((unsigned int)time(NULL)); //Makes the "dice" roll random numbers
	input = fopen("bank.txt", "w"); //Opens bank.txt in write mode so I can store the balance on there
	output = fopen("bank.txt", "r"); //Opens bank.txt in read mode so I can retrieve the balance from there

	print_game_rules(); //Shows the player how to play
	starting_balance = get_bank_balance(); //Gets the starting balance
	fprintf(input, "%lf", starting_balance); //Writes the balance into bank.txt
	wager = get_wager_amount(); //Gets the wager
	fprintf(input, "%lf", wager); //Writes the wager into bank.txt
	check = check_wager_amount(wager, starting_balance); //Checks to see if the wager is valid, if not, tells user to check the amount and closes program
		if (check == 1)
		{
			printf("You have entered an invalid wager amount. Please reevaluate your life.\n");
			return 0;
		}
	
	die1 = roll_die(); //Gets die1 value
	die2 = roll_die(); //Gets die2 value
	first_sum_die = calculate_sum_dice(die1, die2); //This will be the point. Declaring the first roll as a separate variable lets me reuse it as the point instead of creating a new variable point with the same value
	result = is_win_loss_or_point(first_sum_die); //Tells the program if the player won (1), lost (0), or made a point (-1). Nicely sets me up for writing an if loop

	if (result == 1) //If they win, roll a 7 or 11 on first roll
	{
		printf("Congratulations, you won $%.2lf!\n", wager); //Since the player rolled a 7 or 11, result == 1 from the is_win_loss_or_point function and the player gets to keep their money
		current_balance = adjust_bank_balance(starting_balance, wager, result);
		fprintf(input, "%lf", current_balance);
		chatter_messages(number_rolls, result, starting_balance, current_balance);
		printf("Your final balance is $%.2lf\n", current_balance);
		return 0; //Stops the program so it doesn't run through the do while loop
	}
	if (result == 0) //If they lose, roll a 2, 3, or 12 on first roll
	{
		printf("Sorry, you lost $%.2lf. Better luck next time, champ!\n", wager); //Since the player rolled a 2, 3, or 12, result == 0 from the is_win_loss_or_point and the player loses their money
		current_balance = adjust_bank_balance(starting_balance, wager, result);
		fprintf(input, "%lf", current_balance);
		chatter_messages(number_rolls, result, starting_balance, current_balance);
		printf("Your final balance is $%.2lf\n", current_balance);
		return 0; //Stops the program so it doesn't run through the do while loop
	}
	else if (result == -1) //If the player rolls anything else, they can roll again
	{
		printf("You need to get another %d to win.\n", first_sum_die); //Tells the player what their point is
		number_rolls += 1;
		current_balance = adjust_bank_balance(starting_balance, wager, result);
		fprintf(input, "%lf", current_balance);
		chatter_messages(number_rolls, result, starting_balance, current_balance);
	}
	do //The do while loop runs as long as the player isn't winning (making their point) or losing (rolling a 7)
	{
		reroll_sum_die = reroll(); //I liked the idea of creating a new variable for a reroll instead of calling roll_die twice and calculating the sum of the two dice
		result = is_point_loss_or_neither(reroll_sum_die, first_sum_die);
		number_rolls += 1 ;
		chatter_messages(number_rolls, result, starting_balance, current_balance);
			if (result == 1) //The player made their point
	{
		printf("Congratulations, you made your point and won $%.2lf!\n", wager);
		current_balance = adjust_bank_balance(starting_balance, wager, result);
		fprintf(input, "%lf", current_balance);
		printf("Your final balance is $%.2lf\n", current_balance);
		return 0; //Closes the program
	}
			else if (result == 0) //The player rolled a 7 and lost
	{
		printf("Sorry, you rolled a 7 and lost $%.2lf. Better luck next time, champ!\n", wager);
		current_balance = adjust_bank_balance(starting_balance, wager, result);
		fprintf(input, "%lf", current_balance);
		printf("Your final balance is $%.2lf\n", current_balance);
		return 0; //Closes the program
	}
	}
	while (result != 1 || result != 0); //If the result is 1 or 0, then the player has either won or lost, therefore the player can't keep playing on this wager
	return 0;
}