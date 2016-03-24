#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <time.h>
#include "PA4_functions.h"

void print_game_rules (void)
{
	printf("Craps Rules:\n If the sum is 7 or 11 on the first throw, the player wins. If the sum is 2, 3, or 12 on the first throw it is called craps and the player loses. If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the player's point. To win, the player must continue rolling the dice until they make their point. The player loses by rolling a 7 before making their point.\n");
}

double get_bank_balance (void)
{
	double starting_balance = 0;
	printf("Enter your starting balance: ");
	scanf("%lf", &starting_balance);
	return starting_balance;
}

double get_wager_amount (void)
{
	double wager = 0;
	printf("Enter your wager: ");
	scanf("%lf", &wager);
	return wager;
}
int check_wager_amount (double wager, double balance)
{
	int check = 0;
	if (wager <= balance)
	{
		check = 0;
	}
	else if (wager > balance)
	{
		check = 1;
	}
	return check;
}
int roll_die(void)
{
	int die1 = 0;
	die1 = rand() % 6 + 1;
	return die1; //Need to restrict range to 1-6, so x % 6 can be 0-5, then add 1 so range is 1-6
}
int reroll(void)
{
	int die1 = 0, die2 = 0, sum_die = 0, result = 0, points = 0;
	die1 = roll_die();
	die2 = roll_die();
	sum_die = calculate_sum_dice(die1, die2);
	return sum_die;
}

int calculate_sum_dice (int die1_value, int die2_value)
{
	int sum_dice = 0;
	sum_dice = die1_value + die2_value;
	printf("You rolled %d\n", sum_dice);
	return sum_dice;
}
int is_win_loss_or_point (int sum_dice)
{
	int result = 0;

	if (7 == sum_dice || 11 == sum_dice)
	{
		result = 1;
		return result;
	}
	else if (2 == sum_dice || 3 == sum_dice || 12 == sum_dice)
	{
		result = 0;
		return result;
	}
	else
	{
		result = -1;
		return result;
	}
}
int is_point_loss_or_neither (int sum_dice, int point_value)
{
	int result = 0;

	if (7 == sum_dice)
	{
		result = 0;
		return result;
	}
	else if (sum_dice == point_value)
	{
		result = 1;
		return result;
	}
	else
	{
		result = -1;
		return result;
	}
}
double adjust_bank_balance (double bank_balance, double wager_amount, int add_or_subtract)
{
	int final_balance = 0;

	if (add_or_subtract == 1)
	{
		final_balance = bank_balance + wager_amount;
		return final_balance;
	}
	else if (add_or_subtract == 0)
	{
		final_balance = bank_balance - wager_amount;
		return final_balance;
	}
}
void chatter_messages (int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance)
{	
	if (initial_bank_balance == current_bank_balance)
	{
		printf("Nice job on breaking even.\n");
	}
	if ((current_bank_balance < initial_bank_balance) && (win_loss_neither != 0 || win_loss_neither != 1))
	{
		printf("Going for broke, huh?\n");
	}
	if (current_bank_balance > initial_bank_balance)
	{
		printf("You've got hot dice, my friend!\n");
	}
	if (number_rolls < 2 && (win_loss_neither != 0 || win_loss_neither != 1))
	{
		printf("Keep rolling! You got this!\n");
	}
	if (number_rolls >= 5)
	{
		printf("You're still here?\n");
	}
	if (win_loss_neither == 0)
	{
		printf("Sorry about it, champ!\n");
	}
	if (win_loss_neither == 1)
	{
		printf("Nice game! Care to play again?\n");
	}
	if (win_loss_neither == -1)
	{
		printf("Play on, my friend!\n");
	}
}