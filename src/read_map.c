/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:25:28 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/21 13:18:02 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

t_byte	**read_map(void)
{
	int		fd;
	//t_byte	**map;
	size_t	col_num;
	size_t	row_num;
	t_list	*map_lines;

	col_num = 0;
	row_num = 0;
	if ((fd = open(MAP_PATH, O_RDONLY)) <= 0)
	{
		ft_putendl_fd("map.txt not found", 2);
		return (NULL);
	}
	if (!(map_lines = get_list(fd, &col_num, &row_num)))
		return (NULL);
	return (get_point_arr(map_lines, col_num, row_num));
}
