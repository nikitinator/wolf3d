/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 19:04:05 by snikitin          #+#    #+#             */
/*   Updated: 2018/04/18 20:37:22 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

Uint32	*update_img(t_player plr, Uint32 *img_arr)
{
	(void)plr;
	short	i;
	i = 0;
	ft_bzero(img_arr, sizeof(Uint32) * 4 * SCR_WIDTH * SCR_HEIGHT);
	//ft_memset(img_arr, 125, 3 * SCR_WIDTH * SCR_HEIGHT);
	while (i < SCR_WIDTH)
	{
		i++;
	}
	return(img_arr);
}
