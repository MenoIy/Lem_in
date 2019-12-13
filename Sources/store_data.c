/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:44:29 by hmney             #+#    #+#             */
/*   Updated: 2019/09/24 11:19:24 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	check_commands(t_env *store, char **line)
{
	t_list	*new;
	int		ret;
	int		ret_gnl;

	ret = -1;
	if (!ft_strcmp(*line, "##start"))
		ret = 1;
	else if (!ft_strcmp(*line, "##end"))
		ret = 2;
	else if (*line && *line[0] == '#')
		ret = 3;
	if (ret == 1 || ret == 2)
	{
		if (store->position.start_id && store->position.end_id)
			return (0);
		if ((ret_gnl = get_next_line(0, line)) == -1 || ret_gnl == 0)
			return (0);
		if (!(new = ft_lstnew((char *)*line, ft_strlen(*line) + 1)))
		{
			ft_strdel(line);
			return (0);
		}
		ft_lstadd(&store->data, new);
	}
	return (ret);
}

static int	get_number_of_ants(t_env *store)
{
	char	*line;
	int		ret_gnl;
	int		ret;

	while ((ret_gnl = get_next_line(0, &line)) == 1)
	{
		if (!ft_list_add_back(&store->data, (char *)line, ft_strlen(line) + 1))
		{
			ft_strdel(&line);
			return (0);
		}
		if ((ret = check_commands(store, &line)) == 3)
			continue ;
		else if (ret != -1)
			return (0);
		if (ft_isnumber(line) && (store->ants = ft_atol(line)) > 0)
			return (1);
		else
			return (0);
	}
	return (0);
}

static int	start_end_positions(t_env *store, int check, char **tab)
{
	if (check == 1)
	{
		if (!(store->position.start = ft_strdup(tab[0])))
			return (0);
		store->position.start_id = 1;
	}
	if (check == 2)
	{
		if (!(store->position.end = ft_strdup(tab[0])))
			return (0);
		store->position.end_id = 1;
	}
	return (1);
}

static int	check_room(t_env *store, char *line, int check)
{
	t_list	*room;
	char	**tab;

	if (ft_search_characters(line, ' ') != 2)
		return (0);
	if (!(tab = ft_strsplit(line, ' ')) || ft_tablen(tab) != 3)
		return (0);
	if (!ft_isnumber(tab[1]) || !ft_isnumber(tab[2]))
		return (free_tab(&tab));
	if (tab[0][0] == 'L' || tab[0][0] == '-' || tab[0][0] == '#')
		return (free_tab(&tab));
	if (!start_end_positions(store, check, tab))
		return (free_tab(&tab));
	if (!(room = ft_lstnew((char *)ft_strdup(tab[0]), ft_strlen(tab[0]) + 1)))
		return (free_tab(&tab));
	ft_lstadd(&store->rooms, room);
	store->set_rooms = 1;
	free_tab(&tab);
	return (!store->set_links);
}

int			store_data(t_env *store)
{
	t_list	*new;
	char	*line;
	int		ret;
	int		ret_gnl;

	if (!get_number_of_ants(store))
		return (0);
	while ((ret_gnl = get_next_line(0, &line)) == 1)
	{
		if (!(new = ft_lstnew((char *)line, ft_strlen(line) + 1)))
		{
			ft_strdel(&line);
			return (0);
		}
		ft_lstadd(&store->data, new);
		if (!(ret = check_commands(store, &line)))
			return (0);
		if (ret != 3 && !check_room(store, line, ret) &&
				!check_links(store, line))
			return (0);
	}
	if (ret_gnl == -1)
		return (0);
	return (create_edges(store));
}
