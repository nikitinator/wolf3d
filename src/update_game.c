/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:57:03 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/18 12:49:43 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	print_player(t_player *plr)
{
	printf("fov: %d\n", plr->fov);
	printf("plr->dir[X]: %f\n", plr->dir[X]);
	printf("plr->dir[Y]: %f\n", plr->dir[Y]);
	printf("plr->pos[X]: %f\n", plr->pos[X]);
	printf("plr->pos[Y]: %f\n", plr->pos[Y]);
	printf("magnitude plr->dir %f\n", vec_magnitude(plr->dir));
	printf("\n");
}

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
	print_player(player);
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
	print_player(player);
}

void	rotate_player_ckw(t_player *player)
{
	player->dir = vec_rotate(player->dir, ROT_COEFF);
		print_player(player);
}

void	rotate_player_cckw(t_player *player)
{
	player->dir = vec_rotate(player->dir, -ROT_COEFF);
		print_player(player);
}

int		update_game(t_player *plr, t_byte **map) //maybe only player
{
	SDL_Event		e;
	
	const Uint8 *keystates = SDL_GetKeyboardState(NULL); // rewrite it maybe =0
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym ==
				SDLK_ESCAPE))
			return (1);	
		if(keystates[SDL_SCANCODE_UP])
			move_player_forward(plr, map);
        if(keystates[SDL_SCANCODE_DOWN])
			move_player_backward(plr, map);
		if(keystates[SDL_SCANCODE_RIGHT])
			rotate_player_ckw(plr);
		if(keystates[SDL_SCANCODE_LEFT])
			rotate_player_cckw(plr);
	}
	return (0);
}
