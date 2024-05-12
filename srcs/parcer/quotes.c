/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:09:23 by nkarpeko          #+#    #+#             */
/*   Updated: 2024/01/30 21:32:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_quotes	*vars_calculate_buffer_size(bool in_quotes)
{
	t_quotes	*vars;

	vars = malloc(sizeof(t_quotes));
	if (!vars)
		return (NULL);
	vars->var_value = NULL;
	vars->i = 0;
	vars->memory_allocated = 0;
	vars->in_double_quotes = 0;
	vars->in_single_quotes = 0;
	vars->in_q = in_quotes;
	return (vars);
}

int	calculate_buf_if2(char *arg, t_quotes *vars, char quote_type, int *size)
{
	if (arg[vars->i] == '$' && ((!vars->in_q && quote_type == '\'')
			|| (vars->in_q && quote_type == '\"'))
		&& calculate_buf_var_code_error(&arg, &vars->i, size))
		return (1);
	return (0);
}

int	calculate_buffer_size(char *arg, char quote_type, bool in_quotes,
		char **envp)
{
	int			size;
	t_quotes	*vars;

	size = 0;
	vars = vars_calculate_buffer_size(in_quotes);
	while (arg[vars->i] != '\0')
	{
		if (calculate_buf_if1(vars, quote_type, arg))
			vars->in_q = !vars->in_q;
		else if (calculate_buf_if2(arg, vars, quote_type, &size))
		{
			vars->var_value = handle_env_var(arg, &vars->i,
					&vars->memory_allocated, envp);
			calculate_buf_var_val(&vars->var_value, &size,
				vars->memory_allocated);
		}
		else
		{
			size++;
			vars->i++;
		}
	}
	free(vars);
	return (size + 1);
}

void	replace_env_vars_set(int *i, int *j, int *in_double_quotes)
{
	(*in_double_quotes) = 0;
	(*i) = 0;
	(*j) = 0;
}

char	*quotes_env_errors_return(char **result, int i)
{
	(*result)[i] = '\0';
	return ((*result));
}
