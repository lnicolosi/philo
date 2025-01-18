#include "philo.h"

/*
    The Main is a TL;DR of the program

    ./philo 5 800 200 200 [5]
*/
int main(int argc, char **argv)
{
	t_table table;
	if (5 == argc || 6 == argc)
	{
		// correct input
		//1) errors checking, filling table table
		pars_input(&table, argv);

		//2) creating the actual thing
		data_init(&table);

		//3)
		dinner_start(&table);

		//4) No leaks -> philo is full | 1 philo died
		//clean(&table);
	}
	else
	{
		// wrong input
		error_exit("Wrong input:\n"
				G"Correct is ./philo 5 800 200 200 [5]"RST);
	}
	
}