/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 09:53:32 by hmney             #+#    #+#             */
/*   Updated: 2019/09/24 10:44:34 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_delete_double(void *content, size_t content_size)
{
	t_list	*list;
	t_path	*path;

	path = (t_path *)content;
	list = path->path;
	ft_lstdel(&list, &ft_delete_node);
	ft_memdel((void **)&path);
	(void)content_size;
}
