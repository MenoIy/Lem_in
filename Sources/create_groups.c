/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_groups.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:11:32 by hmney             #+#    #+#             */
/*   Updated: 2019/09/24 10:44:56 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	unblocked(t_env *store)
{
	int index;

	if (!store->solution)
	{
		if (!(store->solution = (t_solution *)ft_memalloc(sizeof(t_solution))))
			return (0);
		store->solution->score = INT_MAX;
	}
	index = -1;
	while (++index < store->nb_rooms)
		store->farm[index].blocked = 0;
	return (1);
}

static void	update_graph_group(t_env *store, t_path *path)
{
	t_list	*head;
	t_farm	*parent;

	head = path->path;
	while (head->next != NULL)
	{
		parent = (t_farm *)head->content;
		if (parent->index != store->position.start_index
				&& parent->index != store->position.end_index)
			parent->blocked = 1;
		head = head->next;
	}
}

static int	scorepaths(t_list **group, t_path **path, int *old_score, int score)
{
	t_list *elem;
	t_list *temp;

	if (score > *old_score)
	{
		ft_lstdel(&(*path)->path, &ft_delete_node);
		ft_memdel((void **)path);
		return (0);
	}
	*old_score = score;
	temp = (*path)->path;
	(*path)->path = (*path)->path->next;
	(*path)->length--;
	ft_memdel((void **)&temp);
	ft_lstrev(&(*path)->path);
	if (!(elem = ft_lstnew((void *)*path, sizeof(t_path))))
		return (0);
	ft_lstadd(group, elem);
	return (1);
}

static void	select_group(t_env *store, t_list *group, int score)
{
	if (score < store->solution->score)
	{
		ft_lstdel(&store->solution->group, &ft_delete_double);
		store->solution->score = score;
		ft_lstrev(&group);
		store->solution->group = group;
	}
	else
		ft_lstdel(&group, &ft_delete_double);
}

int			create_groups(t_env *store)
{
	t_list	*group;
	t_path	*path;
	int		score;
	int		nb_room;
	int		nb_path;

	if (!unblocked(store))
		return (0);
	group = NULL;
	nb_room = 0;
	nb_path = 1;
	score = INT_MAX;
	while ((path = ft_bfs(store, 0)) != NULL)
	{
		update_graph_group(store, path);
		nb_room += path->length - 2;
		if (!scorepaths(&group, &path, &score,
		ft_ceil((store->ants + nb_room) / (float)nb_path++)))
			break ;
	}
	select_group(store, group, score);
	return (1);
}
