/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_str_from_char_arr.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 22:31:00 by nkarpeko            #+#    #+#           */
/*   Updated: 2024/01/30 21:07:56 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_remove_str_from_char_arr_middleware(int arr_len, char ***arr)
{
	if (arr_len == ft_strarrlen(*arr))
		return (1);
	if (!arr_len)
	{
		ft_free_char_arr(*arr);
		*arr = NULL;
		return (1);
	}
	return (0);
}

void	ft_remove_str_from_char_arr(char ***arr, const char *target)
{
	int		idx;
	int		s_idx;
	int		arr_len;
	char	**new_arr;

	idx = -1;
	s_idx = 0;
	arr_len = 0;
	new_arr = NULL;
	while ((*arr)[++idx])
		if (ft_strcmp((*arr)[idx], target))
			arr_len++;
	if (ft_remove_str_from_char_arr_middleware(arr_len, arr))
		return ;
	new_arr = (char **)malloc(sizeof(char *) * (arr_len + 1));
	idx = -1;
	while ((*arr)[++idx])
		if (ft_strcmp((*arr)[idx], target))
			new_arr[s_idx++] = ft_strdup((*arr)[idx]);
	new_arr[s_idx] = NULL;
	ft_free_char_arr(*arr);
	*arr = new_arr;
}
