/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 11:16:11 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/17 17:28:56 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_entry	*ll_create_node(char *path, char *fname)
{
	t_entry		*node;
	struct stat	st_buff;

	if (!(node = malloc(sizeof(t_entry))))
		exit(EXIT_FAILURE);
	if (lstat(path, &st_buff))
	{
		printf("LL_CREATE_NODE ERROR\n");
		perror(path);
		return (NULL);
	}
	if (!(node->path = ft_strdup(path)))
		exit(EXIT_FAILURE);
	if (!(node->filename = ft_strdup(fname)))
		exit(EXIT_FAILURE);
	node->filestat = st_buff;
	node->next = NULL;
	return (node);
}

t_entry			*ll_append_node(t_entry *head, char *path, char *fname)
{
	t_entry *roam;
	t_entry *node;

	if (!(node = ll_create_node(path, fname)))
		return (head);
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

t_entry			*ll_push_node(t_entry *head, char *path, char *fname)
{
	t_entry *node;

	if (!(node = ll_create_node(path, fname)))
		return (head);
	if (!head)
	{
		head = node;
		return (head);
	}
	node->next = head;
	head = node;
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

void			ll_print(t_entry *head, char *opts)
{
	t_entry *roam;

	if (!head)
		return ;
	roam = head;
	while (roam)
	{
		display_wpr(roam, opts);
		roam = roam->next;
	}
}

size_t			ll_size(t_entry *head)
{
	t_entry *roam;
	size_t	i;

	if (!head)
		return (0);
	i = 0;
	roam = head;
	while (roam)
	{
		roam = roam->next;
		i++;
	}
	return (i);
}
