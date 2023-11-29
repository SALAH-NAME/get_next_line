/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souahidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:32:06 by souahidi          #+#    #+#             */
/*   Updated: 2023/11/29 16:51:55 by souahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_redup(char *s1, char *s2, size_t len)
{
	size_t	len_s1;
	size_t	len_s2;
	int		i;
	char	*dup;

	len_s1 = ft_lenpro(s1);
	len_s2 = ft_lenpro(s2);
	if (len > len_s2)
		len = len_s2;
	dup = (char *)malloc(sizeof(char) * (len_s1 + len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2 && s2[i] && (size_t)i < len)
	{
		dup[len_s1 + i] = s2[i];
		i++;
	}
	dup[len_s1 + len] = '\0';
	return (dup);
}

char	*ft_newbuffer(t_buff *buff, char *str, int fd)
{
	int		n;
	char	*temp;

	temp = str;
	ft_bzero(buff->str, BUFFER_SIZE);
	n = read(fd, buff->str, BUFFER_SIZE);
	if (n <= 0)
		return (str);
	buff->pos = ft_chrpos(buff->str, '\n');
	temp = str;
	if (buff->pos != -1)
	{
		str = ft_redup(temp, buff->str, buff->pos);
		buff->res += buff->pos;
		buff->new ++;
	}
	else
	{
		str = ft_redup(temp, buff->str, BUFFER_SIZE);
		buff->res = 0;
	}
	if (temp)
		free(temp);
	return (str);
}

char	*ft_oldbuffer(t_buff *buff, char *str)
{
	char	*temp;

	buff->pos = ft_chrpos(buff->str + buff->res, '\n');
	temp = str;
	if (buff->pos != -1)
	{
		str = ft_redup(temp, buff->str + buff->res, buff->pos);
		buff->res += buff->pos;
		buff->new ++;
	}
	else
	{
		str = ft_redup(temp, buff->str + buff->res, BUFFER_SIZE);
		buff->res = 0;
	}
	if (temp)
		free(temp);
	return (str);
}

char	*get_next_line(int fd)
{
	static t_buff	buff;
	char			*str;

	str = NULL;
	while (buff.new == 0)
	{
		if (buff.new == 0 && buff.res == 0)
			str = ft_newbuffer(&buff, str, fd);
		if (buff.new == 0 && buff.res != 0)
			str = ft_oldbuffer(&buff, str);
		if (buff.res >= BUFFER_SIZE || (buff.str[buff.res] == '\0'))
		{
			buff.res = 0;
			buff.new ++;
		}
	}
	buff.new = 0;
	return (str);
}

int	main(void)
{
	int		fd1;
	char	*line;
	char	*line2;
	char	*line3;
	char	*line4;
	char	*line5;

	// char src[40] = "THE TEST FOR BUFFER";
	// char *str = ft_redup(NULL, src, strlen(src));
	// int fd0 = open("test", O_CREAT | O_RDWR, 0644);
	// char *fofo = "THE TEST\n\nFOR BUFFER";
	// write(fd0, fofo, strlen(fofo));
	// close(fd0);
	fd1 = open("test", O_RDONLY);
	// printf("bforenew1|");
	line = get_next_line(fd1);
	printf("%s", line);
	if (line)
		free(line);
	// printf("afternew1|");
	line2 = NULL;
	line2 = get_next_line(fd1);
	printf("%s", line2);
	if (line2)
		free(line2);
	// printf("afternew2|");
	line3 = NULL;
	line3 = get_next_line(fd1);
	printf("%s", line3);
	if (line3)
		free(line3);
	// printf("afternew3|");
	line4 = NULL;
	line4 = get_next_line(fd1);
	printf("%s", line4);
	if (line4)
		free(line4);
	// printf("afternew4|");
	line5 = NULL;
	line5 = get_next_line(fd1);
	printf("%s", line5);
	if (line5)
		free(line5);
	close(fd1);
	return (0);
}
