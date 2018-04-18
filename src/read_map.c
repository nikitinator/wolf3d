/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:25:28 by snikitin          #+#    #+#             */
/*   Updated: 2018/04/18 14:57:47 by snikitin         ###   ########.fr       */
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
	if (!(fd = open(MAP_LOCATION, O_RDONLY)) <= 0)
		return (NULL);
	if (!(map_lines = get_list(fd, &col_num, &row_num)))
		return (NULL);
	return (get_point_arr(col_num, row_num, map_lines));
}
