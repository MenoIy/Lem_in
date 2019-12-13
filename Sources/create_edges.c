/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_edges.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 18:23:30 by hmney             #+#    #+#             */
/*   Updated: 2019/09/24 09:53:07 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	insert_edge(t_env *store, t_farm *room, int index, int length)
{
	int			position;
	int			count;

	position = room->room_id % length;
	if (store->farm[index].edges[position].edge &&
			store->farm[index].edges[position].edge->room_id == room->room_id)
		return (0);
	count = -1;
	while (++count < length && store->farm[index].edges[position].edge != NULL)
		position = (position + 1) % length;
	store->farm[index].edges[position].edge = room;
	store->farm[index].edges[position].capacity = 1;
	return (1);
}

int			search_edge(t_env *store, t_farm *parent, t_farm *fils)
{
	int			index;
	int			position;
	int			count;

	if ((index = search_room(store, parent->room_name)) == -1)
		return (0);
	position = fils->room_id % store->farm[index].nb_edges;
	count = -1;
	while (++count < store->farm[index].nb_edges
			&& store->farm[index].edges[position].edge->room_id !=
			fils->room_id)
		position = (position + 1) % store->farm[index].nb_edges;
	if (store->farm[index].edges[position].edge->room_id != fils->room_id)
		return (-1);
	return (position);
}

int			create_edges(t_env *store)
{
	t_list	*head;
	int		index_1;
	int		length;

	index_1 = -1;
	while (++index_1 < store->nb_rooms)
	{
		length = ft_lstlength(store->farm[index_1].links);
		if (!(store->farm[index_1].edges =
					(t_link *)ft_memalloc(sizeof(t_link) * length)))
			return (0);
		store->farm[index_1].nb_edges = length;
		head = store->farm[index_1].links;
		while (head != NULL)
		{
			if (!insert_edge(store, (t_farm *)head->content, index_1, length))
				return (0);
			head = head->next;
		}
	}
	return (store->set_rooms && store->set_links);
}
