/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:48:22 by aschmidt          #+#    #+#             */
/*   Updated: 2024/09/05 12:42:01 by aschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	negative;
	int	new_num;

	i = 0;
	negative = 1;
	new_num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			negative = negative * -1;
		if (str[i + 1] == '+' || str[i + 1] == '-')
			return (0);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((new_num == 214748364) && (str[i] == '8') && (negative == -1))
			return (-2147483648);
		new_num = (new_num * 10) + (str[i] - '0');
		i++;
	}
	return (new_num * negative);
}

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

long long	ft_atoll(const char *str)
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

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid(int argc, char *argv[])
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (!is_number(argv[i + 1]) || (ft_atoll(argv[i + 1]) \
		> INT_MAX || ft_atoll(argv[i + 1]) < INT_MIN))
		{
			printf("Invalid arguments\n");
			return (0);
		}
		i++;
	}
	if (ft_atoi(argv[1]) == 0)
	{
		printf("No philosophers\n");
		return (0);
	}
	if (argc == 6 && ft_atoi(argv[5]) == 0)
	{
		printf("No foods to be eaten\n");
		return (0);
	}
	return (1);
}
