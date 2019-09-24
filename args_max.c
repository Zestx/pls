/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_util2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:04:43 by srobin            #+#    #+#             */
/*   Updated: 2019/09/24 17:47:54 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			init_size(t_maxlen *ml)
{
	ml->lnk_maxlen = 0;
	ml->uid_maxlen = 0;
	ml->grp_maxlen = 0;
	ml->size_maxlen = 0;
}

t_maxlen			get_maxlen_args(char **args)
{
	char		**roam;
	t_maxlen	ml;
	size_t		lnk_length;
	size_t		uid_length;
	size_t		grp_length;
	size_t		size_length;
	struct stat	st_buff;

	
	init_size(&ml);
	lnk_length = 0;
	uid_length = 0;
	grp_length = 0;
	size_length = 0;
	if (!args)
		return (ml);
	roam = args;
	while (*roam)
	{
		lstat(*roam, &st_buff);	
		lnk_length = ft_count_digits(st_buff.st_nlink);
		uid_length = ft_strlen(get_usrname(st_buff.st_uid));
		grp_length = ft_strlen(get_grpname(st_buff.st_gid));
		size_length = ft_count_digits(st_buff.st_size);
		if (ml.lnk_maxlen < lnk_length)
			ml.lnk_maxlen = lnk_length;
		if (ml.uid_maxlen < uid_length)
			ml.uid_maxlen = uid_length;
		if (ml.grp_maxlen < grp_length)
			ml.grp_maxlen = grp_length;
		if (ml.size_maxlen < size_length)
			ml.size_maxlen = size_length;
		roam++;
	}
	return (ml);
}
