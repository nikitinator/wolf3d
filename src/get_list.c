/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snikitin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:54:15 by snikitin          #+#    #+#             */
/*   Updated: 2018/04/18 18:27:32 by snikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

t_list		*validate_list(t_list *list, size_t col, size_t num)
{
	char	**tokens;
	t_list	*list_copy;
	size_t	i;

	list_copy = list;
	if (col <= 2 || num <= 2)
		return (del_return(list_copy));
	while (list)
	{
		tokens = *(char ***)list->content;
		i = 0;
		while (tokens[i])
		{
			if (!is_number(tokens[i]))
			{
				ft_putendl_fd("Invalid map1", 2);
				list_free(list_copy);
				return (NULL);
				//return (del_return(list_copy));
			}
			i++;
		}
		list = list->next;
	}
	return (list_copy);
}

t_list		*get_list(int fd, size_t *column_num, size_t *row_num)
{
	char	*line;
	char	**split;
	t_list	*begin_list;

	begin_list = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (*line)
		{
			if (*column_num == 0)
				*column_num = ft_cntwrd(line);
			else if (ft_cntwrd(line) != *column_num)
			{
				free(line);
				return (del_return(begin_list));
			}
			split = ft_strsplit(line, ' ');// protect?
			ft_list_push_back(&begin_list, &split, sizeof(char ***));//two stars?
		}
		*row_num += 1;
		free(line);
	}
	return (validate_list(begin_list, *column_num, *row_num));
}
