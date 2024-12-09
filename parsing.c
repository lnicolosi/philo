#include "philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}


/*
	1) check for negatives
	2) check if num is legit
		"      +329$& "
		"    +ç%245"
	3) check for INT_MAX
	4) return ptr to 1st num
*/
static const char   *valid_input(const char *str)
{
	int         len;
	const char  *number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Only positive value!");
	if (!is_digit(*str))
		error_exit("Input not correct digit!");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("Value is too big!");
	return (number);
}


static long	ft_atol(const char *str)
{
	long    num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		error_exit("Value is too big!");
	return (num);
}

/*
				  ms	ms		ms
	./philo 5    800    200     200    [5]
		  av[1] av[2]  av[3]  av[4]   av[5]
	1) actual numbers
	2) not > INT_MAX
	3) timesstamps > 60ms

	USLEEP function want micro secod (not milisecond)
*/
void	pars_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3; //1e3 = 1000 (1 et 3 zero)
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_exit("Use timestamps major than 60ms");
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5])
	else
		table->nbr_limit_meals = -1;



}