/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:50:42 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/23 19:31:55 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_cursors(t_cursors *llc, t_entry *lst)
{
	llc->curs_c = lst;
	llc->curs_p = llc->curs_c;
	llc->wkst_c = llc->curs_c;
	llc->wkst_p = llc->curs_p;
}

void	alpha_free_wpr(t_entry *entry, char *path)
{
	free(entry->filename);
	free(entry->path);
	free(entry);
	free(path);
}

int		is_tooold(time_t m_time)
{
	if (time(NULL) - m_time > 15552000)
		return (1);
	return (0);
}

char	*get_year(char *m_time)
{
	char	*ptr;
	char	*year;
	int		i;

	ptr = m_time;
	while (*ptr != '\n')
		ptr++;
	*ptr = '\0';
	i = 0;
	while (i < 4)
	{
		ptr--;
		i++;
	}
	if (!(year = ft_strdup(ptr)))
		exit(EXIT_FAILURE);
	return (year);
}

size_t	tablen(char **tab)
{
	char	**roam;
	size_t	i;

	if (!tab)
		return (0);
	roam = tab;
	i = 0;
	while (*roam)
	{
		i++;
		roam++;
	}
	return (i);
}
