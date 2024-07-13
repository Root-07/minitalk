/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 13:53:07 by ael-amin          #+#    #+#             */
/*   Updated: 2023/01/11 15:39:27 by ael-amin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	if (argc == 3)
	{
		while (argv[2][i] != '\0')
		{
			j = 7;
			while (j >= 0)
			{
				if (argv[2][i] >> j & 1)
					kill(ft_atoi (argv[1]), SIGUSR2);
				else
					kill(ft_atoi (argv[1]), SIGUSR1);
				usleep(180);
				j--;
			}
			i++;
		}
	}
	else
		ft_putstr_fd("\033[1;31m L'erreur: doit être saisie 3 arg!!!\033[0m\n", 1);
	return (0);
}
