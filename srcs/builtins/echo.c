/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:09:51 by nkarpeko          #+#    #+#             */
/*   Updated: 2024/01/30 18:25:05 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo_n_handler(char *buf, int *newline)
{
	int	idx;

	idx = 2;
	if (ft_strncmp(buf, "-n", 2) == 0)
	{
		*newline = 0;
		while (buf[idx] == 'n')
			(idx)++;
		if (buf[idx] != '\0')
			*newline = 1;
	}
	else
		*newline = 1;
}

void	echo(char **buf_args)
{
	int	newline;
	int	idx;

	idx = -1;
	newline = 1;
	echo_n_handler(buf_args[0], &newline);
	if (newline == 0)
		idx++;
	while (buf_args[++idx])
	{
		if (buf_args[idx + 1])
			ft_printf("%s ", buf_args[idx]);
		else
			ft_printf("%s", buf_args[idx]);
	}
	if (newline)
		ft_printf("\n");
	g_exit_code = 0;
}
