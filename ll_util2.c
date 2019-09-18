/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_util2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:04:43 by srobin            #+#    #+#             */
/*   Updated: 2019/09/18 14:07:00 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t				ll_size(t_entry *head)
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

static size_t		get_block_size(char *path)
{
	struct stat	attr;
	size_t		blocks;

	if (stat(path, &attr))
		return (0);
	blocks = attr.st_blocks;
	return (blocks);
}

size_t				count_ll_blocks(t_entry *head)
{
	t_entry *roam;
	size_t	i;

	if (!head)
		return (0);
	i = 0;
	roam = head;
	while (roam)
	{
		i = i + get_block_size(roam->path);
		roam = roam->next;
	}
	return (i);
}
