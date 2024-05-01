/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:42:42 by inikulin          #+#    #+#             */
/*   Updated: 2024/05/01 21:44:39 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"

static void	send_number(int num, int pid)
{
	int	bit_mask;

	kill(pid, SIGUSR1);
	usleep(100);
	bit_mask = 1 << 30;
	while (bit_mask)
	{
		if (num & bit_mask)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
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
		kill(pid, SIGUSR1);
		usleep(100);
		bit_mask = 1 << 6;
		while (bit_mask)
		{
			if (s[sym_i] & bit_mask)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
			bit_mask >>= 1;
		}
	}
}

int	main(int argc,  char **argv)
{
	int	pid;
	int	ok;

	if (argc != 3)
		return (-1);
	ok = 0;
	pid = ft_atoi(argv[1], &ok);
	if (!ok)
		return (-1);
	send_number(ft_strlen(argv[2]), pid);
	send_text(argv[2], pid);
	return (0);
}
