/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:09:11 by nkarpeko          #+#    #+#             */
/*   Updated: 2024/01/30 20:47:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*create_full_path(char *dir, char *command)
{
	char	*temp_path;
	char	*full_path;

	temp_path = ft_strjoin(dir, "/");
	if (!temp_path)
		return (NULL);
	full_path = ft_strjoin(temp_path, command);
	free(temp_path);
	return (full_path);
}

char	*search_command_in_dirs(char *temp, char *command)
{
	char		*dir;
	struct stat	st;
	char		*full_path;

	dir = ft_strtok(temp, ":");
	while (dir)
	{
		full_path = create_full_path(dir, command);
		if (!full_path)
			return (NULL);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
			return (full_path);
		free(full_path);
		dir = ft_strtok(NULL, ":");
	}
	return (NULL);
}

char	*find_command_in_path(char *command, char **custom_environ)
{
	char		*path;
	char		*temp;
	char		*result;
	struct stat	st;

	if (command[0] == '/' || ft_strchr(command, '/'))
	{
		if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
			return (ft_strdup(command));
		return (NULL);
	}
	path = custom_getenv("PATH", custom_environ, 0);
	if (!path)
		return (NULL);
	temp = ft_strdup(path);
	if (!temp)
		return (NULL);
	result = search_command_in_dirs(temp, command);
	free(temp);
	return (result);
}

bool	process_quotes1(const char *buffer, size_t len)
{
	size_t	index;
	bool	quote_open;
	char	quote_type;

	index = 0;
	quote_open = false;
	quote_type = 0;
	while (index < len)
	{
		if (buffer[index] == '\"' || buffer[index] == '\'')
		{
			if (!quote_open || buffer[index] == quote_type)
			{
				quote_open = !quote_open;
				if (quote_open)
					quote_type = buffer[index];
				else
					quote_type = 0;
			}
		}
		index++;
	}
	return (quote_open);
}

char	*check_for_quotes(char *buffer)
{
	size_t	len;

	len = ft_strlen(buffer);
	if (process_quotes1(buffer, len))
	{
		printf("Missing closing quote\n");
		return (NULL);
	}
	return (buffer);
}
