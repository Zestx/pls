/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 17:00:35 by srobin            #+#    #+#             */
/*   Updated: 2019/09/23 19:22:38 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_entry_l(t_entry *ent, struct stat *fstats, int l, t_maxlen pad)
{
	if (l == 0)
	{
		ft_putstr(ent->filename);
		ft_putchar('\n');
		return ;
	}
	get_mode(fstats->st_mode);
	ft_putstr("  ");
	format_link(fstats->st_nlink, pad);
	ft_putstr(" ");
	format_name(fstats, pad);
	ft_putstr("  ");
	format_size(fstats->st_size, pad);
	ft_putstr(" ");
	format_time(ctime(&(fstats->st_mtime)), is_tooold(fstats->st_mtime));
	print_fname(ent->filename, ent->path, fstats);
	ft_putchar('\n');
}

void	print_fname(char *fname, char *path, struct stat *fstats)
{
	size_t	buffer;
	char	*buf;

	if (S_ISLNK(fstats->st_mode))
	{
		if (!(buf = malloc(sizeof(buf) * 1024)))
			exit(EXIT_FAILURE);
		buffer = 4096;
		readlink(path, buf, buffer);
		ft_putstr(fname);
		ft_putstr(" -> ");
		ft_putstr(buf);
		free(buf);
	}
	else
		ft_putstr(fname);
}
