/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_regargs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:58:46 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/27 19:31:10 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_args(char **reglist, char *opts, t_flag *flag)
{
	char		**roam;
	struct stat	st_buff;
	t_maxlen	pad;

	if (!reglist || !*reglist)
		return (0);
	pad = get_maxlen_args(reglist);
	roam = reglist;
	while (*roam)
	{
		lstat(*roam, &st_buff);
		print_inode(st_buff.st_ino, pad, opts);
		if (opts && ft_strchr(opts, 'l'))
			display_entry(*roam, &st_buff, 1, pad);
		else
			display_entry(*roam, &st_buff, 0, pad);
		roam++;
	}
	flag->nl = 1;
	return (1);
}
