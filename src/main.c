/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:46:53 by snikitin          #+#    #+#             */
/*   Updated: 2018/04/17 19:58:22 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>


int		main(void)
{
	SDL_Window*		window;
	char			*img_arr;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
	t_player		plr;
	t_byte			**map;

	if (!(map = read_map()))
		return (1);  				//normalnyi vixod sdelai
		
	ft_bzero(&plr, sizeof(t_player));
	if(SDL_Init(SDL_INIT_VIDEO) < 0 )
		return (1);
	if (!(img_arr = malloc(sizeof(char) * SCR_WIDTH * SCR_HEIGHT * 4)))
		return (1);

	if (!(window = SDL_CreateWindow( "wolf3d", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCR_WIDTH, SCR_HEIGHT,
		SDL_WINDOW_SHOWN)))
		return (1);
	renderer = SDL_CreateRenderer(window, -1, 0);
	texture = SDL_CreateTexture(renderer, 
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		SCR_WIDTH, SCR_HEIGHT);

	char	color;
	color = 0;

	while (1)
	{
		if (update_game(plr, &color))
			exit(1);
		ft_bzero(img_arr, sizeof(char) * 4 * SCR_WIDTH * SCR_HEIGHT);
		ft_memset(img_arr, color, 3 * SCR_WIDTH * SCR_HEIGHT);
		update_window(img_arr, texture, renderer);
	}

	SDL_DestroyWindow( window );
	SDL_Quit();
	return (0);
}
