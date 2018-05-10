/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:57:03 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/08 13:32:27 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	print_player(t_player *plr)
{
	printf("fov: %d\n", plr->fov);
	printf("plr->pov[X]: %f\n", plr->pov[X]);
	printf("plr->pov[Y]: %f\n", plr->pov[Y]);
	printf("plr->position[X]: %f\n", plr->position[X]);
	printf("plr->position[Y]: %f\n", plr->position[Y]);
	printf("\n");
}

void	move_player_forward(t_player *player, t_byte **map)
{
	t_vector_2	new_position;

	new_position = player->position;
	new_position[Y] += player->pov[Y] * MOV_COEFF;
	if (!map[(int)new_position[Y]][(int)player->position[X]])
		player->position[Y] = new_position[Y];
	new_position[X] += player->pov[X] * MOV_COEFF;		//potom uprastit, sprosit u senkki
	if (!map[(int)player->position[Y]][(int)new_position[X]])
		player->position[X] = new_position[X];
	//else
	//{
	//	new_position = player->position; //sovet u seni po otnimaniu
	//	new_position[X] += 1 * MOV_COEFF;
	//	new_position[Y] += 1 * MOV_COEFF;
	//	if (!map[(int)new_position[Y]][(int)player->position[X]])
	//		player->position[Y] = new_position[Y];
	//	if (!map[(int)player->position[Y]][(int)new_position[X]])
	//		player->position[X] = new_position[X];
	//}
	print_player(player);
}

void	move_player_backward(t_player *player, t_byte **map)
{
	t_vector_2	new_position;

	new_position = player->position;
	new_position[X] -= player->pov[X] * MOV_COEFF;		//potom uprastit, sprosit u senkki
	new_position[Y] -= player->pov[Y] * MOV_COEFF;
	if (!map[(int)new_position[Y]][(int)new_position[X]])
		player->position = new_position;
	print_player(player);
}

void	rotate_player_ckw(t_player *player)
{
	player->pov = vec_rotate(player->pov, ROT_COEFF);
		print_player(player);
}

void	rotate_player_cckw(t_player *player)
{
	player->pov = vec_rotate(player->pov, -ROT_COEFF);
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
