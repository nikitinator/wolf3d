/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:42:14 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/23 15:49:49 by snikitin         ###   ########.fr       */
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

double		vec_angle(t_vector_2 a, t_vector_2 b)
{
	return (acos(vec_dot_product(a, b)
				/ (vec_magnitude(a) * vec_magnitude(b))));
}

double		vec_mod_tg(t_vector_2 v)
{
	return (fabs(v[Y] / v[X]));
}

double		vec_mod_ctg(t_vector_2 v)
{
	return (fabs(v[X] / v[Y]));
}
