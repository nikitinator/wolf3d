/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:21:36 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/30 16:40:43 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_player(t_player *plr)
{
	plr->fov = FOV;
	plr->dir[X] = 1;
	plr->dir[Y] = 0;
	plr->pos[X] = 1.5;
	plr->pos[Y] = 1.5;
}

int		init_sdl_stuff(t_drawer *drw)
{
	if (!(drw->window = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCR_WIDTH, SCR_HEIGHT,
		SDL_WINDOW_SHOWN)))
		return (1);
	if (!(drw->renderer = SDL_CreateRenderer(drw->window, -1, 0)))
		return (1);
	if (!(drw->texture = SDL_CreateTexture(drw->renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_TARGET,
		SCR_WIDTH, SCR_HEIGHT)))
		return (1);
	return (0);
}

int		open_textures(SDL_Surface **texture)
{
	if (!(texture[BLUESTONE] = SDL_LoadBMP(BLUESTONE_PATH)))
		return (0);
	if (!(texture[COLORSTONE] = SDL_LoadBMP(COLORSTONE_PATH)))
		return (0);
	if (!(texture[EAGLE] = SDL_LoadBMP(EAGLE_PATH)))
		return (0);
	if (!(texture[GREYSTONE] = SDL_LoadBMP(GREYSTONE_PATH)))
		return (0);
	if (!(texture[MOSSY] = SDL_LoadBMP(MOSSY_PATH)))
		return (0);
	if (!(texture[PURPLESTONE] = SDL_LoadBMP(PURPLESTONE_PATH)))
		return (0);
	if (!(texture[REDBRICK] = SDL_LoadBMP(REDBRICK_PATH)))
		return (0);
	if (!(texture[CEILING] = SDL_LoadBMP(CEILING_PATH)))
		return (0);
	return (1);
}

int		main(void)
{
	Uint32			*img_arr;
	SDL_Surface		*textures[TEXTURE_NUM];
	t_drawer		drw;
	t_player		plr;
	t_byte			**map;

	if (!(map = map_read()))
		return (1);
	if (!(open_textures(textures)))
		return (1);
	init_player(&plr);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (1);
	if (!(img_arr = malloc(sizeof(Uint32) * SCR_WIDTH * SCR_HEIGHT)))
		return (1);
	if (init_sdl_stuff(&drw))
		return (1);
	while (!(update_game(&plr, map)))
	{
		img_arr = update_img(plr, img_arr, map, textures);
		update_window(img_arr, drw.texture, drw.renderer);
	}
	SDL_DestroyWindow(drw.window);
	SDL_Quit();
	return (0);
}
