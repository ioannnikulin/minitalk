/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:46:40 by inikulin          #+#    #+#             */
/*   Updated: 2024/05/03 21:49:28 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_global	g_g;

static void	get_len(int signal)
{
	g_g.bytes_promised <<= 1;
	g_g.len_bits ++;
	if (signal == SIGUSR2)
		g_g.bytes_promised ++;
}

void	get_text(int signal, siginfo_t *info);

static void	getit(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (g_g.len_bits < 32)
		get_len(signal);
	else
	{
		if (g_g.len_bits == 32 && g_g.bytes_printed == 0 && g_g.sym_bits == 0)
		{
			ft_printf("Incoming message, length: %i bytes\n",
				g_g.bytes_promised);
			ft_bzero(g_g.sym_cur, 6);
			g_g.sym_bits_exp = 8;
		}
		get_text(signal, info);
	}
}

static void	init_g_g(void)
{
	g_g.bytes_promised = 0;
	g_g.len_bits = 0;
	g_g.bytes_printed = 0;
	ft_bzero(g_g.sym_cur, 6);
	g_g.sym_bits = 0;
	g_g.sym_bits_exp = 8;
	sigemptyset(&g_g.action.sa_mask);
	g_g.action.sa_sigaction = getit;
	g_g.action.sa_flags = SA_SIGINFO;
}

int	main(void)
{
	int	pid;

	init_g_g();
	pid = getpid();
	ft_printf("PID: %i\n", pid);
	while (1)
	{
		sigaction(SIGUSR1, &g_g.action, 0);
		sigaction(SIGUSR2, &g_g.action, 0);
		pause();
	}
}
