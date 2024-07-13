/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 17:21:05 by ael-amin          #+#    #+#             */
/*   Updated: 2023/01/12 17:41:18 by ael-amin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_pow(int nb, int power)
{
	int	result;

	result = 1;
	while (power)
	{
		result *= nb;
		power--;
	}
	return (result);
}

void	handlesig(int signo, siginfo_t *sig_info, void *context)
{
	static int	res;
	static int	i;
	static int	pid;

	(void)context;
	if (pid != sig_info->si_pid)
	{
		res = 0;
		i = 0;
		pid = sig_info->si_pid;
	}
	if (signo == SIGUSR2)
		res += ft_pow(2, 7 - i);
	else if (signo == SIGUSR1)
		res += 0;
	i++;
	if (i == 8)
	{
		write(1, &res, 1);
		if (!res)
			kill (sig_info->si_pid, SIGUSR1);
		res = 0;
		i = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	sa.sa_sigaction = &handlesig;
	sa.sa_flags = SA_SIGINFO;
	pid = getpid();
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_putstr_fd("Pid : ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
	while (1)
		pause();
}
