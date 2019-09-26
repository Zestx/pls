/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_util2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:50:09 by srobin            #+#    #+#             */
/*   Updated: 2019/09/26 14:50:46 by srobin           ###   ########.fr       */
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
	size_t		lnk_length;
	size_t		uid_length;
	size_t		grp_length;
	size_t		size_length;

	initiate_length(&lnk_length, &uid_length, &grp_length, &size_length);
	initiate_length(&ml.lnk_maxlen, &ml.uid_maxlen,
					&ml.grp_maxlen, &ml.size_maxlen);
	if (!roam)
		return (ml);
	while (roam)
	{
		lnk_length = get_link_length(roam);
		uid_length = ft_strlen(get_usrname(roam->filestat.st_uid));
		grp_length = ft_strlen(get_grpname(roam->filestat.st_gid));
		size_length = get_size_length(roam);
		compare_max(&ml.lnk_maxlen, lnk_length);
		compare_max(&ml.uid_maxlen, uid_length);
		compare_max(&ml.grp_maxlen, grp_length);
		compare_max(&ml.size_maxlen, size_length);
		roam = roam->next;
	}
	return (ml);
}
