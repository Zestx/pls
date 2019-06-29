/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:43:27 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/29 20:25:55 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// A lot of adaptations and ERROR CHECKING & MANAGEMENT to do!!
#include "ft_ls.h"

void	display_wpr(t_entry *entry, char *opts)
{
	if (opts && ft_strchr(opts, 'l'))
		display_entry(entry->filename, &(entry->filestat), 1);
	else
		display_entry(entry->filename, &(entry->filestat), 0);
}

void	display_entry(char *fname, struct stat *fstats, int l_mode)
{
	if (l_mode == 0)
	{
		ft_putstr(fname);
		ft_putchar('\n');
		return ;
	}
	get_mode(fstats->st_mode);
	ft_putstr("  ");
	format_link(fstats->st_nlink);
	ft_putstr("  ");
	ft_putstr(get_usrname(fstats->st_uid));
	ft_putstr("  ");
	ft_putstr(get_grpname(fstats->st_gid));
	ft_putstr("  ");
	format_size(fstats->st_size);
	ft_putstr("  ");
	format_time(ctime(&(fstats->st_mtime)));
	ft_putstr(fname);
	ft_putchar('\n');
}

void	format_time(char *r_time)
{
	char	*f_time;
	int		col_count;
	char	*ptr;

	f_time = malloc(15);
	ptr = f_time;
	while (*r_time != ' ')
		r_time++;
	r_time++;
	col_count = 0;
	while (1)
	{
		if (*r_time == ':')
			col_count++;
		if (col_count >= 2)
			break ;
		*ptr = *r_time;
		ptr++;
		r_time++;
	}
	*ptr++ = ' ';
	*ptr = '\0';
	ft_putstr(f_time);
	free(f_time);
}

void	format_size(int size)
{
	char	*raw_size;
	int		nb_len;

	raw_size = ft_itoa(size);
	nb_len = ft_strlen(raw_size);
	while (10 - nb_len > 0)
	{
		ft_putchar(' ');
		nb_len++;
	}
	ft_putstr(raw_size);
	free(raw_size);
}

void	format_link(int link)
{
	char	*raw_link;
	int		nb_len;

	raw_link = ft_itoa(link);
	nb_len = ft_strlen(raw_link);
	while (3 - nb_len > 0)
	{
		ft_putchar(' ');
		nb_len++;
	}
	ft_putstr(raw_link);
	free(raw_link);
}
