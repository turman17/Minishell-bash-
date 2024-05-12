/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:26:39 by nkarpeko          #+#    #+#             */
/*   Updated: 2024/01/30 18:30:37 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_strcat(char *s1, const char *s2)
{
	int	idx;
	int	s_idx;

	idx = 0;
	s_idx = -1;
	while (s1[idx])
		idx++;
	while (s2[++s_idx])
		s1[idx++] = s2[s_idx];
	s1[idx] = '\0';
}
