/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 18:08:04 by hmney             #+#    #+#             */
/*   Updated: 2019/09/23 18:12:16 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	unvisited(t_env *store)
{
	int index;

	index = -1;
	while (++index < store->nb_rooms)
	{
		store->farm[index].visited = 0;
		store->farm[index].parent_bfs = NULL;
	}
}

static void	flow(t_queue *queue, t_farm *parent, t_link *fils, int *counter)
{
	if (!fils->edge->visited && fils->capacity)
	{
		if (parent->blocked)
		{
			if (fils->edge->blocked)
			{
				enqueue(queue, (void *)fils->edge, sizeof(t_farm));
				fils->edge->visited = 1;
				fils->edge->parent_bfs = parent;
			}
			else if (parent->parent_bfs && parent->parent_bfs->blocked)
			{
				enqueue(queue, (void *)fils->edge, sizeof(t_farm));
				fils->edge->visited = 1;
				fils->edge->parent_bfs = parent;
			}
			(*counter)++;
		}
		else
		{
			enqueue(queue, (void *)fils->edge, sizeof(t_farm));
			fils->edge->visited = 1;
			fils->edge->parent_bfs = parent;
		}
	}
}

static void	paths(t_queue *queue, t_farm *parent, t_link *fils)
{
	if (!fils->edge->visited && !fils->edge->blocked && !fils->capacity)
	{
		enqueue(queue, (void *)fils->edge, sizeof(t_farm));
		fils->edge->visited = 1;
		fils->edge->parent_bfs = parent;
	}
}

static void	add_childs(t_env *store, t_farm *parent, t_queue *queue, int set)
{
	t_link	*fils;
	int		counter;
	int		length_queue;
	int		index;

	index = -1;
	counter = 0;
	length_queue = queue->counter;
	while (++index < store->farm[parent->index].nb_edges)
	{
		fils = &store->farm[parent->index].edges[index];
		if (set)
			flow(queue, parent, fils, &counter);
		else
			paths(queue, parent, fils);
	}
	if (parent->blocked && counter && length_queue == queue->counter)
		parent->visited = 0;
}

t_path		*ft_bfs(t_env *store, int set)
{
	t_queue	*queue;
	t_farm	*parent;
	t_list	*temp;

	if (!(queue = (t_queue *)ft_memalloc(sizeof(t_queue))))
		return (NULL);
	unvisited(store);
	enqueue(queue, (void *)&store->farm[store->position.start_index],
			sizeof(t_farm));
	store->farm[store->position.start_index].visited = 1;
	while (!empty_queue(queue))
	{
		temp = dequeue(queue);
		parent = (t_farm *)temp->content;
		ft_memdel((void **)&temp);
		add_childs(store, parent, queue, set);
		if (store->farm[store->position.end_index].visited == 1)
		{
			free_queue(queue);
			ft_memdel((void **)&queue);
			return (get_path(store));
		}
	}
	ft_memdel((void **)&queue);
	return (NULL);
}
