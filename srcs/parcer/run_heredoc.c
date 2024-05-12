/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:09:21 by nkarpeko          #+#    #+#             */
/*   Updated: 2024/01/30 20:49:51 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count_quotes(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] == '\'' || str[i] == '\"')
			count++;
	return (count);
}

void	process_delimeter_loop(char *delimiter, char *quote_type,
		char *to_remove)
{
	int	idx;

	idx = -1;
	while (delimiter[++idx])
	{
		if (delimiter[idx] == '\'' || delimiter[idx] == '\"')
		{
			if (!(*quote_type))
				*quote_type = delimiter[idx];
			else if (*quote_type == delimiter[idx])
			{
				to_remove[0] = *quote_type;
				*quote_type = -1;
			}
		}
	}
}

void	process_delimeter(char *delimiter, char *quote_type)
{
	char	to_remove[2];
	char	*new_delimeter;

	*quote_type = 0;
	to_remove[0] = '\0';
	to_remove[1] = '\0';
	new_delimeter = NULL;
	if (!ft_count_quotes(delimiter) || ft_strlen(delimiter) == 0)
		return ;
	process_delimeter_loop(delimiter, quote_type, to_remove);
	if (*quote_type > 0)
	{
		ft_printf("gimme last quote bruh🤡\n");
		return ;
	}
	new_delimeter = ft_str_remove_chars(delimiter, to_remove);
	ft_strlcpy(delimiter, new_delimeter, ft_strlen(new_delimeter) + 1);
	free(new_delimeter);
}

char	*return_variable(char *buf, int *idx, int *new_buf_idx,
		char **custom_environ)
{
	int		s_idx;
	char	*substr;
	char	*getenv_result;

	s_idx = 1;
	while (buf[s_idx + *idx] && !ft_isspace(buf[s_idx + *idx]))
		s_idx++;
	substr = ft_substr(buf, *idx + 1, s_idx - 1);
	getenv_result = custom_getenv(substr, custom_environ, false);
	free(substr);
	*idx += s_idx - 1;
	if (getenv_result)
	{
		*new_buf_idx += ft_strlen(getenv_result);
		return (getenv_result);
	}
	else
		return (NULL);
}

void	calc_len_with_vars_middleware(int *idx, int *str_len, char *substr)
{
	*idx += 1;
	substr = ft_itoa(g_exit_code);
	str_len += ft_strlen(substr) + 1;
	free(substr);
}
