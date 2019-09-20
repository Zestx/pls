/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_regargs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:58:46 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/20 20:30:19 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_args(char **reglist, char *opts)
{
	char		**roam;
	char		*path;
	struct stat	st_buff;
	t_maxlen	pad;

	if (!reglist || !*reglist)
		return (0);
	roam = reglist;
	while (*roam)
	{
		path = subdir_path(".", *roam);
		if (lstat(path, &st_buff))
		{
			perror(path);
			return (0);
		}
		pad = get_len(st_buff);
		if (opts && ft_strchr(opts, 'l'))
			display_entry(path, &st_buff, 1, pad);
		else
			display_entry(path, &st_buff, 0, pad);
		roam++;
		free(path);
	}
	return (1);
}
