/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:24:38 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/20 19:03:41 by srobin           ###   ########.fr       */
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
	if (!(f_str = malloc(14)))
		exit(EXIT_FAILURE);
	year = get_year(r_time);
	while (i < 6)
	{
		f_str[i] = r_time[i];
		i++;
	}
	f_str[i] = ' ';
	f_str[i + 1] = ' ';
	i += 2;
	j = 0;
	while (j < 4)
	{
		f_str[i] = year[j];
		i++;
		j++;
	}
	f_str[i] = '\0';
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
