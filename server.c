/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:46:40 by inikulin          #+#    #+#             */
/*   Updated: 2024/05/02 20:47:30 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "libft.h"

typedef struct s_global
{
	unsigned int		len_promised;
	int					len_bits;
	unsigned int		sym_printed;
	unsigned char				sym_cur;
	char				sym_bits;
	struct sigaction	action;
}	t_global;

t_global g_g;

static void	get_len(int signal)
{
	g_g.len_promised <<= 1;
	g_g.len_bits ++;
	if (signal == SIGUSR2)
		g_g.len_promised ++;
}

static void	get_text(int signal)
{
	g_g.sym_cur <<= 1;
	g_g.sym_bits ++;
	if (signal == SIGUSR2)
		g_g.sym_cur ++;
	if (g_g.sym_bits == 8)
	{
		g_g.sym_bits = 0;
		ft_printf("%c", g_g.sym_cur, g_g.sym_cur);
		g_g.sym_cur = 0;
		if (++ g_g.sym_printed >= g_g.len_promised)
		{
			ft_printf("\n");
			g_g.len_promised = 0;
			g_g.len_bits = 0;
			g_g.sym_printed = 0;
		}
	}
}

static void	getit(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (g_g.len_bits < 32)
		get_len(signal);
	else
	{
		if (g_g.len_bits == 32 && g_g.sym_printed == 0 && g_g.sym_bits == 0)
		{
			ft_printf("Incoming message, length: %i\n", g_g.len_promised);
			g_g.sym_cur = 0;
		}
		get_text(signal);
	}
}

static void	init_g_g()
{
	g_g.len_promised = 0;
	g_g.len_bits = 0;
	g_g.sym_printed = 0;
	g_g.sym_cur = 0;
	g_g.sym_bits = 0;
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
