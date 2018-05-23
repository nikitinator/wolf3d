/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 15:50:05 by snikitin          #+#    #+#             */
/*   Updated: 2018/05/23 15:50:13 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_vector_2	vec_rotate(t_vector_2 vector, double radians)
{
	t_vector_2	result;

	result[X] = vector[X] * cos(radians) -
		vector[Y] * sin(radians);
	result[Y] = vector[X] * sin(radians) +
		vector[Y] * cos(radians);
	return (result);
}
