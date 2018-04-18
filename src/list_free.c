/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 16:20:46 by snikitin          #+#    #+#             */
/*   Updated: 2018/04/18 18:03:42 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	del_content(void *content, size_t content_size)
{
	ft_bzero(content, content_size);
	free(content);
}

void		list_free(t_list *list)
{
	char	**tokens;
	t_list	*list_copy;
	size_t	i;

	list_copy = list;
	while (list)
	{
		tokens = *(char ***)list->content;
		i = 0;
		while (tokens[i])
		{
			free(tokens[i]);
			i++;
		}
		free(tokens);
		list = list->next;
	}
	if (list_copy)
		ft_lstdel(&list_copy, del_content);
}

void		*del_return(t_list *list)
{
	ft_putendl_fd("Invalid map", 2);
	list_free(list);
	return (NULL);
}
