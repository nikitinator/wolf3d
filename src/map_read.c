/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:25:28 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/30 16:41:42 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static t_byte	**create_arr(t_list *begin_list, size_t row, size_t col)
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

t_byte			**map_read(void)
{
	int		fd;
	t_byte	**map;
	size_t	row_num;
	size_t	col_num;
	t_list	*map_list;

	row_num = 0;
	col_num = 0;
	if ((fd = open(MAP_PATH, O_RDONLY)) <= 0)
	{
		ft_putendl_fd("map.txt not found", 2);
		return (NULL);
	}
	if (!(map_list = map_get_list(fd, &col_num, &row_num)))
		return (NULL);
	map = create_arr(map_list, row_num, col_num);
	ft_lstdel(&map_list, del_content);
	return (map_validate(map, row_num, col_num));
}
