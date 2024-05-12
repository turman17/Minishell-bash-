/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 20:01:52 by nkarpeko          #+#    #+#             */
/*   Updated: 2024/01/31 20:18:47 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_quotes	*quotes_env_errors_set(int *s_idx)
{
	t_quotes	*vars;

	vars = malloc(sizeof(t_quotes));
	if (!vars)
		return (NULL);
	vars->in_double_quotes = 0;
	vars->in_single_quotes = 0;
	vars->i = 0;
	(*s_idx) = 0;
	return (vars);
}

void	quotes_env_errors_middleware(t_quotes *vars, t_quotes3 *vars2,
		char *arg, char **envp)
{
	if (quotes_env_errors_exit_code(&vars2->ch_va1, arg, &vars->i,
			&vars2->var_val))
		vars2->var_val = handle_env_var(arg, &vars->i, &vars2->ch_va2, envp);
	if (re_e_v_ch_em(vars2->var_val, &vars2->result, &vars2->s_idx)
		&& (vars2->ch_va1 || vars2->ch_va2))
		free(vars2->var_val);
}

char	*quotes_env_errors(char *arg, char q_ty, int in_q, char **envp)
{
	t_quotes	*vars;
	t_quotes3	*vars2;

	vars2 = malloc(sizeof(t_quotes3));
	vars2->result = (char *)malloc(calculate_buffer_size(arg, q_ty, false, envp)
			+ 1);
	if (!vars2->result || !vars2)
		return (NULL);
	vars = quotes_env_errors_set(&vars2->s_idx);
	while (arg[vars->i] != '\0')
	{
		if (calculate_buf_if1(vars, q_ty, arg))
			in_q = !in_q;
		else if (arg[vars->i] == '$' && ((!in_q && q_ty == '\'') || (in_q
					&& q_ty == '\"')))
			quotes_env_errors_middleware(vars, vars2, arg, envp);
		else
			vars2->result[vars2->s_idx++] = arg[vars->i++];
	}
	free(vars);
	return (quotes_env_errors_return(&vars2->result, vars2->s_idx));
}

char	*process_quotes(char *arg, char quote1, char quote2, char **envp)
{
	char	*processed_arg;
	char	*temp;

	processed_arg = quotes_env_errors(arg, quote1, false, envp);
	temp = processed_arg;
	processed_arg = quotes_env_errors(processed_arg, quote2, false, envp);
	if (temp != arg && temp != processed_arg)
		free(temp);
	return (processed_arg);
}

char	*handle_all_quotes(char *arg, char **envp)
{
	char	*single_quote_ptr;
	char	*double_quote_ptr;

	single_quote_ptr = ft_strchr(arg, '\'');
	double_quote_ptr = ft_strchr(arg, '\"');
	if (double_quote_ptr == NULL || (single_quote_ptr != NULL
			&& single_quote_ptr < double_quote_ptr))
		return (process_quotes(arg, '\"', '\'', envp));
	else
		return (process_quotes(arg, '\'', '\"', envp));
}
