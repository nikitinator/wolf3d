/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:01:34 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/21 18:01:38 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

Uint32	get_pix_txt(SDL_Surface *texture, double x_ratio, double y_ratio)
{
	return (*(Uint32 *)(texture->pixels
				+ (int)((texture->w - 1) * x_ratio) * 3
				+ (int)((texture->h - 1) * y_ratio) * texture->pitch));
}

void	draw_obstacle(t_obst_drw obst_drw, short x, Uint32 *img_arr)
{
	short	from;
	short	to;
	double	y_ratio;
	double	y_ratio_to_add;

	from = (obst_drw.from < 0) ? 0 : obst_drw.from;
	to = (obst_drw.to > SCR_HEIGHT) ? SCR_HEIGHT : obst_drw.to;
	y_ratio = (double)(from - obst_drw.from)
		/ ((double)(obst_drw.to - obst_drw.from));
	y_ratio_to_add = 1.0 / ((double)(obst_drw.to - obst_drw.from));
	while (from < to)
	{
		SET_PIX(x, from, img_arr,
				get_pix_txt(obst_drw.txt, obst_drw.x_ratio, y_ratio));
		y_ratio += y_ratio_to_add;
		from++;
	}
}

void	draw_ceil_floor(t_fc_drw fc_drw)
{
	long		y_floor;
	long		y_ceiling;
	double		dist;
	t_vector_2	floor;

	y_floor = fc_drw.to_txt;
	y_ceiling = fc_drw.from_txt - 1;
	while (y_floor < SCR_HEIGHT || y_ceiling > 0)
	{
		dist = fc_drw.dtpp * PLAYER_HEIGHT / (y_floor - SCR_HEIGHT / 2);
		dist = dist / vec_dot_product(fc_drw.plr.dir, fc_drw.ray_dir);
		floor[X] = fc_drw.ray_dir[X] * dist + fc_drw.plr.pos[X];
		floor[Y] = fc_drw.ray_dir[Y] * dist + fc_drw.plr.pos[Y];
		floor[X] -= (int)floor[X];
		floor[Y] -= (int)floor[Y];
		SET_PIX(fc_drw.x, y_ceiling, fc_drw.img_arr,
				get_pix_txt(fc_drw.textures[WOOD], floor[X], floor[Y]));
		SET_PIX(fc_drw.x, y_floor, fc_drw.img_arr,
				get_pix_txt(fc_drw.textures[GREYSTONE], floor[X], floor[Y]));
		y_ceiling--;
		y_floor++;
	}
}
