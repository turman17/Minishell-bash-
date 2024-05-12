/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fgets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:49:41 by nkarpeko          #+#    #+#             */
/*   Updated: 2024/01/30 18:31:17 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdbool.h>

char	*ft_fgets(char *str, int n, FILE *fp)
{
	int		c;
	char	*s;
	bool	did_read;

	did_read = false;
	s = str;
	while (--n > 0)
	{
		c = fgetc(fp);
		if (c == EOF)
			break ;
		did_read = true;
		*s = c;
		s++;
		if (c == '\n')
			break ;
	}
	*s = '\0';
	if (did_read)
		return (str);
	else
		return (NULL);
}
