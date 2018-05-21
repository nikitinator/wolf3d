/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 14:21:53 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/21 19:30:53 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef WOLF3D
# define WOLF3D
// check all defines do yo need em

# define WALL_HEIGHT 1.0//

# define MOV_COEFF 0.5 
# define ROT_COEFF M_PI/180*5 
# define FOV 60
# define TAN30 0.57735026919//

# define SCR_WIDTH 1680
# define SCR_HEIGHT 1050
# define SCR_BPP 32

# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3

# define X 0
# define Y 1

# define RR 0
# define GG 1
# define BB 2

# define PLAYER_HEIGHT 0.5

# define TEXTURE_NUM 8
# define TEXTURE_HEIGHT 64
# define TEXTURE_WIDTH 64

# define BLUESTONE 0
# define COLORSTONE 1
# define EAGLE 2
# define GREYSTONE 3
# define MOSSY 4
# define PURPLESTONE 5
# define REDBRICK 6
# define WOOD 7

# define BLUESTONE_PATH "./res/pics/bluestone.bmp"
# define COLORSTONE_PATH "./res/pics/colorstone.bmp"
# define EAGLE_PATH "./res/pics/eagle.bmp"
# define GREYSTONE_PATH "./res/pics/greystone.bmp"
# define MOSSY_PATH "./res/pics/mossy.bmp"
# define PURPLESTONE_PATH "./res/pics/purplestone.bmp"
# define REDBRICK_PATH "./res/pics/redbrick.bmp"
# define WOOD_PATH "./res/pics/ceiling.bmp"

# define MAP_PATH "./res/map.txt"

# define GET_PIX(x, y, i) *(Uint32 *)(i + x + y * 64)

# define TRUECHK(x) if (x) return (1);//

#define	GET_PIX_TXT(x_ratio, y_ratio, texture)\
			(*(Uint32 *)(texture->pixels \
			+(int)((texture->w-1)*x_ratio)*3\
			+(int)((texture->h-1)*y_ratio)*texture->pitch))

# define SET_PIX(x, y, i, c) i[x + y * SCR_WIDTH] = c
# define RADIAN(angle) (M_PI/180.0*(angle))
# define SQR(n) ((n) * (n))

# include <SDL.h>
# include <stdio.h>//
# include <stdlib.h>
# include <libft.h>
# include <fcntl.h>

typedef unsigned char t_byte;
typedef unsigned short t_ushort;

typedef double	t_vector_2 __attribute__((vector_size(sizeof(double)*2)));
typedef double	t_vector_3 __attribute__((vector_size(sizeof(double)*3)));

typedef union		u_color
{
	unsigned int	c_32;
	unsigned char	c_8[3];
}					t_color;

typedef struct	s_obst_drw
{
	long		from;
	long		to;
	double		x_ratio;
	SDL_Surface	*txt;
}				t_obst_drw;

typedef struct	s_player
{
	t_ushort	fov;
	t_vector_2	dir;
	t_vector_2	pos;
}				t_player;


typedef struct	s_fc_drw
{
	t_player	plr;
	double		dtpp;
	long		from_txt;
	long		to_txt;
	t_vector_2	ray_dir;
	short		x;
	SDL_Surface **textures;
	Uint32		*img_arr;
}				t_fc_drw;

typedef struct	s_hitpoint
{
	t_byte		type;
	double		dist;
	double		x_ratio;
	t_byte		card_dir;
}				t_hitpoint;

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
t_byte	**get_point_arr(t_list *begin_list, size_t col_n, size_t row_n);
void	list_free(t_list *list);
void	del_content(void *content, size_t content_size);
void	*del_return(t_list *list);

double		vec_dot_product(t_vector_2 a, t_vector_2 b);
double		vec_magnitude(t_vector_2 v);
double		vec_angle(t_vector_2 a, t_vector_2 b);
double		vec_mod_tg(t_vector_2 v);
double		vec_mod_ctg(t_vector_2 v);

void		draw_obstacle(t_obst_drw obst_drw, short x, Uint32 *img_arr);
void		draw_ceil_floor(t_fc_drw fc_drw);

t_vector_2	vec_rotate(t_vector_2 vector, double radians);

t_hitpoint	cast_ray(t_vector_2 position, t_vector_2 dir, t_byte **map);

int		update_game(t_player *plr, t_byte **map);
Uint32	*update_img(t_player plr, Uint32 *img_arr, t_byte **map, SDL_Surface **textures);
void	update_window(Uint32 *img_arr, SDL_Texture *texture, SDL_Renderer *renderer);


#endif

