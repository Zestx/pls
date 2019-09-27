/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:43:27 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/27 15:26:00 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_entry(char *fname, struct stat *fstats, int l, t_maxlen pad)
{
	if (l == 0)
	{
		ft_putstr(fname);
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
	print_fname(fname, fname, fstats);
	ft_putchar('\n');
}

void	format_name(struct stat *fstat, t_maxlen pad)
{
	int		curr_usize;
	int		curr_gsize;
	char	*usr_name;
	char	*grp_name;

	usr_name = get_usrname(fstat->st_uid);
	grp_name = get_grpname(fstat->st_gid);
	curr_usize = ft_strlen(usr_name);
	curr_gsize = ft_strlen(grp_name);
	ft_putstr(usr_name);
	while (pad.uid_maxlen - curr_usize > 0)
	{
		ft_putchar(' ');
		pad.uid_maxlen--;
	}
	ft_putstr("  ");
	ft_putstr(grp_name);
	while (pad.grp_maxlen - curr_gsize > 0)
	{
		ft_putchar(' ');
		pad.grp_maxlen--;
	}
}

void	format_time(char *r_time, int too_old)
{
	char	*f_time;

	while (*r_time != ' ')
		r_time++;
	r_time++;
	if (too_old)
		f_time = format_old(r_time);
	else
		f_time = format_yun(r_time);
	ft_putstr(f_time);
	ft_putchar(' ');
	free(f_time);
}

void	format_size(long size, size_t maxlen)
{
	char	*raw_size;
	size_t	curr_size;

	curr_size = ft_count_digits(size);
	while (curr_size < maxlen)
	{
		ft_putchar(' ');
		curr_size++;
	}
	raw_size = ft_itoa(size);
	ft_putstr(raw_size);
	free(raw_size);
}

void	format_link(int link, t_maxlen pad)
{
	char	*raw_link;
	int		curr_link;

	curr_link = ft_count_digits(link);
	while (pad.lnk_maxlen - curr_link > 0)
	{
		ft_putchar(' ');
		pad.lnk_maxlen--;
	}
	raw_link = ft_itoa(link);
	ft_putstr(raw_link);
	free(raw_link);
}
