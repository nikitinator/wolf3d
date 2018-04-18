/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_point_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:44:55 by snikitin          #+#    #+#             */
/*   Updated: 2018/04/18 14:44:56 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		set_point_xyz(t_point *p, int x, int y, int z)
{
	(*p)[X] = x * XY_COORD_MUL;
	(*p)[Y] = y * XY_COORD_MUL;
	(*p)[Z] = z;
}

static int		set_arr(size_t row, size_t col, t_list *begin_list)
{
	size_t	i;
	size_t	j;
	t_byte	**tokens;

	j = 0;
	if (!(parr->arr = malloc(row * sizeof(t_byte *))))
		return (1);
	while (begin_list)
	{
		tokens = *(char ***)begin_list->content;
		if (!(map[j] = malloc(col * sizeof(char))))
			return (1);
		i = 0;
		while (tokens[i])
		{
			map[j][i] = ft_atoi(tokens[i]);
			free(tokens[i]);
			i++;
		}
		free(tokens);
		begin_list = begin_list->next;
		j++;
	}
	return (0);
}

t_byte		**get_point_arr(size_t col_n, size_t row_n, t_list *begin_list)
{
	t_list	*temp;
	t_byte	**map;

	temp = begin_list;
	if ((map = set_arr(col_n, row_n, begin_list)))
	{
		list_free(temp);
		ft_lstdel(&temp, del_content);
		return (NULL);
	}
	ft_lstdel(&temp, del_content);
	return (map);
}
