/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:25:26 by hmney             #+#    #+#             */
/*   Updated: 2019/09/24 11:23:14 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_data(t_env *store)
{
	int index;

	ft_lstdel(&store->data, &ft_delete_content);
	index = -1;
	while (++index < store->nb_rooms)
	{
		ft_lstclear(&store->farm[index].links);
		ft_memdel((void **)&store->farm[index].edges);
	}
	ft_lstdel(&store->rooms, &ft_delete_content);
	ft_lstdel(&store->solution->group, &ft_delete_double);
	ft_memdel((void **)&store->solution);
	ft_memdel((void **)&store->farm);
	ft_strdel(&store->position.start);
	ft_strdel(&store->position.end);
	ft_memdel((void **)&store);
}

void		ft_manage_errors(t_env *store, char **line)
{
	ft_strdel(line);
	free_data(store);
	ft_putendl_fd("ERROR", 2);
	exit(1);
}
