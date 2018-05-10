/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 19:04:05 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/10 18:43:07 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

Uint32	get_pixel_from_texture(int obst_type, double x_ratio, double y_ratio, //prop???
		SDL_Surface **textures)
{
	void	*pixels;
	t_color	clr;

	clr.c_32 = 0;
	int		x = 64 * x_ratio;
	int		y = 64 * y_ratio;
	
	pixels = textures[obst_type]->pixels;
	clr.c_8[RR] = *(unsigned char *)(pixels + (int)x * 3 + (int)y *192  + RR);
	clr.c_8[GG] = *(unsigned char *)(pixels + (int)x * 3 + (int)y *192  + GG);
	clr.c_8[BB] = *(unsigned char *)(pixels + (int)x * 3 + (int)y *192  + BB);

	return (clr.c_32);
}

void		draw_line_textures(short x, t_hitpoint	obstacle, Uint32 *img_arr, SDL_Surface **textures)
{
	Uint32	color;
	short	from;
	short	to;

	double temp;
	temp = 1 / obstacle.distance;
	if (temp > 1)
		temp = 1;
	from = SCR_HEIGHT/2 - ((SCR_HEIGHT/2) * (temp));
	short from_copy = from;
	to = SCR_HEIGHT/2 + ((SCR_HEIGHT/2) * (temp));
	if (obstacle.type)
	{
		while (from < to)
		{
			double	y_prop = (double)(from_copy - from) / (double)(to - from_copy);
			color = get_pixel_from_texture(obstacle.type, obstacle.x_ratio, 
					y_prop, textures);
			SET_PIX(x, from, img_arr, color);
			from++;
		}	
	}
}

void		draw_texture(Uint32 *img_arr, SDL_Surface **textures)
{
	void	*pixels;
	t_color	clr;

			clr.c_32 = 0;
	
	pixels = textures[EAGLE]->pixels;
	for(int y = 0; y < 64; y++)
	{
		for(int x = 0; x < 64; x++)
		{
			clr.c_8[RR] = *(unsigned char *)(pixels + x * 3 + y *192  + RR);
			clr.c_8[GG] = *(unsigned char *)(pixels + x * 3 + y *192  + GG);
			clr.c_8[BB] = *(unsigned char *)(pixels + x * 3 + y *192  + BB);
			SET_PIX(x, y, img_arr, clr.c_32); 
		}
	}
}

Uint32	*update_img(t_player plr, Uint32 *img_arr, t_byte **map, SDL_Surface **textures)
{
	short		i;
	t_vector_2	ray_direction;
	t_hitpoint	obstacle;
	double		to_rotate;

	//ft_bzero(img_arr, sizeof(Uint32) * SCR_WIDTH * SCR_HEIGHT);
	ft_memset(img_arr, 0x00d3d3d3,sizeof(Uint32) * SCR_WIDTH * SCR_HEIGHT);
	i = 0;
	ray_direction = vec_rotate(plr.pov, RADIAN(-(plr.fov / 2)));
	to_rotate = RADIAN((double)plr.fov / (double)SCR_WIDTH);
	while (i < SCR_WIDTH - 1)
	{
		obstacle = cast_ray(plr.position, ray_direction, map);
		obstacle.distance = obstacle.distance *
			((vec_dot_product(plr.pov, ray_direction))/(vec_magnitude(plr.pov)
				* vec_magnitude(ray_direction)));
		draw_line_textures(i, obstacle, img_arr, textures);
		ray_direction = vec_rotate(ray_direction, to_rotate);
		i++;
	}
	draw_texture(img_arr, textures);
	
	return(img_arr);
}
