/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:27:59 by root              #+#    #+#             */
/*   Updated: 2024/01/30 20:49:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	replace_env_vars_exit_code(int *is_itoa, char *arg, int *i,
		char **var_value)
{
	(*is_itoa) = 0;
	if (ft_strncmp(arg + (*i), "$?", 2) == 0)
	{
		(*var_value) = ft_itoa(g_exit_code);
		(*i) += 2;
		(*is_itoa) = 1;
		return (0);
	}
	return (1);
}

int	re_e_v_ch_em(char *var_value, char **result, int *j)
{
	if (var_value != NULL)
	{
		ft_strncpy((*result) + (*j), var_value, ft_strlen(var_value));
		(*j) += ft_strlen(var_value);
		return (1);
	}
	return (0);
}

char	*replace_env_vars_return(char **result, int i)
{
	(*result)[i] = '\0';
	return ((*result));
}

int	quotes_env_errors_exit_code(int *is_itoa, char *arg, int *i,
		char **var_value)
{
	(*is_itoa) = 0;
	if (ft_strncmp(arg + (*i), "$?", 2) == 0)
	{
		(*var_value) = ft_itoa(g_exit_code);
		(*i) += 2;
		(*is_itoa) = 1;
		return (0);
	}
	return (1);
}
