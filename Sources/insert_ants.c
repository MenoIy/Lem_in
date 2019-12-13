/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:19:16 by hmney             #+#    #+#             */
/*   Updated: 2019/09/24 18:21:15 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	insert_ants(t_env *store)
{
	t_path	*path;
	t_path	*next_path;
	t_list	*head;
	int		index;

	index = 0;
	while (++index <= store->ants)
	{
		head = store->solution->group;
		while (head != NULL)
		{
			path = (t_path *)head->content;
			next_path = NULL;
			if (head->next != NULL)
				next_path = (t_path *)head->next->content;
			if (!next_path || path->length < next_path->length)
			{
				path->nb_ants++;
				path->length++;
				break ;
			}
			head = head->next;
		}
	}
}
