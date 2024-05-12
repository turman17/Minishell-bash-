/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:08:59 by nkarpeko          #+#    #+#             */
/*   Updated: 2024/01/30 20:48:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_exit_code;

void	execute_command(char *new_buf, char ***custom_env)
{
	struct s_cmd	*cmd;

	cmd = parsecmd(new_buf, *custom_env);
	free(new_buf);
	if (cmd->flag != 1 && g_exit_code != 7777)
		runcmd(cmd, custom_env);
	if (g_exit_code == 7777)
		g_exit_code = 2;
	free_cmd(cmd);
}

int	handle_exit_command(char *new_buf, char ***custom_env)
{
	if (!builtin_exit(new_buf + 4))
	{
		rl_clear_history();
		ft_free_char_arr(*custom_env);
		free(new_buf);
		exit(g_exit_code);
	}
	free(new_buf);
	return (1);
}

int	handle_something(char *new_buf, char ***custom_env)
{
	if (ft_strcmp(new_buf, "exit") == 0 || ft_strncmp(new_buf, "exit ", 5) == 0)
	{
		if (handle_exit_command(new_buf, custom_env))
			return (1);
	}
	if (ft_strlen(new_buf) && ft_isspace(new_buf[0]) == 0)
		add_history(new_buf);
	execute_command(new_buf, custom_env);
	return (0);
}

void	process_input(char ***custom_env)
{
	char	*new_buf;
	char	*buf;

	g_exit_code = 0;
	while (1)
	{
		buf = readline("fuckingshell# ");
		new_buf = read_and_trim_line(buf);
		if (!new_buf)
			break ;
		if (check_for_pipes(new_buf) == NULL || is_blank(new_buf)
			|| check_for_quotes(new_buf) == NULL)
		{
			free(new_buf);
			continue ;
		}
		if (handle_something(new_buf, custom_env) == 1)
			continue ;
	}
	rl_clear_history();
	ft_free_char_arr(*custom_env);
}

int	main(int ac, char **av, char **env)
{
	char	**custom_env;

	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_handler);
	custom_env = clone_env(env);
	process_input(&custom_env);
	return (0);
}
