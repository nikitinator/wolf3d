/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 14:21:53 by snikitin          #+#    #+#             */
/*   Updated: 2018/04/17 20:03:01 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D
# define WOLF3D

# define MOV_COEFF 0.5

# define SCR_WIDTH 1680//2560
# define SCR_HEIGHT 1050//1440 
# define SCR_BPP 32

# include <SDL.h>
# include <stdio.h>//
# include <stdlib.h>
# include <libft.h>

typedef unsigned char t_byte;
typedef unsigned short t_ushort;

typedef double	t_vector_2 __attribute__((vector_size(sizeof(double)*2)));
typedef double	t_vector_3 __attribute__((vector_size(sizeof(double)*3)));

typedef struct	s_player
{
	t_ushort	fov;
	t_vector_2	pov;
	t_vector_2	position;
}				t_player;

typedef struct	s_map
{
	size_t		col;
	size_t		row;
	t_vector_2	**arr;
}				t_map;


/*
** 		Init and read everything.
*/
t_byte	**read_map(void);
t_list	*get_list(int fd, size_t *col_n, size_t *row_n);
void	get_point_arr(char **map, size_t col_n, size_t row_n, t_list *begin_list);

void	update_game(t_player plr, char *color);
void	update_window(char	*img_arr, SDL_Texture *texture, SDL_Renderer *renderer);


#endif
