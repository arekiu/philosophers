#include "philosophers.h"

static long long	ft_convert_to_ll(const char *str, int negative)
{
	int			i;
	long long	new_num;

	i = 0;
	new_num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (new_num > (LLONG_MAX - (str[i] - '0')) / 10)
		{
			if (negative == 1)
				return (LLONG_MAX);
			else
				return (LLONG_MIN);
		}
		new_num = (new_num * 10) + (str[i] - '0');
		i++;
	}
	return (new_num * negative);
}

static long long	ft_atoll(const char *str)
{
	int			i;
	int			negative;

	i = 0;
	negative = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			negative = -1;
		if (str[i + 1] == '+' || str[i + 1] == '-')
			return (0);
		i++;
	}
	return (ft_convert_to_ll(&str[i], negative));
}

static int	ft_isdigit(int num)
{
	if (num >= '0' && num <= '9')
		return (1);
	else
		return (0);
}

static int	is_int(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int is_valid(int argc, char *argv[])
{
    int i;
    long long   num;

    i = 0;
    while (i < argc - 1)
    {
        if (!is_int(argv[i + 1]))
            return (0);
        num = ft_atoll(argv[i + 1]);
        if (num > INT_MAX || num < INT_MIN)
            return (0);
        i++;
    }
    return (1);
}
