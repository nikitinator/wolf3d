/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:21:36 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/21 18:57:32 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_player(t_player *plr)//mind the position
{
	plr->fov = FOV;

	plr->dir[X]= 1;
	plr->dir[Y]= 0;
	plr->pos[X]= 3;
	plr->pos[Y]= 3;
}

int		init_sdl_stuff(SDL_Window **window, SDL_Texture **texture, SDL_Renderer **renderer)
{
	if (!(*window = SDL_CreateWindow( "wolf3d", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCR_WIDTH, SCR_HEIGHT,
		SDL_WINDOW_SHOWN)))
		return (1);
	if (!(*renderer = SDL_CreateRenderer(*window, -1, 0)))
		return (1);
	if (!(*texture = SDL_CreateTexture(*renderer, 
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
	if (!(texture[WOOD] = SDL_LoadBMP(WOOD_PATH)))
		return (0);
	return (1);
}

int		main(void)
{
	Uint32			*img_arr;
	SDL_Surface		*textures[TEXTURE_NUM];
	SDL_Window		*window;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
	t_player		plr;
	t_byte			**map;

	if (!(map = read_map()))
		return (1);  				//normalnyi vixod sdelai
	if (!(open_textures(textures)))
		return (1);
	init_player(&plr);	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		return (1);
	if (!(img_arr = malloc(sizeof(Uint32) * SCR_WIDTH * SCR_HEIGHT)))
		return (1);
	if (init_sdl_stuff(&window, &texture, &renderer))
		return (1);

	while (1)//while update_game
	{
		if (update_game(&plr, map))
			exit(1);
		img_arr = update_img(plr, img_arr, map, textures);// V WHILE
		update_window(img_arr, texture, renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
 }
