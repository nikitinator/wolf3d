/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:57:03 by snikitin          #+#    #+#             */
/*   Updated: 2018/04/17 17:57:42 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		update_game(t_player plr, char *color)
{
	SDL_Event		e;
	
	const Uint8 *keystates = SDL_GetKeyboardState(NULL); // rewrite it maybe =0

	(void)plr;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym ==
				SDLK_ESCAPE))
			return (1);	
		if(keystates[SDL_SCANCODE_UP])
			*color = *color + 25;
        if(keystates[SDL_SCANCODE_DOWN])
			*color = *color - 25;
	}
	return (0);
}
