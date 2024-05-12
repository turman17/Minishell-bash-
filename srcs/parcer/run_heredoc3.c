/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:38:58 by nkarpeko          #+#    #+#             */
/*   Updated: 2024/01/30 20:47:45 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_double_redirect_left(struct s_redircmd *rcmd, char ***custom_environ)
{
	int	original_stdin;
	int	pipe_read_end;

	original_stdin = dup(STDIN_FILENO);
	pipe_read_end = double_redirect_left(rcmd, *custom_environ);
	if (pipe_read_end < 0)
	{
		perror("double_redirect_left");
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdin);
		g_exit_code = 1;
		return (-1);
	}
	runcmd(rcmd->cmd, custom_environ);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	return (1);
}
