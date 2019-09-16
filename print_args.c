/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_regargs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:58:46 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/16 19:51:34 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_args(char **reglist, char *opts)
{
	char **roam;
	char *path;
	struct stat st_buff;

	if (!reglist || !*reglist)
		return (0);
	roam = reglist;
	while (*roam)
	{
		//secure this:
		path = subdir_path(".", *roam);
		if (lstat(path, &st_buff))
		{
			perror(path);
			return (0);
		}
		if (opts && ft_strchr(opts, 'l'))
			display_entry(path, &st_buff, 1);
		else
			display_entry(path, &st_buff, 0);
		roam++;
	}
	return (1);
}
