/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:43:34 by nkarpeko          #+#    #+#             */
/*   Updated: 2024/01/30 18:31:37 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strlen(const char *str)
{
	int	idx;

	idx = 0;
	if (!str)
		return (0);
	while (str[idx])
		idx++;
	return (idx);
}
