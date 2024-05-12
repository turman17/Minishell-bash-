/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:17:20 by root              #+#    #+#             */
/*   Updated: 2024/01/30 19:53:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_exec_cmd(struct s_execcmd *ecmd)
{
	if (ecmd)
	{
		ft_free_char_arr(ecmd->argv);
		ecmd->argv = NULL;
	}
}

void	free_pipecmd(struct s_pipecmd *pcmd)
{
	if (pcmd->left)
	{
		free_cmd(pcmd->left);
		pcmd->left = NULL;
	}
	if (pcmd->right)
	{
		free_cmd(pcmd->right);
		pcmd->right = NULL;
	}
}

void	free_redircmd(struct s_redircmd *rcmd)
{
	if (rcmd->cmd)
	{
		free_cmd(rcmd->cmd);
		rcmd->cmd = NULL;
	}
	if (rcmd->file)
	{
		free(rcmd->file);
		rcmd->file = NULL;
	}
}

void	free_cmd(struct s_cmd *command)
{
	if (!command)
		return ;
	if (command->type == ' ')
		free_exec_cmd((struct s_execcmd *)command);
	else if (command->type == '|')
		free_pipecmd((struct s_pipecmd *)command);
	else if (command->type == '>' || command->type == '<'
		|| command->type == '+' || command->type == '-')
		free_redircmd((struct s_redircmd *)command);
	free(command);
}
