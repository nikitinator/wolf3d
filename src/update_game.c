/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:57:03 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/23 16:20:17 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move_player_forward(t_player *player, t_byte **map)
{
	t_vector_2	new_position;

	new_position = player->pos;
	new_position[Y] += player->dir[Y] * MOV_COEFF;
	if (!map[(int)new_position[Y]][(int)player->pos[X]])
		player->pos[Y] = new_position[Y];
	new_position[X] += player->dir[X] * MOV_COEFF;
	if (!map[(int)player->pos[Y]][(int)new_position[X]])
		player->pos[X] = new_position[X];
}

void	move_player_backward(t_player *player, t_byte **map)
{
	t_vector_2	new_position;

	new_position = player->pos;
	new_position[Y] -= player->dir[Y] * MOV_COEFF;
	if (!map[(int)new_position[Y]][(int)player->pos[X]])
		player->pos[Y] = new_position[Y];
	new_position[X] -= player->dir[X] * MOV_COEFF;
	if (!map[(int)player->pos[Y]][(int)new_position[X]])
		player->pos[X] = new_position[X];
}

int		update_game(t_player *plr, t_byte **map)
{
	SDL_Event	e;
	const Uint8	*keystates = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym ==
				SDLK_ESCAPE))
			return (1);
		if (keystates[SDL_SCANCODE_UP])
			move_player_forward(plr, map);
		if (keystates[SDL_SCANCODE_DOWN])
			move_player_backward(plr, map);
		if (keystates[SDL_SCANCODE_RIGHT])
			plr->dir = vec_rotate(plr->dir, ROT_COEFF);
		if (keystates[SDL_SCANCODE_LEFT])
			plr->dir = vec_rotate(plr->dir, -ROT_COEFF);
	}
	return (0);
}
