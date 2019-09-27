/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_util2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:50:09 by srobin            #+#    #+#             */
/*   Updated: 2019/09/27 16:38:24 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t		get_block_size(char *path)
{
	struct stat	attr;
	size_t		blocks;

	if (!path)
		return (0);
	if (lstat(path, &attr))
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
	if (S_ISCHR(entry->filestat.st_mode) || S_ISBLK(entry->filestat.st_mode))
		length = 8;
	else
		length = ft_count_digits(entry->filestat.st_size);
	return (length);
}

static size_t		get_link_length(t_entry *entry)
{
	size_t		length;

	if (!entry)
		return (0);
	length = ft_count_digits(entry->filestat.st_nlink);
	return (length);
}

t_maxlen			get_maxlen(t_entry *roam)
{
	t_maxlen	ml;
	t_maxlen	cl;

	init_size(&ml);
	init_size(&cl);
	if (!roam)
		return (ml);
	while (roam)
	{
		cl.lnk_maxlen = get_link_length(roam);
		cl.uid_maxlen = ft_strlen(get_usrname(roam->filestat.st_uid));
		cl.grp_maxlen = ft_strlen(get_grpname(roam->filestat.st_gid));
		cl.size_maxlen = get_size_length(roam);
		cl.ino_maxlen = ft_count_digits(roam->filestat.st_ino);
		compare_max(&ml.lnk_maxlen, cl.lnk_maxlen);
		compare_max(&ml.uid_maxlen, cl.uid_maxlen);
		compare_max(&ml.grp_maxlen, cl.grp_maxlen);
		compare_max(&ml.size_maxlen, cl.size_maxlen);
		compare_max(&ml.ino_maxlen, cl.ino_maxlen);
		roam = roam->next;
	}
	return (ml);
}
