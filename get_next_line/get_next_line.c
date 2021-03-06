/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 15:30:16 by amovchan          #+#    #+#             */
/*   Updated: 2017/02/16 12:50:02 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char			*ft_strndup(char *str, size_t len)
{
	char	*src;

	if (!(src = ft_strnew(len)))
		return (NULL);
	src = ft_strncpy(src, str, len);
	return (src);
}

static char			*ft_strnjoin(char const *s1, char const *s2, size_t len)
{
	char *s;

	if (!s1 || !s2 || !(s = ft_strnew(ft_strlen(s1) + len)))
		return (NULL);
	s = ft_strcpy(s, s1);
	s = ft_strncat(s, s2, len);
	return (s);
}

static t_list		*ft_audit_fd(t_list **list, size_t fd)
{
	t_list	*new_list;

	new_list = *list;
	if (new_list)
	{
		while (new_list)
		{
			if (fd == new_list->content_size)
				return (new_list);
			new_list = new_list->next;
		}
	}
	new_list = ft_lstnew("", fd);
	ft_lstadd(list, new_list);
	return (new_list);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*new_list;
	t_list			*begin;
	char			buff[BUFF_SIZE + 1];
	int				res;

	if (fd < 0 || read(fd, buff, 0) < 0 || !line)
		return (-1);
	begin = new_list;
	new_list = ft_audit_fd(&begin, fd);
	while (!ft_strchr(new_list->content, '\n') &&
			(res = read(fd, buff, BUFF_SIZE)))
		new_list->content = ft_strnjoin(new_list->content, buff, res);
	res = 0;
	while (((char *)new_list->content)[res] &&
			((char *)new_list->content)[res] != '\n')
		res++;
	*line = ft_strndup(new_list->content, res);
	if (((char *)new_list->content)[res] == '\n')
		res++;
	new_list->content = ft_strdup(new_list->content + res);
	new_list = begin;
	return (res ? 1 : 0);
}
