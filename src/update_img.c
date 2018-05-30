/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 19:04:05 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/29 17:53:42 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_obst_drw	get_obst_drw(double dtpp, t_hitpoint obst, SDL_Surface **textures)
{
	double		txt_size;
	t_obst_drw	obst_drw;

	txt_size = 1.0 / obst.dist * dtpp;
	obst_drw.from = SCR_HEIGHT / 2 - (txt_size / 2);
	obst_drw.to = SCR_HEIGHT / 2 + (txt_size / 2);
	if (obst.type == 3)
	{
		if (obst.card_dir == NORTH)
			obst_drw.txt = textures[MOSSY];
		else if (obst.card_dir == WEST)
			obst_drw.txt = textures[PURPLESTONE];
		else if (obst.card_dir == EAST)
			obst_drw.txt = textures[REDBRICK];
		else if (obst.card_dir == SOUTH)
			obst_drw.txt = textures[BLUESTONE];
	}
	else
		obst_drw.txt = textures[obst.type];
	if (obst.card_dir == NORTH || obst.card_dir == EAST)
		obst_drw.x_ratio = 1 - obst.x_ratio;
	else
		obst_drw.x_ratio = obst.x_ratio;
	return (obst_drw);
}

Uint32		*update_img(t_player plr, Uint32 *img_arr,
		t_byte **map, SDL_Surface **textures)
{
	short		x;
	t_vector_2	ray_dir;
	t_hitpoint	obst;
	t_obst_drw	obst_drw;
	double		to_rotate;

	ray_dir = vec_rotate(plr.dir, RADIAN(-(plr.fov / 2)));
	to_rotate = RADIAN((double)plr.fov / (double)SCR_WIDTH);
	x = 0;
	while (x < SCR_WIDTH)
	{
		obst = cast_ray(plr.pos, ray_dir, map);
		obst.dist = obst.dist * vec_dot_product(plr.dir, ray_dir);
		obst_drw = get_obst_drw(DTPP, obst, textures);
		draw_ceil_floor((t_fc_drw){plr, DTPP, obst_drw.from, obst_drw.to,
				ray_dir, x, textures, img_arr});
		draw_obstacle(obst_drw, x, img_arr);
		ray_dir = vec_rotate(ray_dir, to_rotate);
		x++;
	}
	return (img_arr);
}
