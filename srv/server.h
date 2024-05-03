/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:46:40 by inikulin          #+#    #+#             */
/*   Updated: 2024/05/03 21:48:22 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include "libft.h"

typedef struct s_global
{
	unsigned int		bytes_promised;
	int					len_bits;
	unsigned int		bytes_printed;
	unsigned char		sym_cur[6];
	char				sym_bits;
	char				sym_bits_exp;
	struct sigaction	action;
}	t_global;

extern t_global	g_g;
#endif
