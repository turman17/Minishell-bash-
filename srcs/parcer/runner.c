/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:09:13 by nkarpeko          #+#    #+#             */
/*   Updated: 2024/01/30 19:42:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_error(char *cmd)
{
	if (errno == EACCES)
	{
		write(2, cmd, strlen(cmd));
		write(2, ": permission denied\n", 20);
		return (126);
	}
	else if (errno == ENOENT)
	{
		write(2, cmd, strlen(cmd));
		write(2, ": command not found\n", 20);
		return (127);
	}
	else
	{
		perror(cmd);
		return (127);
	}
}

int	runcmd(struct s_cmd *cmd, char ***env)
{
	char	type;

	type = cmd->type;
	if (type == ' ')
	{
		exec_cmd(cmd, env);
		return (1);
	}
	else if (type == '>' || type == '<' || type == '+' || type == '-')
		redirect_cmd((struct s_redircmd *)cmd, env);
	else if (type == '|')
		pipe_command((struct s_pipecmd *)cmd, env);
	else
	{
		printf("unknown runcmd\n");
		return (-1);
	}
	return (1);
}
