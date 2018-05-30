/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:41:02 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/30 16:59:53 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		get_col_row(t_list *list, size_t *col, size_t *row)
{
	char	**tokens;

	tokens = *(char ***)list->content;
	while (tokens[*col])
	{
		*col += 1;
	}
	while (list)
	{
		list = list->next;
		*row += 1;
	}
}

static int		validate_col(t_list *list, size_t col)
{
	char	**tokens;
	size_t	i;

	while (list)
	{
		tokens = *(char ***)list->content;
		i = 0;
		while (tokens[i])
			i++;
		if (i != col)
			return (1);
		list = list->next;
	}
	return (0);
}

static t_list	*validate_list(t_list *list, size_t *col)
{
	if (validate_col(list, *col))
	{
		ft_putendl_fd("Invalid map.", 2);
		list_free(list);
		return (NULL);
	}
	return (list);
}

t_list			*map_get_list(int fd, size_t *col, size_t *row)
{
	char	*line;
	char	**split;
	t_list	*list;

	list = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		free(line);
		ft_list_push_back(&list, &split, sizeof(char **));
		if (!split || !split[0] || !split[0][0])
		{
			ft_putendl_fd("Invalid map.", 2);
			list_free(list);
			return (NULL);
		}
	}
	if (!list)
	{
		ft_putendl_fd("Invalid map.", 2);
		return (NULL);
	}
	get_col_row(list, col, row);
	return (validate_list(list, col));
}
