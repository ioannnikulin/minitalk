/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:42:42 by inikulin          #+#    #+#             */
/*   Updated: 2024/05/02 21:04:09 by inikulin         ###   ########.fr       */
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

static int	sym_len(char *s)
{
	unsigned char	c;

	c = *s;
	if (c & 128 == 0)
		return (1);
	if (c & 192 == 192)
		return (2);
	if (c & 224 == 224)
		return (3);
	if (c & 240 == 240)
		return (4);
	if (c & 248 == 248)
		return (5);
	return (6);
}

static void	send_text(char *s, int pid)
{
	int				sym_i;
	unsigned char	bit_mask;
	int				sym_len;

	sym_i = 0;
	while (s[sym_i])
	{
		sym_len = sym_len(s[sym_i]);
		bit_mask = 1 << (8 * sym_len - 1);
		while (bit_mask)
		{
			if (s[sym_i] & bit_mask)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
			bit_mask >>= 1;
		}
		sym_i += sym_len;
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
