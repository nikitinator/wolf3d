/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:46:53 by snikitin          #+#    #+#             */
/*   Updated: 2018/04/13 18:51:12 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int		main(void)
{
	SDL_Event		e;
	SDL_Window*		window = NULL;
	char			*img_arr;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;

	if(SDL_Init(SDL_INIT_VIDEO) < 0 )
		return (1);
	if (!(window = SDL_CreateWindow( "wolf3d", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCR_WIDTH, SCR_HEIGHT,
			SDL_WINDOW_SHOWN)))
		return (1);
		if (!(img_arr = malloc(sizeof(char) * SCR_WIDTH * SCR_HEIGHT * 4)))
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
			ft_memset(img_arr, color++, 3 * SCR_WIDTH * SCR_HEIGHT);
			SDL_UpdateTexture(texture, NULL, img_arr, 4);
			SDL_RenderCopy(renderer, texture, NULL, NULL);
			SDL_RenderPresent(renderer);
			SDL_RenderClear(renderer);
			if (SDL_PollEvent(&e) != 0 && e.type == SDL_QUIT)
				break ;
		}
	SDL_DestroyWindow( window );
	SDL_Quit();
	return 0;
}
