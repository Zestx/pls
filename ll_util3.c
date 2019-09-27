/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_util3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:29:59 by srobin            #+#    #+#             */
/*   Updated: 2019/09/27 15:30:55 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t		ll_size(t_entry *head)
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

t_maxlen	get_len(struct stat filestat)
{
	t_maxlen ml;

	ml.lnk_maxlen = ft_count_digits(filestat.st_nlink);
	ml.uid_maxlen = ft_strlen(get_usrname(filestat.st_uid));
	ml.grp_maxlen = ft_strlen(get_grpname(filestat.st_gid));
	if (S_ISCHR(filestat.st_mode || S_ISBLK(filestat.st_mode)))
		ml.size_maxlen = 8;
	else
		ml.size_maxlen = ft_count_digits(filestat.st_size);
	return (ml);
}

void		compare_max(size_t *max, size_t check)
{
	if (*max < check)
		*max = check;
}
