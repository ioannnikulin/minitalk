/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:46:40 by inikulin          #+#    #+#             */
/*   Updated: 2024/05/03 21:54:32 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static unsigned char	sym_len(unsigned char c)
{
	if ((c & 252) == 252)
		return (48);
	if ((c & 248) == 248)
		return (40);
	if ((c & 240) == 240)
		return (32);
	if ((c & 224) == 224)
		return (24);
	if ((c & 192) == 192)
		return (16);
	return (8);
}

void	get_text(int signal, siginfo_t *info)
{
	g_g.sym_cur[g_g.sym_bits / 8] <<= 1;
	if (signal == SIGUSR2)
		g_g.sym_cur[g_g.sym_bits / 8]++;
	g_g.sym_bits ++;
	if (g_g.sym_bits == g_g.sym_bits_exp)
	{
		if (g_g.sym_bits_exp == 8)
			g_g.sym_bits_exp = sym_len(g_g.sym_cur[0]);
		if (g_g.sym_bits != g_g.sym_bits_exp)
			return ;
		write(1, g_g.sym_cur, g_g.sym_bits / 8);
		g_g.bytes_printed += g_g.sym_bits / 8;
		ft_bzero(g_g.sym_cur, 6);
		g_g.sym_bits_exp = 8;
		g_g.sym_bits = 0;
		if (g_g.bytes_printed >= g_g.bytes_promised)
		{
			ft_printf("\n");
			g_g.bytes_promised = 0;
			g_g.len_bits = 0;
			g_g.bytes_printed = 0;
			usleep(10);
			kill(info->si_pid, SIGUSR1);
		}
	}
}
