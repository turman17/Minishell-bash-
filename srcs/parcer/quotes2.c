/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:31:52 by root              #+#    #+#             */
/*   Updated: 2024/01/30 20:49:47 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	calculate_buf_if1(t_quotes *vars, char quote_type, char *arg)
{
	if (arg[(vars->i)] == '\"' && !(vars->in_single_quotes))
		(vars->in_double_quotes) = !(vars->in_double_quotes);
	if (arg[(vars->i)] == '\'' && !(vars->in_double_quotes))
		(vars->in_single_quotes) = !(vars->in_single_quotes);
	if (arg[(vars->i)] == quote_type && (!(vars->in_double_quotes)
			|| quote_type == '\"') && (!(vars->in_single_quotes)
			|| quote_type == '\''))
	{
		(vars->i)++;
		return (1);
	}
	return (0);
}

int	calculate_buf_var_code_error(char **arg, int *i, int *size)
{
	if (ft_strncmp((*arg) + (*i), "$?", 2) == 0)
	{
		(*size) += 3;
		(*i) += 2;
		return (0);
	}
	return (1);
}

char	*handle_env_var(char *arg, int *i, int *memory_allocated, char **envp)
{
	char	var_name[256];
	int		k;
	char	*env_value;

	k = 0;
	(*i)++;
	while (ft_isalnum(arg[*i]) || arg[*i] == '_')
		var_name[k++] = arg[(*i)++];
	var_name[k] = '\0';
	if (var_name[0] == '\0')
	{
		*memory_allocated = 1;
		return (ft_strdup("$"));
	}
	env_value = custom_getenv(var_name, envp, false);
	if (env_value != NULL)
	{
		*memory_allocated = 1;
		return (ft_strdup(env_value));
	}
	else
	{
		*memory_allocated = 1;
		return (NULL);
	}
}

void	calculate_buf_var_val(char **var_value, int *size, int memory_allocated)
{
	if ((*var_value) != NULL)
	{
		(*size) += ft_strlen((*var_value));
		if (memory_allocated)
			free((*var_value));
	}
}

char	*parseexec_arg_process(char *q, char *eq, char **envp)
{
	char	*arg;
	char	*processed_arg;

	arg = mkcopy((q), (eq));
	processed_arg = handle_all_quotes(arg, (envp));
	free(arg);
	return (processed_arg);
}
