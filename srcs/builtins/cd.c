/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:09:53 by nkarpeko          #+#    #+#             */
/*   Updated: 2024/01/30 18:42:17 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_to_home_directory(char **custom_environ)
{
	char	*home_dir;

	home_dir = custom_getenv("HOME", custom_environ, 0);
	if (home_dir)
	{
		if (chdir(home_dir) == 0)
			g_exit_code = 0;
		else
			g_exit_code = 1;
	}
	else
	{
		ft_printf("minishell# cd: HOME not set\n");
		g_exit_code = 1;
	}
}

void	change_to_specified_directory(char *new_buf)
{
	struct stat	file_stat;

	if (stat(new_buf, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			if (chdir(new_buf) == 0)
				g_exit_code = 0;
			else
				g_exit_code = 1;
		}
		else
		{
			ft_printf("minishell# cd: %s: Not a directory\n", new_buf);
			g_exit_code = 1;
		}
	}
	else
	{
		ft_printf("minishell# cd: %s: No such file or directory\n", new_buf);
		g_exit_code = 1;
	}
}

void	ft_cd(char *buf, char **custom_environ)
{
	char	*new_buf;

	new_buf = ft_str_remove_chars(buf, " ");
	if (ft_strlen(new_buf) == 0)
		change_to_home_directory(custom_environ);
	else
		change_to_specified_directory(new_buf);
	free(new_buf);
}
