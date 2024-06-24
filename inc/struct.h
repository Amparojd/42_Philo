/* Enum */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

enum e_mssg
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEATH
};

/* Structs */

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	int					l_fork;
	int					r_fork;
	long				deadline;
	pthread_mutex_t		deadline_mutex;
	pthread_mutex_t		meals_mutex;
	pthread_t			ph_thread;
	struct s_philoenv	*philoenv;
}	t_philo;

typedef struct s_philoenv
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_meals;
	long			start_time;
	int				stop_time;
	int				num_fin_eating;
	pthread_mutex_t	msg;
	pthread_mutex_t	check_stop;
	pthread_mutex_t	check_fin_eating;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		monitor;
}	t_philoenv;