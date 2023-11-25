#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 8


typedef struct s_buff
{
	char	str[BUFFER_SIZE + 1];
	int		pos;
	int		new;
	int		res;
}	t_buff;

void    ft_bzero(void *s, size_t n)
{
    size_t  i;
    unsigned char   *us;
    
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
			return (pos);
		pos++;
	}
	return (-1);
}

char	*ft_redup(char *s1, char *s2, size_t len)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	char    *dup;

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
	while (s2 && s2[i] && i < len)
	{
		dup[len_s1 + i] = s2[i];
		i++;
	}
	dup[len_s1 + len] = '\0';
	return (dup);
}

// char *ft_repos(t_buff *buff, char **str)
// {
//     char    *temp;

//     temp = *str;
//     if (buff->pos != -1)
// 	{
// 	    (buff->pos) += 1;
// 		*str = ft_redup(temp, buff->str, buff->pos);
// 		buff->res = buff->pos;
// 		(buff->new) += 1;
// 	}
// 	else
// 	{
// 		*str = ft_redup(temp, buff->str, BUFFER_SIZE);
// 		buff->res = -1;
// 		buff->new = 0;
// 	}
// 	if (temp)
// 		free(temp);
// 	return (*str);
// }


// char	*ft_getline(int fd)
// {
// 	static t_buff buff;
// 	char	*str;
// 	char	*temp;
// 	int		n;

// 	str = NULL;
// 	while (buff.new == 0)
// 	{
		
// 		if (buff.res != -1 && buff.pos == -1)
// 		{
// 			temp = str;
// 		    buff.pos = ft_chrpos(buff.str + buff.res, '\n');
// 			if (buff.str && buff.str[buff.res] == '\0')
// 				return (NULL);
// 		    ft_repos(&buff, &str);
// 		}
// 		if (buff.new == 0)
// 		{
// 			temp = str;
// 		    ft_bzero(buff.str, BUFFER_SIZE);
// 			n = read(fd, buff.str, BUFFER_SIZE);
// 			if (n <= 0)
// 				return (str);
// 			buff.pos = ft_chrpos(buff.str, '\n');
// 			ft_repos(&buff, &str);
// 		}
// 		if (temp)
// 			free(temp);
// 	}
// 	buff.pos = -1;
// 	buff.new = 0;
// 	return (str);
// }

char    *ft_oldbuffer(t_buff *buff, char *str)
{
    char *temp;
    
    temp = str;
    buff->pos = ft_chrpos(buff->str + buff->res, '\n');
	if (buff->str && buff->str[buff->res] == '\0')
		return (NULL);
    if (buff->pos != -1)
    {
        buff->pos++;
        str = ft_redup(temp, buff->str + buff->res, buff->pos);
        buff->res += buff->pos;
        buff->new++;
    }
    else
    {
        str = ft_redup(temp, buff->str + buff->res, BUFFER_SIZE);
        buff->res = -1;
		buff->new = 0;
    }
    if (temp)
        free(temp);
    return (str);
}

char    *ft_newbuffer(t_buff *buff, char *str, int fd)
{
    int n;
    char *temp;

    temp = str;
    ft_bzero(buff->str, BUFFER_SIZE);
	n = read(fd, buff->str, BUFFER_SIZE);
	if (n <= 0)
		return (NULL);
	buff->pos = ft_chrpos(buff->str, '\n');
	if (buff->pos != -1)
	{
	    buff->pos++;
		str = ft_redup(temp, buff->str, buff->pos);
		buff->res = buff->pos;
		buff->new++;
	}
	else
	{
		str = ft_redup(temp, buff->str, BUFFER_SIZE);
		buff->res = -1;
		buff->new = 0;
	}
	if (temp)
	    free(temp);
	return (str);
}

char	*ft_getline(int fd)
{
	static t_buff buff;
	char	*str;
	char	*temp;

	str = NULL;
	while (buff.new == 0)
	{
		if (buff.res != -1 && buff.pos == -1)
		{
			temp = ft_oldbuffer(&buff, str);
			if (!temp)
			    return (NULL);
			str = temp;
		}
		if (buff.new == 0)
		{
			temp = ft_newbuffer(&buff, str, fd);
			if (!temp)
			    return (str);
			str = temp;
		}
	}
	buff.pos = -1;
	buff.new = 0;
	return (str);
}

// char	*ft_getline(int fd)
// {
// 	static t_buff buff;
// 	char	*str;
// 	char	*temp;
// 	int		n;

// 	str = NULL;
// 	while (buff.new == 0)
// 	{
		
// 		if (buff.res != -1 && buff.pos == -1)
// 		{
// 			temp = str;
// 		    buff.pos = ft_chrpos(buff.str + buff.res, '\n');
// 			if (buff.str && buff.str[buff.res] == '\0')
// 				return (NULL);
// 		    if (buff.pos != -1)
// 		    {
// 		        buff.pos++;
//                 str = ft_redup(temp, buff.str + buff.res, buff.pos);
// 		        buff.res += buff.pos;
// 		        buff.new++;
// 		    }
// 		    else
// 		    {
// 		        str = ft_redup(temp, buff.str + buff.res, BUFFER_SIZE);
// 		        buff.res = -1;
// 				buff.new = 0;
// 		    }
// 		}
// 		if (buff.new == 0)
// 		{
// 			temp = str;
// 		    ft_bzero(buff.str, BUFFER_SIZE);
// 			n = read(fd, buff.str, BUFFER_SIZE);
// 			if (n <= 0)
// 			{
// 				return (str);
// 			}
// 			buff.pos = ft_chrpos(buff.str, '\n');
// 			if (buff.pos != -1)
// 			{
// 			    buff.pos++;
// 				str = ft_redup(temp, buff.str, buff.pos);
// 				buff.res = buff.pos;
// 				buff.new++;
// 			}
// 			else
// 			{
// 				str = ft_redup(temp, buff.str, BUFFER_SIZE);
// 				buff.res = -1;
// 				buff.new = 0;
// 			}
// 		}
// 		if (temp)
// 			free(temp);
// 	}
// 	buff.pos = -1;
// 	buff.new = 0;
// 	return (str);
// }


int main()
{
    // char src[40] = "THE TEST FOR BUFFER";
    // char *str = ft_redup(NULL, src, strlen(src));
    
    // int fd0 = open("test", O_CREAT | O_RDWR, 0644);
    // char *fofo = "THE TEST\n\nFOR BUFFER";
    // write(fd0, fofo, strlen(fofo));
    // close(fd0);
    
    int fd1 = open("test", O_RDONLY);
    
    printf("bforenew1|");
    char *line = ft_getline(fd1);
    printf("%s", line);
    if (line)
        free(line);
    
    printf("afternew1|");
    char *line2 = NULL;
    line2 = ft_getline(fd1);
    printf("%s", line2);
    if (line2)
        free(line2);
        
    printf("afternew2|");
    
    char *line3 = NULL;
    line3 = ft_getline(fd1);
    printf("%s", line3);
    if (line3)
        free(line3);
        
    printf("afternew3|");
    char *line4 = NULL;
    line4 = ft_getline(fd1);
    printf("%s", line4);
    if (line4)
        free(line4);
        
    printf("afternew4|");
    // char *line5 = NULL;
    // line5 = ft_getline(fd1);
    // printf("%s", line5);
    // if (line5)
    //     free(line5);
    
    close(fd1);

	return (0);
}
