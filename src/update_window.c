/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:54:50 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/23 15:45:33 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	update_window(Uint32 *img_arr, SDL_Texture *texture,
		SDL_Renderer *renderer)
{
	SDL_UpdateTexture(texture, NULL, img_arr, sizeof(Uint32) * SCR_WIDTH);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}
