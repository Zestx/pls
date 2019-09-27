/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 17:00:35 by srobin            #+#    #+#             */
/*   Updated: 2019/09/27 19:23:12 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_wpr(t_entry *ent, char *opts, t_maxlen pad)
{
	print_inode(ent->filestat.st_ino, pad, opts);
	if (opts && ft_strchr(opts, 'l'))
		display_entry_l(ent, &(ent->filestat), 1, pad);
	else
		display_entry_l(ent, &(ent->filestat), 0, pad);
}

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
	if (!(print_minormajor(fstats, pad)))
		format_size(fstats->st_size, pad.size_maxlen);
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

int		print_minormajor(struct stat *fstats, t_maxlen ml)
{
	size_t	major;
	size_t	minor;
	size_t	minmajpad;
	char	*tmp;

	if (S_ISCHR(fstats->st_mode) || S_ISBLK(fstats->st_mode))
	{
		major = ft_count_digits(fstats->st_rdev >> 24);
		minor = ft_count_digits(fstats->st_rdev & 16777215);
		minmajpad = 8;
		if (ml.size_maxlen > 8)
			while (ml.size_maxlen - minmajpad-- > 8)
				ft_putchar(' ');
		while (3 - major++ > 0)
			ft_putchar(' ');
		tmp = ft_itoa(fstats->st_rdev >> 24);
		utils(&tmp, 0) && utils(&tmp, 1) && utils(&tmp, 2);
		while (4 - minor++ > 0)
			ft_putchar(' ');
		tmp = ft_itoa(fstats->st_rdev & 16777215);
		utils(&tmp, 0) && utils(&tmp, 2);
		return (1);
	}
	else
		return (0);
}

void	print_inode(long size, t_maxlen pad, char *opts)
{
	if (opts && ft_strchr(opts, 'i'))
	{
		format_size(size, pad.ino_maxlen);
		ft_putchar(' ');
	}
	else
		return ;
}
