/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 17:32:33 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/23 15:40:09 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		validate_values(t_byte **map, size_t row, size_t col)
{
	size_t	x;
	size_t	y;

	y = 0;
	x = 0;
	while (y < row)
	{
		x = 0;
		while (x < col)
		{
			if (map[y][x] >= TEXTURE_NUM)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static int		validate_spawn(t_byte **map)
{
	if (map[1][1])
		return (1);
	return (0);
}

static int		validate_borders(t_byte **map, size_t row, size_t col)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < col)
	{
		y = 0;
		while (y < row)
		{
			if (x == 0 || y == 0 || x == col - 1 || y == row - 1)
				if (!map[y][x])
					return (1);
			y++;
		}
		x++;
	}
	return (0);
}

static void		free_map(t_byte **map, size_t row_num)
{
	size_t y;

	y = 0;
	while (y < row_num)
	{
		free(map[y]);
		y++;
	}
	free(map);
}

t_byte			**validate_map(t_byte **map, size_t row_num, size_t col_num)
{
	if (validate_borders(map, row_num, col_num)
			|| validate_values(map, row_num, col_num)
				|| validate_spawn(map))
	{
		free_map(map, row_num);
		ft_putendl_fd("Invalid map READ.", 2);
		return (NULL);
	}
	return (map);
}
