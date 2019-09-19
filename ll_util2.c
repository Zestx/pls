/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_util2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:04:43 by srobin            #+#    #+#             */
/*   Updated: 2019/09/19 16:48:28 by srobin           ###   ########.fr       */
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

	if (!path)
		return (0);
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

static size_t		get_size_length(t_entry *entry)
{
	size_t		length;

	if (!entry)
		return (0);
	length = ft_count_digits(entry->filestat.st_size);
	return (length);
}

size_t			get_size_max(t_entry *head)
{
	t_entry	*roam;
	size_t	max_length;
	size_t	size_length;

	if (!head)
		return (0);
	roam = head;
	max_length = 0;
	while (roam)
	{
		size_length = get_size_length(roam);
		if (max_length < size_length)
			max_length = size_length;
		roam = roam->next;
	}
	return (max_length);
}
