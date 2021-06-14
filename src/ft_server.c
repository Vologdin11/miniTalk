#include "../minitalk.h"

t_var	g_var;

static void	error(void)
{
	if (g_var.str != NULL)
	{
		free(g_var.str);
		g_var.str = NULL;
	}
	write(1, "Error\n", 6);
	exit(EXIT_FAILURE);
}

static void	work_str(int signal)
{
	static unsigned int	i = 0;
	static int			count = 128;
	static char			ch = 0;

	if (signal == SIGUSR1)
		ch += count;
	count >>= 1;
	if (count == 0)
	{
		g_var.str[i++] = ch;
		count = 128;
		ch = 0;
		if (i == g_var.len)
		{
			write(1, g_var.str, g_var.len);
			free(g_var.str);
			g_var.str = NULL;
			g_var.get_len = 0;
			g_var.len = 0;
			i = 0;
		}
	}
}

static void	work_len(int signal)
{
	static unsigned int	count = 2147483648;

	if (signal == SIGUSR1)
		g_var.len += count;
	count >>= 1;
	if (count == 0)
	{
		g_var.get_len = 1;
		count = 2147483648;
		g_var.str = (char *)malloc(sizeof(char) * (g_var.len + 1));
		if (g_var.str == NULL)
			error();
		g_var.str[g_var.len] = '\0';
	}
}

int	main(void)
{
	char				*pid;
	struct sigaction	handler;

	g_var.len = 0;
	g_var.get_len = 0;
	pid = ft_itoa(getpid());
	write(1, pid, ft_strlen(pid));
	write(1, "\n", 1);
	sigemptyset(&handler.sa_mask);
	sigaddset(&handler.sa_mask, SIGUSR1);
	sigaddset(&handler.sa_mask, SIGUSR2);
	while (1)
	{
		if (g_var.get_len == 0)
			handler.sa_handler = work_len;
		else
			handler.sa_handler = work_str;
		if (sigaction(SIGUSR1, &handler, NULL) < 0 || \
		sigaction(SIGUSR2, &handler, NULL) < 0)
			error();
		usleep(1);
	}
}
