/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:54:15 by snikitin          #+#    #+#             */
/*   Updated: 2018/04/18 15:30:10 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		del_content(void *content, size_t content_size)
{
	ft_bzero(content, content_size);
	free(content);
}

void		list_free(t_list *list)
{
	char	**tokens;
	t_list	*list_copy;
	int		i;

	list_copy = list;
	while (list)
	{
		tokens = *(char ***)list->content;
		i = 0;
		while (tokens[i])
		{
			free(tokens[i]);
			i++;
		}
		free(tokens);
		list = list->next;
	}
	if (list_copy)
		ft_lstdel(&list_copy, del_content);
}

void		*del_return(t_list *list)
{
	ft_putendl_fd("Invalid map", 2);
	list_free(list);
	return (NULL);
}

t_list		*get_list(int fd, size_t *column_num, size_t *row_num)
{
	char	*line;
	char	**split;
	t_list	*begin_list;

	begin_list = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (*line)
		{
			if (*column_num == 0)
				*column_num = ft_cntwrd(line);
			else if (ft_cntwrd(line) != *column_num)
			{
				free(line);
				return (del_return(begin_list));
			}
			split = ft_strsplit(line, ' ');// protect?
			ft_list_push_back(&begin_list, &split, sizeof(char ***));
		}
		*row_num += 1;
		free(line);
	}
	return (validate_list(begin_list, *column_num, *row_num));
}
