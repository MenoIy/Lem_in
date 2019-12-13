/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_date2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:24:07 by hmney             #+#    #+#             */
/*   Updated: 2019/09/24 09:57:36 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			search_room(t_env *store, char *room)
{
	intmax_t	hash_value;
	int			index;
	int			counter;

	counter = -1;
	hash_value = ft_hash_string(room);
	index = hash_value % store->nb_rooms;
	while (++counter < store->nb_rooms &&
			store->farm[index].room_id != hash_value
			&& store->farm[index].room_name != NULL)
		index = (index + 1) % store->nb_rooms;
	if (store->farm[index].room_id != hash_value)
		return (-1);
	return (index);
}

static int	add_links(t_env *store, char *first_room, char *second_room)
{
	t_list	*link;
	int		index_fr;
	int		index_sr;

	if ((index_fr = search_room(store, first_room)) == -1)
		return (0);
	if ((index_sr = search_room(store, second_room)) == -1)
		return (0);
	if (!(link = ft_lstnew((void *)&store->farm[index_sr], sizeof(t_farm))))
		return (0);
	ft_lstadd(&store->farm[index_fr].links, link);
	if (!(link = ft_lstnew((void *)&store->farm[index_fr], sizeof(t_farm))))
		return (0);
	ft_lstadd(&store->farm[index_sr].links, link);
	return (1);
}

static int	insert_room(t_farm *farm, char *room, int nb_rooms)
{
	intmax_t	hash_value;
	int			index;
	int			counter;

	hash_value = ft_hash_string(room);
	index = hash_value % nb_rooms;
	if (farm[index].room_id == hash_value)
		return (0);
	counter = -1;
	while (++counter < nb_rooms && farm[index].room_name != NULL)
		index = (index + 1) % nb_rooms;
	farm[index].room_id = hash_value;
	farm[index].room_name = room;
	farm[index].index = index;
	farm[index].links = NULL;
	return (1);
}

int			create_farm(t_env *store, t_list *rooms)
{
	int index;

	store->nb_rooms = ft_lstlength(rooms);
	store->farm = (t_farm *)ft_memalloc(sizeof(t_farm) * store->nb_rooms);
	if (!store->farm)
		return (0);
	while (rooms != NULL)
	{
		if (!insert_room(store->farm, (char *)rooms->content, store->nb_rooms))
			return (0);
		rooms = rooms->next;
	}
	if ((index = search_room(store, store->position.start)) == -1)
		return (0);
	store->position.start_index = index;
	store->position.start_id = store->farm[index].room_id;
	if ((index = search_room(store, store->position.end)) == -1)
		return (0);
	store->position.end_index = index;
	store->position.end_id = store->farm[index].room_id;
	return (1);
}

int			check_links(t_env *store, char *line)
{
	static int	index;
	char		**tab;

	if (!store->position.start_id || !store->position.end_id
			|| !store->set_rooms)
		return (0);
	if (index++ == 0)
		if (!create_farm(store, store->rooms))
			return (0);
	if (ft_search_characters(line, '-') != 1)
		return (0);
	if (!(tab = ft_strsplit(line, '-')) || ft_tablen(tab) != 2)
		return (0);
	if (!add_links(store, tab[0], tab[1]))
		return (free_tab(&tab));
	store->set_links = 1;
	free_tab(&tab);
	return (1);
}
