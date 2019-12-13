/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:33:36 by hmney             #+#    #+#             */
/*   Updated: 2019/09/25 11:55:57 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(void)
{
	t_env	*store;
	t_path	*path;

	path = NULL;
	if (!(store = (t_env *)ft_memalloc(sizeof(t_env))))
		return (1);
	if (!store_data(store) || !(path = ft_bfs(store, 1)))
		ft_manage_errors(store, NULL);
	ft_lstdel(&path->path, &ft_delete_node);
	ft_memdel((void **)&path);
	ft_lstrev(&store->data);
	print_data(store->data);
	if (search_edge(store, &store->farm[store->position.start_index],
				&store->farm[store->position.end_index]) != -1)
		special_case(store);
	else
		edmond_karp(store);
	free_data(store);
	return (0);
}
