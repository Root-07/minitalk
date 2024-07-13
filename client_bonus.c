/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 17:21:13 by ael-amin          #+#    #+#             */
/*   Updated: 2023/01/11 15:39:43 by ael-amin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_Bonus.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_send_bits(int pid, char *msg)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	len = ft_strlen(msg) + 1;
	while (i < len)
	{
		j = 7;
		while (j >= 0)
		{
			if (msg[i] >> j & 1)
			{
				kill(pid, SIGUSR2);
			}
			else
			{
				kill(pid, SIGUSR1);
			}
			usleep(180);
			j--;
		}
		i++;
	}
}

void	ft_print_message(int sig)
{
	if (sig == SIGUSR1)
		ft_putstr_fd("\033[1;32m Successful Communication\033[0m", 1);
}

int	main(int argc, char *argv[])
{
	if (argc == 3)
	{
		signal(SIGUSR1, ft_print_message);
		ft_send_bits(ft_atoi(argv[1]), argv[2]);
	}
	else
		ft_putstr_fd("\033[1;31m L'erreur: doit être saisie 3 arg!!!\033[0m\n", 1);
	return (0);
}
