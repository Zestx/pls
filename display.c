/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:43:27 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/27 18:06:53 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//copied from my old ls. A lot of adaptations and ERROR CHECKING & MANAGEMENT to do!!
#include "ft_ls.h"

void	display_wpr(t_entry *entry, char *opts)
{
	if (opts && ft_strchr(opts, 'l'))
		display_entry(entry->filename, &(entry->filestat), 1);
	else
		display_entry(entry->filename, &(entry->filestat), 0);
}

//the l_mode 'boolean' is used to know if we need the long display (-l)
//or just the filename display. Some stuff needs to be fixed on the long
//display though, as the aditional x permissions and the right-aligned
//display of the columns.
int		display_entry(char *fname, struct stat *fstats, int l_mode)
{
	if (l_mode == 1)
	{
		get_mode(fstats->st_mode);
		ft_putstr("  ");
		format_link(fstats->st_nlink);
		ft_putstr("  ");
		ft_putstr(get_usrname(fstats->st_uid));
		ft_putstr("  ");
		ft_putstr(get_grpname(fstats->st_gid));
		ft_putstr("  ");
		//right-aligned display is partly done for the size.
		format_size(fstats->st_size);
		ft_putstr("  ");
		format_time(ctime(&(fstats->st_mtime)));
		ft_putstr(fname);
		ft_putchar('\n');
	}
	else if (l_mode == 0)
	{
		ft_putstr(fname);
		ft_putchar('\n');
	}
	else
		return (-1);
	return (0);
}

//I think this function was only used for testing, so commented here.
/*
void	ll_display(t_entry *head, char *dirpath, char *opts)
{
	t_entry *roam;

	roam = head;
	while (cursor)
	{
		display_wpr(roam, options);
		if (opts && ft_strchr(opts, 'R'))
			recursive_wpr(roam, path, opts);
		roam = roam->next;
	}
}*/

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
