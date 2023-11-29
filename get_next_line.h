/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souahidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:19:19 by souahidi          #+#    #+#             */
/*   Updated: 2023/11/29 16:51:02 by souahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

typedef struct s_buff
{
	char	str[BUFFER_SIZE + 1];
	int		pos;
	int		new;
	int		res;
}			t_buff;

int			ft_chrpos(char *s, char c);
void		ft_bzero(void *s, size_t n);
size_t		ft_lenpro(char *s);
char		*get_next_line(int fd);

#endif
