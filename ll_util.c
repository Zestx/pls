/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 11:16:11 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/22 11:36:54 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_entry	**ll_create_node(char *path, char *fname)
{
	t_entry		*node;
	struct stat	st_buff;

	if (!path || fname)
		return (NULL);
	if (!(node = malloc(sizeof(t_entry))))
		return (NULL);
	if (stat(path, &st_buff))
		return (NULL);
	node->filename = ft_strdup(fname);
	node->filestat = st_buff;
	node->next = NULL;
	return (node);
}

t_entry			**ll_append_node(t_entry *ll_head, char *path, char *fname)
{
	t_entry *roam;
	t_entry *node;

	if (!(node = create_node(path, fname)))
		return (NULL);
	if (!ll_head)
	{
		ll_head = node;
		return (ll_head);
	}
	roam = ll_head;
	while (roam->next)
		roam = roam->next;
	roam->next = node;
	return (ll_head);
}

void			ll_free(t_entry *ll_head)
{
	t_entry	*tmp;

	if (!ll_head)
		return ;
	while (ll_head)
	{
		tmp = ll_head->next;
		free(head->filename);
		free(head);
		head = tmp;
	}
}
