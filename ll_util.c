/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 11:16:11 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/22 15:20:27 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_entry	*ll_create_node(char *path, char *fname)
{
	t_entry		*node;
	struct stat	st_buff;

	if (!path || !fname)
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

t_entry			*ll_append_node(t_entry *head, char *path, char *fname)
{
	t_entry *roam;
	t_entry *node;

	if (!(node = ll_create_node(path, fname)))
		return (NULL);
	if (!head)
	{
		head = node;
		return (head);
	}
	roam = head;
	while (roam->next)
		roam = roam->next;
	roam->next = node;
	return (head);
}

void			ll_free(t_entry *head)
{
	t_entry	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		free(head->filename);
		free(head);
		head = tmp;
	}
}

void			ll_print(t_entry *head)
{
	t_entry *roam;

	if (!head)
		return ;
	roam = head;
	while (roam)
	{
		ft_putendl(roam->filename);
		roam = roam->next;
	}
}
