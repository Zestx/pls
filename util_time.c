/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:24:38 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/18 19:59:28 by qbackaer         ###   ########.fr       */
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

	i = 0;
	spa_count = 0;
	f_str = malloc(14);
	year = get_year(r_time);
	while (1)
	{
		if (r_time[i] == ' ')
			spa_count++;
		if (spa_count == 2)
			break ;
		f_str[i] = r_time[i];
		i++;
	}
	f_str[i] = ' ';
	i++;
	j = 0;
	while (j < 4)
	{
		f_str[i] = year[j];
		i++;
		j++;
	}

	return (f_str);
}

char	*format_yun(char *r_time)
{
	char	*f_str;
	int		i;
	int		col_count;

	i = 0;
	col_count = 0;
	f_str = malloc(15);
	while (1)
	{
		if (r_time[i] == ':')
			col_count++;
		if (col_count >= 2)
			break ;
		f_str[i] = r_time[i];
		i++;
	}
	return (f_str);
}
