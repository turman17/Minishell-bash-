/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:42:40 by root              #+#    #+#             */
/*   Updated: 2024/01/30 20:16:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_fork_error(char *full_path)
{
	perror("fork");
	free(full_path);
	exit(1);
}

void	execute_child_process(char *full_path, struct s_execcmd *ecmd,
		char **custom_environ)
{
	signal(SIGQUIT, SIG_DFL);
	if (full_path)
	{
		execve(full_path, ecmd->argv, custom_environ);
		free(full_path);
	}
	else
		execve(ecmd->argv[0], ecmd->argv, custom_environ);
	exit(errno);
}

void	process_completion(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		g_exit_code = WEXITSTATUS(*status);
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		g_exit_code = 131;
	}
}

void	execute_command1(struct s_execcmd *ecmd, char **custom_environ)
{
	char	*full_path;
	pid_t	pid;
	int		status;

	full_path = find_command_in_path(ecmd->argv[0], custom_environ);
	if (!full_path && access(ecmd->argv[0], F_OK) != 0)
	{
		g_exit_code = check_error(ecmd->argv[0]);
		free(full_path);
		return ;
	}
	pid = fork();
	if (pid < 0)
		handle_fork_error(full_path);
	else if (pid == 0)
		execute_child_process(full_path, ecmd, custom_environ);
	else
		process_completion(pid, &status);
	free(full_path);
}

int	exec_cmd(struct s_cmd *cmd, char ***custom_environ)
{
	struct s_execcmd	*ecmd;

	ecmd = (struct s_execcmd *)cmd;
	if (ecmd->argv[0] != NULL)
	{
		if (ecmd->argv[0] == 0)
			exit(0);
		if (builtins(ecmd->argv, ecmd->argc, custom_environ))
			return (g_exit_code);
		execute_command1(ecmd, *custom_environ);
	}
	return (g_exit_code);
}
