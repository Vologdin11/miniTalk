#include "../minitalk.h"

static int	ft_checklimits(long long num, char	ch, long long sign)
{
	num = num * 10 + (ch - '0');
	num *= sign;
	if (num < -2147483648)
		return (0);
	if (num > 2147483647)
		return (-1);
	return (1);
}

int	ft_atoi(const char *str)
{
	unsigned int	i;
	long long		sign;
	long long		num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'\
	|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		if (ft_checklimits(num, str[i], sign) == 1)
			num = num * 10 + (str[i++] - '0');
		else
			return (ft_checklimits(num, str[i], sign));
	}
	return ((int)num * sign);
}
