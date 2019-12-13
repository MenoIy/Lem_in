/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:29:02 by hmney             #+#    #+#             */
/*   Updated: 2019/09/24 18:22:18 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>

typedef struct	s_bd
{
	int			start_index;
	int			end_index;
	int			start_id;
	int			end_id;
	intmax_t	end_ants;
	char		*start;
	char		*end;
}				t_bd;

typedef struct	s_link
{
	struct s_farm		*edge;
	int					capacity;
}				t_link;

typedef struct	s_farm
{
	int					room_id;
	int					index;
	char				*room_name;
	struct s_list		*links;
	int					nb_edges;
	t_link				*edges;
	int					visited;
	int					blocked;
	struct s_farm		*parent_bfs;
	int					curent_ant;
}				t_farm;

typedef struct	s_path
{
	t_list		*path;
	int			length;
	int			nb_ants;
}				t_path;

typedef struct	s_solution
{
	t_list		*group;
	int			score;
}				t_solution;

typedef struct	s_env
{
	t_list		*data;
	t_list		*rooms;
	t_farm		*farm;
	t_solution	*solution;
	t_bd		position;
	intmax_t	ants;
	int			nb_rooms;
	int			set_rooms;
	int			set_links;
}				t_env;

void			ft_delete_double(void *content, size_t content_size);
int				create_farm(t_env *store, t_list *rooms);
int				search_rooms(t_list *rooms, char *first_room,
				char *second_room);
int				check_links(t_env *store, char *line);
int				store_data(t_env *store);
void			free_data(t_env *store);
void			ft_manage_errors(t_env *store, char **line);
int				search_room(t_env *store, char *room);
t_path			*ft_bfs(t_env *store, int set);
int				edmond_karp(t_env *store);
int				create_groups(t_env *store);
int				create_edges(t_env *store);
int				search_edge(t_env *store, t_farm *parent, t_farm *fils);
t_path			*get_path(t_env *store);
void			ft_print_results(t_env *store);
void			print_data(t_list *data);
void			special_case(t_env *store);
void			insert_ants(t_env *store);
#endif
