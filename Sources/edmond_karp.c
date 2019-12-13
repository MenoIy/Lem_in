/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond_karp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 18:13:18 by hmney             #+#    #+#             */
/*   Updated: 2019/09/24 10:37:20 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	update_graph(t_env *store, t_path *path)
{
	t_list	*head;
	t_farm	*parent;
	t_farm	*fils;
	int		index;
	int		index_2;

	head = path->path;
	while (head->next != NULL)
	{
		parent = (t_farm *)head->content;
		if (head->next != NULL)
			fils = (t_farm *)head->next->content;
		index = search_edge(store, parent, fils);
		index_2 = search_edge(store, fils, parent);
		parent->edges[index].capacity--;
		fils->edges[index_2].capacity++;
		head = head->next;
	}
}

int			edmond_karp(t_env *store)
{
	t_path *path;

	while ((path = ft_bfs(store, 1)) != NULL)
	{
		update_graph(store, path);
		ft_lstdel(&path->path, &ft_delete_node);
		ft_memdel((void **)&path);
		if (!create_groups(store))
			return (0);
	}
	ft_print_results(store);
	return (1);
}
