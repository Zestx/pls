/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_util2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:04:43 by srobin            #+#    #+#             */
/*   Updated: 2019/09/20 17:33:52 by qbackaer         ###   ########.fr       */
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

static size_t		get_link_length(t_entry *entry)
{
	size_t		length;

	if (!entry)
		return (0);
	length = ft_count_digits(entry->filestat.st_nlink);
	return (length);
}

t_maxlen			get_maxlen(t_entry *head)
{
	t_entry	*roam;
	t_maxlen ml;
	size_t  lnk_length;
	size_t	uid_length;
	size_t	grp_length;
	size_t	size_length;

	lnk_length = 0;
	uid_length = 0;
	grp_length = 0;
	size_length = 0;
	ml.lnk_maxlen = 0;
	ml.uid_maxlen = 0;
	ml.grp_maxlen = 0;
	ml.size_maxlen = 0;
	if (!head)
		return (ml);
	roam = head;
	while (roam)
	{
		lnk_length = get_link_length(roam);
		uid_length = ft_strlen(get_usrname(roam->filestat.st_uid));
		grp_length = ft_strlen(get_grpname(roam->filestat.st_gid));	
		size_length = get_size_length(roam);
		if (ml.lnk_maxlen < lnk_length)
			ml.lnk_maxlen = lnk_length;
		if (ml.uid_maxlen < uid_length)
			ml.uid_maxlen = uid_length;
		if (ml.grp_maxlen < grp_length)
			ml.grp_maxlen = grp_length;
		if (ml.size_maxlen < size_length)
			ml.size_maxlen = size_length;
		roam = roam->next;
	}
	return (ml);
}

t_maxlen			get_len(struct stat filestat)
{
	t_maxlen ml;

	ml.lnk_maxlen = ft_count_digits(filestat.st_nlink);
	ml.uid_maxlen = ft_strlen(get_usrname(filestat.st_uid));
	ml.grp_maxlen = ft_strlen(get_grpname(filestat.st_gid));	
	ml.size_maxlen = ft_count_digits(filestat.st_size);
	
	return (ml);
}
