/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souahidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 09:41:06 by souahidi          #+#    #+#             */
/*   Updated: 2023/11/29 16:51:15 by souahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*us;

	i = 0;
	us = (unsigned char *)s;
	while (us && us[i] && i < n)
		us[i++] = 0;
}

size_t	ft_lenpro(char *s)
{
	size_t	count;

	count = 0;
	while (s && s[count])
		count++;
	return (count);
}

int	ft_chrpos(char *s, char c)
{
	int	pos;

	pos = 0;
	while (s && s[pos])
	{
		if (s[pos] == c)
			return (pos + 1);
		pos++;
	}
	return (-1);
}
