/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:14:15 by nkarpeko          #+#    #+#             */
/*   Updated: 2024/01/30 21:04:07 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	calc_len_with_vars(char *str, char **custom_environ)
{
	int		idx;
	int		str_len;
	char	*substr;

	idx = -1;
	str_len = 0;
	substr = NULL;
	while (str[++idx])
	{
		if (str[idx] == '$')
		{
			if (str[idx + 1] == '?')
				calc_len_with_vars_middleware(&idx, &str_len, substr);
			else if (str[idx + 1] && ft_isdigit(str[idx + 1]))
			{
				idx++;
				str_len -= 1;
			}
			else if (str[idx + 1] && !ft_isspace(str[idx + 1])
				&& !ft_isdigit(str[idx + 1]))
				return_variable(str, &idx, &str_len, custom_environ);
		}
		str_len++;
	}
	return (str_len);
}

void	process_heredoc_middleware(t_process_heredoc *strc, char *new_buf,
		char *buf, char **custom_environ)
{
	if (buf[strc->idx + 1] == '?')
	{
		strc->idx++;
		strc->substr = ft_itoa(g_exit_code);
		strc->s_idx += ft_strlen(strc->substr);
		ft_strcat(new_buf, strc->substr);
		free(strc->substr);
	}
	else if (buf[strc->idx + 1] && ft_isdigit(buf[strc->idx + 1]))
		strc->idx++;
	else if (buf[strc->idx + 1] && !ft_isspace(buf[strc->idx + 1])
		&& !ft_isdigit(buf[strc->idx + 1]))
	{
		strc->substr = return_variable(buf, &strc->idx, &strc->s_idx,
				custom_environ);
		if (strc->substr)
			ft_strcat(new_buf, strc->substr);
	}
}

char	*process_heredoc(char *buf, char **custom_environ)
{
	char				*new_buf;
	t_process_heredoc	*strc;

	strc = malloc(sizeof(t_process_heredoc));
	new_buf = (char *)malloc(calc_len_with_vars(buf, custom_environ) + 1);
	if (!new_buf || !strc)
		return (NULL);
	strc->s_idx = 0;
	strc->idx = -1;
	new_buf[0] = '\0';
	buf[ft_strlen(buf) - 1] = '\0';
	while (buf[++strc->idx])
	{
		if (buf[strc->idx] == '$')
			process_heredoc_middleware(strc, new_buf, buf, custom_environ);
		else
		{
			new_buf[strc->s_idx++] = buf[strc->idx];
			new_buf[strc->s_idx] = '\0';
		}
	}
	new_buf[strc->s_idx] = 10;
	new_buf[strc->s_idx + 1] = '\0';
	free(strc);
	return (new_buf);
}

int	read_heredoc_input(char *delimiter, int write_fd, char **custom_environ)
{
	char	buffer[1024];
	ssize_t	read_len;
	char	quote_type;
	char	*new_buf;

	process_delimeter(delimiter, &quote_type);
	while (1)
	{
		ft_putstr_fd("> ", STDERR_FILENO);
		read_len = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		buffer[read_len] = '\0';
		if (!quote_type && read_len > 0)
			read_len = calc_len_with_vars(buffer, custom_environ);
		if (read_len <= 0 || ft_strcmp(buffer, delimiter) == 10)
			break ;
		if (!quote_type)
		{
			new_buf = process_heredoc(buffer, custom_environ);
			ft_putstr_fd(new_buf, write_fd);
			free(new_buf);
		}
		else
			ft_putstr_fd(buffer, write_fd);
	}
	return (1);
}

int	double_redirect_left(struct s_redircmd *rcmd, char **custom_environ)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (0);
	}
	if (!read_heredoc_input(rcmd->file, pipefd[1], custom_environ))
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (0);
	}
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipefd[0]);
		g_exit_code = 1;
		return (0);
	}
	close(pipefd[0]);
	return (1);
}
