/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmidt <aschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:53:22 by aschmidt          #+#    #+#             */
/*   Updated: 2024/08/01 15:49:31 by aschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	if (argc == 5 || argc == 6)
	{
		if (!is_valid(argc, argv))
		{
			printf("Invalid arguments\n");
			return (0);
		}
		else
			printf("Todo bien!\n");
	}
	else
	{
		printf("Invalid number of arguments\n");
		return (0);
	}
	return (0);
}
