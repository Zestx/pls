/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:24:38 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/01 17:06:50 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*format_old(char *r_time)
{
	char	*f_str;
	char	*year;
	int		i;
	int		j;
	int		spa_count;

	i = -1;
	spa_count = 0;
	if (!(f_str = malloc(14)))
		exit(EXIT_FAILURE);
	year = get_year(r_time);
	while (++i < 6)
		f_str[i] = r_time[i];
	f_str[i] = ' ';
	f_str[i + 1] = ' ';
	i += 2;
	j = 0;
	while (j < 4)
		f_str[i++] = year[j++];
	f_str[i] = '\0';
	free(year);
	return (f_str);
}

char	*format_yun(char *r_time)
{
	char	*f_str;
	int		i;
	int		col_count;

	i = 0;
	col_count = 0;
	if (!(f_str = malloc(15)))
		exit(EXIT_FAILURE);
	while (1)
	{
		if (r_time[i] == ':')
			col_count++;
		if (col_count >= 2)
			break ;
		f_str[i] = r_time[i];
		i++;
	}
	f_str[i] = '\0';
	return (f_str);
}

long	get_time(char *path)
{
	struct stat	attr;
	time_t		m_time;

	if (lstat(path, &attr))
		return (0);
	m_time = attr.st_mtime;
	return (m_time);
}

long	get_time_ll(struct stat fstat)
{
	time_t		m_time;

	m_time = fstat.st_mtime;
	return (m_time);
}
