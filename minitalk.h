#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

typedef struct s_var
{
	unsigned int	len;
	int				get_len;
	char			*str;
}				t_var;

char	*ft_itoa(int n);
int		ft_strlen(const char *str);
int		ft_atoi(const char *str);

#endif
