/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_point_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:44:55 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/21 13:16:50 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_byte		**create_arr(t_list *begin_list, size_t row, size_t col)
{
	size_t	i;
	size_t	j;
	char	**tokens;
 	t_byte	**map;

	j = 0;
	if (!(map = malloc(row * sizeof(t_byte *))))
		return (NULL);
	while (begin_list)
	{
		tokens = *(char ***)begin_list->content;
		if (!(map[j] = malloc(col * sizeof(t_byte))))
			return (NULL);
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
	return (map);
}

t_byte		**get_point_arr(t_list *begin_list, size_t col_n, size_t row_n)
{
	t_list	*temp;
	t_byte	**map;

	temp = begin_list;
	map = create_arr(begin_list, col_n, row_n);
	ft_lstdel(&temp, del_content);
	return (map);
}
