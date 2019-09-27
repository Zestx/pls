/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_max.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:50:40 by srobin            #+#    #+#             */
/*   Updated: 2019/09/27 15:31:15 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				init_size(t_maxlen *ml)
{
	ml->lnk_maxlen = 0;
	ml->uid_maxlen = 0;
	ml->grp_maxlen = 0;
	ml->size_maxlen = 0;
	ml->ino_maxlen = 0;
}

static size_t		get_size_length(struct stat filestat)
{
	size_t	length;

	if (S_ISCHR(filestat.st_mode) || (S_ISBLK(filestat.st_mode)))
		length = 8;
	else
		length = ft_count_digits(filestat.st_size);
	return (length);
}

t_maxlen			get_maxlen_args(char **args)
{
	t_maxlen	ml;
	t_maxlen	cl;
	struct stat	st_buff;

	init_size(&ml);
	init_size(&cl);
	if (!args)
		return (ml);
	while (*args)
	{
		lstat(*args, &st_buff);
		cl.lnk_maxlen = ft_count_digits(st_buff.st_nlink);
		cl.uid_maxlen = ft_strlen(get_usrname(st_buff.st_uid));
		cl.grp_maxlen = ft_strlen(get_grpname(st_buff.st_gid));
		cl.size_maxlen = get_size_length(st_buff);
		cl.ino_maxlen = ft_count_digits(st_buff.st_ino);
		compare_max(&ml.lnk_maxlen, cl.lnk_maxlen);
		compare_max(&ml.uid_maxlen, cl.uid_maxlen);
		compare_max(&ml.grp_maxlen, cl.grp_maxlen);
		compare_max(&ml.size_maxlen, cl.size_maxlen);
		compare_max(&ml.ino_maxlen, cl.ino_maxlen);
		args++;
	}
	return (ml);
}
