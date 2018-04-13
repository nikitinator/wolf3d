/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 14:21:53 by snikitin          #+#    #+#             */
/*   Updated: 2018/04/13 19:32:20 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D
# define WOLF3D

# define SCR_WIDTH 1680//2560
# define SCR_HEIGHT 1050//1440 
# define SCR_BPP 32

# include <SDL.h>
# include <stdio.h>
# include <libft.h>

typedef unsigned short t_ushort;

typedef double	t_vector_2 __attribute__((vector_size(sizeof(double)*2)));
typedef double	t_vector_3 __attribute__((vector_size(sizeof(double)*3)));

typedef struct	t_player
{
	t_ushort	fov;
	t_vector_2	pov;
	t_vector_2	position;
}

#endif
