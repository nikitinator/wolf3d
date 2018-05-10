/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:42:14 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/04 15:39:15 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double		vec_dot_product(t_vector_2 a, t_vector_2 b)
{
	return (a[X] * b[X] + a[Y] * b[Y]);
}	

double		vec_magnitude(t_vector_2 a)
{
	return (sqrt(SQR(a[X]) + SQR(a[Y])));
}

double		vec_angle(t_vector_2 a, t_vector_2 b)//ensure return type
{
	return(acos(vec_dot_product(a, b)/(vec_magnitude(a) * vec_magnitude(b))));
}

double		vec_mod_tg(t_vector_2 v)
{
	//if (v[X] == 0.0)
	//	return (0.0);
	//else
		return(fabs(v[Y] / v[X]));
}

double		vec_mod_ctg(t_vector_2 v)
{
	//if (v[Y] == 0.0)
	//	return (0.0);
	//else
		return(fabs(v[X] / v[Y]));
}

t_vector_2	vec_rotate(t_vector_2 vector, double radians)
{
	t_vector_2	result;

	result[X] = vector[X] * cos(radians) - 
		vector[Y] * sin(radians); //static hranit
	result[Y] = vector[X] * sin(radians) +
		vector[Y] * cos(radians);
	return (result);
}
