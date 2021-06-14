#include "../minitalk.h"

static void	error(void)
{
	write(1, "Error\n", 6);
	exit(EXIT_FAILURE);
}

static void	send_len(int len, pid_t pid)
{
	unsigned int	i;

	i = 2147483648;
	while (i > 0)
	{
		if (i & len)
		{
			if ((kill(pid, SIGUSR1)) < 0)
				error();
		}
		else
		{
			if ((kill(pid, SIGUSR2)) < 0)
				error();
		}
		i >>= 1;
		usleep(50);
	}
}

static void	send_str(char *str, pid_t pid)
{
	int		i;

	while (*str != '\0')
	{
		i = 128;
		while (i > 0)
		{
			if (i & *str)
			{
				if ((kill(pid, SIGUSR1)) < 0)
					error();
			}
			else
			{
				if ((kill(pid, SIGUSR2)) < 0)
					error();
			}
			i >>= 1;
			usleep(50);
		}
		str++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	(void)argc;
	pid = (pid_t)ft_atoi(argv[1]);
	if (!argv[1] || !argv[2] || !pid || pid == -1)
		error();
	send_len(ft_strlen(argv[2]), pid);
	send_str(argv[2], pid);
}
