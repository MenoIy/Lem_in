/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 18:12:22 by hmney             #+#    #+#             */
/*   Updated: 2019/09/24 10:45:07 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*get_path(t_env *store)
{
	t_path	*ret;
	t_list	*path;
	t_list	*elem;
	t_farm	*temp;
	int		index;

	path = NULL;
	temp = &store->farm[store->position.end_index];
	index = 0;
	while (++index)
	{
		if (!(elem = ft_lstnew((void *)temp, sizeof(t_farm))))
			return (NULL);
		ft_lstadd(&path, elem);
		if (temp->index == store->position.start_index)
			break ;
		temp = temp->parent_bfs;
	}
	if (!(ret = (t_path *)ft_memalloc(sizeof(t_path))))
		return (NULL);
	ret->path = path;
	ret->length = index;
	return (ret);
}
