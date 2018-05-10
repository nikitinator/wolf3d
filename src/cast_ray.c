/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:12:36 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/10 18:37:02 by snikitin         ###   ########.fr       */
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
	return(compare_point);
}

t_vector_2		get_hor_intersec(t_vector_2 pos, t_vector_2 pov, t_vector_2 compare_point,
					double tg_pov)
{
	t_vector_2	result;

	result[X] = compare_point[X];
	if (pov[Y] < 0)
		result[Y] = pos[Y] - tg_pov * fabs(compare_point[X] - pos[X]);
	else
		result[Y] = pos[Y] + tg_pov * fabs(compare_point[X] - pos[X]);
	return (result);
}

t_vector_2		get_ver_intersec(t_vector_2 pos, t_vector_2 pov, t_vector_2 compare_point,
					double ctg_pov)
{
	t_vector_2	result;
	
	result[Y] = compare_point[Y];
	if (pov[X] < 0)
		result[X] = pos[X] - ctg_pov * fabs(compare_point[Y] - pos[Y]);
	else
		result[X] = pos[X] + ctg_pov * fabs(compare_point[Y] - pos[Y]);
	return (result);
}

t_byte		get_obstacle_type(t_byte **map, t_vector_2 ray_pos, t_vector_2 ray_dir)
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

t_hitpoint	cast_ray(t_vector_2 pos, t_vector_2 direction, t_byte **map) //CHANGE "pos" name
{
	t_hitpoint	obstacle;
	t_vector_2	ray_pos;
	t_vector_2	compare_point;
	double		tg_pov;
	double		ctg_pov;

	obstacle.type = 0;
	ray_pos = pos;
	tg_pov = vec_mod_tg(direction);
	ctg_pov = vec_mod_ctg(direction);
	while (!obstacle.type)
	{
		//printf("ray_pos[X]: %f\n", ray_pos[X]/64);  
		compare_point = get_compare_point(ray_pos, direction);
		if (tg_pov > vec_mod_tg(compare_point - ray_pos))
			ray_pos = get_ver_intersec(ray_pos, direction, compare_point, ctg_pov);
		else
			ray_pos = get_hor_intersec(ray_pos, direction, compare_point, tg_pov);
		obstacle.type = get_obstacle_type(map, ray_pos, direction);
	}
	obstacle.x_ratio = (ray_pos[X] - (int)ray_pos[X]) 
		? ray_pos[Y] - (int)ray_pos[Y] 
		: ray_pos[X] - (int)ray_pos[X];
	obstacle.distance = vec_magnitude(ray_pos - pos);

	//printf("direction[X]: %f\n", direction[X]);  
	//printf("direction[Y]: %f\n", direction[Y]);  
	//printf("ray_pos[X]: %f\n", ray_pos[X]);  
	//printf("ray_pos[Y]: %f\n", ray_pos[Y]);  
	//printf("obstacle.distance: %f\n", obstacle.distance);  
	//printf("\n");
	return (obstacle);
}
