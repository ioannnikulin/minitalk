/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:42:42 by inikulin          #+#    #+#             */
/*   Updated: 2024/05/03 21:54:15 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static void	send_number(unsigned int num, int pid)
{
	unsigned int	bit_mask;

	bit_mask = 1 << 31;
	while (bit_mask)
	{
		if (num & bit_mask)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(10);
		bit_mask >>= 1;
	}
}

static void	send_text(char *s, int pid)
{
	int				sym_i;
	unsigned char	bit_mask;

	sym_i = -1;
	while (s[++ sym_i])
	{
		bit_mask = 1 << 7;
		while (bit_mask)
		{
			if (s[sym_i] & bit_mask)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(10);
			bit_mask >>= 1;
		}
	}
}

static void	ack(int signal, siginfo_t *info, void *context)
{
	(void)signal;
	(void)info;
	(void)context;
	ft_printf("the server confirmed delivery\n");
	exit(0);
}

int	main(int argc, char **argv)
{
	int					pid;
	int					ok;
	struct sigaction	sa;

	if (argc != 3)
		return (-1);
	ok = 0;
	pid = ft_atoi(argv[1], &ok);
	if (!ok)
		return (-1);
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = ack;
	sa.sa_flags = SA_SIGINFO;
	send_number(ft_strlen(argv[2]), pid);
	send_text(argv[2], pid);
	while (1)
	{
		sigaction(SIGUSR1, &sa, 0);
		pause();
	}
	return (0);
}
