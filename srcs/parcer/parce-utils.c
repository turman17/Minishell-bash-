/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:09:29 by nkarpeko          #+#    #+#             */
/*   Updated: 2024/01/30 20:21:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

struct s_cmd	*execcmd(void)
{
	struct s_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (cmd == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = ' ';
	return ((struct s_cmd *)cmd);
}

struct s_cmd	*redircmd(struct s_cmd *subcmd, char *file, int type)
{
	struct s_redircmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = type;
	cmd->cmd = subcmd;
	cmd->file = file;
	if (type == '<' || type == '-')
	{
		cmd->mode = O_RDONLY;
		cmd->fd = 0;
	}
	else if (type == '>')
	{
		cmd->mode = O_WRONLY | O_CREAT | O_TRUNC;
		cmd->fd = 1;
	}
	else if (type == '+')
	{
		cmd->mode = O_WRONLY | O_CREAT | O_APPEND;
		cmd->fd = 1;
	}
	return ((struct s_cmd *)cmd);
}

struct s_cmd	*pipecmd(struct s_cmd *left, struct s_cmd *right)
{
	struct s_pipecmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = '|';
	cmd->left = left;
	cmd->right = right;
	return ((struct s_cmd *)cmd);
}
