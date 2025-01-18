#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

/*
	write function macro
*/
#define DEBUG_MODE	0

/*
	ANSI Escape Sequeces for Bold Text Colors
	Usage :
		printf(R "This is red text." RST);
		printf(B "This is blue text." RST);
	Remember to use RST to reset the color after setting it.
*/

# define RST	"\033[0m"		/* Reset to default color */
# define RED	"\033[1;31m"	/* Bold Red */
# define G		"\033[1;32m"	/* Bold Green */
# define Y		"\033[1;33m"	/* Bold Yellow */
# define B		"\033[1;34m"	/* Bold Blue */
# define M		"\033[1;35m"	/* Bold Magenta */
# define C		"\033[1;36m"	/* Bold Cyan */
# define W		"\033[1;37m"	/* Bold White */

//********************************
//*** ENUM philo states
typedef enum	e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}				t_philo_status;

//*** ENUM opcode for mutex and thread functions ***
typedef enum	e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}				t_opcode;

//*** ENUM codes for gettime ***
typedef enum	e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}				t_time_code;



//********************************
//*** STRUCTURES ***

/*___________________________
	code more readable
*/
typedef pthread_mutex_t	t_mtx;

/*___________________________
	IOU for compiler
*/
typedef struct	s_table	t_table;

/*___________________________
	FORK
*/
typedef struct	s_fork
{
	t_mtx	fork;
	int		fork_id;
}				t_fork;

/*___________________________
	PHILO

	./philo 5 800 200 200 [5]
*/
typedef struct	s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;	// time passed from last meal
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id; // a philo is a thread
	t_mtx		philo_mutex; //useful for races with the monitor
	t_table		*table;
	
}				t_philo;

/*_____________________________
	TABLE
	
	./philo 5 800 200 200 [5]
*/
struct	s_table
{
	long		philo_nbr; // 5
	long		time_to_die; // 800
	long		time_to_eat; // 200
	long		time_to_sleep; // 200
	long		nbr_limit_meals; // [5] | FLAG if -1
	long		start_simulation; 
	bool		end_simulation; // a philo dies or all philo full
	bool		all_threads_ready; // syncro philos
	long		threads_running_nbr;
	pthread_t	monitor;
	t_mtx		table_mutex; // avoid races while reading from table
	t_mtx		write_mutex;
	t_fork		*forks; // array of forks
	t_philo		*philos; // array of philos
};

//********************************
// *** PROTOTYPES ***

// *** utils ***
void	error_exit(const char *error);
long	gettime(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);

// *** dinner ***
void	dinner_start(t_table *table);
void	thinking(t_philo *philo, bool pre_simulation);

// *** monitor ***
void	*monitor_dinner(void *data);

// *** write ***
void	write_status(t_philo_status status, t_philo *philo, bool debug);

// *** parsing ***
void	pars_input(t_table *table, char **av);

// *** init ***
void	data_init(t_table *table);

// *** safe functions ***
void	*safe_malloc(size_t bytes);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);

// *** synchro utils ***
void	wait_all_threads(t_table *table);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void	increase_long(t_mtx *mutex, long *value);
void	de_synchronize_philos(t_philo *philo);

// *** setter and getters ***
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	simulation_finished(t_table *table);

#endif