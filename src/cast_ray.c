/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:12:36 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/18 12:53:53 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_vector_2	get_compare_point(t_vector_2 pos, t_vector_2 dir)
{
	t_vector_2 compare_point;

	compare_point[X] = (int)pos[X];
	compare_point[Y] = (int)pos[Y];
	if (dir[Y] < 0 && pos[Y] == (int)pos[Y])
		compare_point[Y] -= 1;
	if (dir[X] < 0 && pos[X] == (int)pos[X])
		compare_point[X] -= 1;
	if (dir[Y] > 0)
		compare_point[Y] += 1;
	if (dir[X] > 0)
		compare_point[X] += 1;
	return (compare_point);
}

static t_byte		get_obstacle_type(t_byte **map,
		t_vector_2 ray_pos, t_vector_2 ray_dir)
{
	t_ushort	x;
	t_ushort	y;

	y = ray_pos[Y];
	x = ray_pos[X];
	if (ray_dir[Y] < 0 && ray_pos[Y] == (int)ray_pos[Y])
		y -= 1;
	if (ray_dir[X] < 0 && ray_pos[X] == (int)ray_pos[X])
		x -= 1;
	return (map[y][x]);
}

static t_vector_2	get_intersection(t_vector_2 pos, t_vector_2 dir,
		double tg_dir, double ctg_dir)
{
	t_vector_2	intersec;
	t_vector_2	compare_point;

	compare_point = get_compare_point(pos, dir);
	if (tg_dir > vec_mod_tg(compare_point - pos))
	{
		intersec[Y] = compare_point[Y];
		if (dir[X] < 0)
			intersec[X] = pos[X] - ctg_dir * fabs(compare_point[Y] - pos[Y]);
		else
			intersec[X] = pos[X] + ctg_dir * fabs(compare_point[Y] - pos[Y]);
	}
	else
	{
		intersec[X] = compare_point[X];
		if (dir[Y] < 0)
			intersec[Y] = pos[Y] - tg_dir * fabs(compare_point[X] - pos[X]);
		else
			intersec[Y] = pos[Y] + tg_dir * fabs(compare_point[X] - pos[X]);
	}
	return (intersec);
}

static t_byte		get_cardinal_direction(t_vector_2 pos, t_vector_2 dir)
{
	if (pos[X] - (int)pos[X])
	{
		if (dir[Y] > 0)
			return (NORTH);
		else
			return (SOUTH);
	}
	else
	{
		if (dir[X] > 0)
			return (WEST);
		else
			return (EAST);
	}
}

t_hitpoint			cast_ray(t_vector_2 plr_pos, t_vector_2 dir, t_byte **map)
{
	t_hitpoint	obstacle;
	t_vector_2	ray_pos;
	double		tg_dir;
	double		ctg_dir;

	obstacle.type = 0;
	ray_pos = plr_pos;
	tg_dir = vec_mod_tg(dir);
	ctg_dir = vec_mod_ctg(dir);
	while (!obstacle.type)
	{
		ray_pos = get_intersection(ray_pos, dir, tg_dir, ctg_dir);
		obstacle.type = get_obstacle_type(map, ray_pos, dir);
	}
	obstacle.x_ratio = (ray_pos[X] - (int)ray_pos[X])
		? ray_pos[X] - (int)ray_pos[X]
		: ray_pos[Y] - (int)ray_pos[Y];
	obstacle.dist = vec_magnitude(ray_pos - plr_pos);
	obstacle.card_dir = get_cardinal_direction(ray_pos, dir);
	return (obstacle);
}
