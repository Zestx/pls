/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 17:00:35 by srobin            #+#    #+#             */
/*   Updated: 2019/09/20 18:25:29 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_entry_l(t_entry *entry, struct stat *fstats, int l_mode, t_maxlen pad)
{
	if (l_mode == 0)
	{
		ft_putstr(entry->filename);
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
	print_fname(entry->filename, entry->path, fstats);
	ft_putchar('\n');
}

void	print_fname(char *fname, char *path, struct stat *fstats)
{
	size_t	buffer;
	char	*buf;

	buf = malloc(sizeof(buf) * 1024);
	buffer = 1024;
	if (S_ISLNK(fstats->st_mode))
	{
		readlink(path, buf, buffer);
		ft_putstr(fname);
		ft_putstr(" -> ");
		ft_putstr(buf);
		free(buf);
	}
	else
		ft_putstr(fname);
}
