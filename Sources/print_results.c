/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_results.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 21:15:41 by hmney             #+#    #+#             */
/*   Updated: 2019/09/24 20:46:38 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_data(t_list *data)
{
	t_list *head;

	head = data;
	while (head != NULL)
	{
		ft_putendl((char *)head->content);
		head = head->next;
	}
	ft_putchar('\n');
}

void		special_case(t_env *store)
{
	intmax_t index;

	index = 0;
	while (++index <= store->ants)
	{
		ft_putchar('L');
		ft_putnbr(index);
		ft_putchar('-');
		ft_putstr(store->position.end);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}

static void	print_instructions(t_path *path)
{
	t_list *head;
	t_farm *room;

	head = path->path;
	while (head != NULL)
	{
		room = (t_farm *)head->content;
		if (room->curent_ant)
		{
			ft_putchar('L');
			ft_putnbr(room->curent_ant);
			ft_putchar('-');
			ft_putstr(room->room_name);
			ft_putchar(' ');
		}
		head = head->next;
	}
}

static void	move_ants(t_env *store, t_path *path, int *index)
{
	t_list *head;
	t_farm *room;
	t_farm *next_room;

	head = path->path;
	while (head != NULL)
	{
		room = (t_farm *)head->content;
		if (head->next != NULL)
		{
			next_room = (t_farm *)head->next->content;
			if (room->room_id == store->position.end_id &&
					next_room->curent_ant)
				store->position.end_ants++;
			room->curent_ant = next_room->curent_ant;
		}
		else
		{
			if (*index <= store->ants && path->nb_ants-- > 0)
				room->curent_ant = (*index)++;
			else
				room->curent_ant = 0;
		}
		head = head->next;
	}
}

void		ft_print_results(t_env *store)
{
	t_list	*head;
	int		index;
	int		min;

	index = 1;
	min = INT_MAX;
	if (store->solution)
	{
		insert_ants(store);
		while (store->position.end_ants != store->ants)
		{
			head = store->solution->group;
			while (head != NULL)
			{
				move_ants(store, (t_path *)head->content, &index);
				print_instructions((t_path *)head->content);
				head = head->next;
			}
			ft_putchar('\n');
		}
	}
}
