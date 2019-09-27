/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 13:58:15 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/27 19:36:01 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		isdir(t_entry *head)
{
	t_entry *roam;

	if (!head)
		return (-1);
	roam = head;
	while (roam->next)
		roam = roam->next;
	if (S_ISDIR(roam->filestat.st_mode))
		return (1);
	else
		return (0);
}

char			**ll_gen(t_entry **head, DIR *dir, char *path, char *opts)
{
	struct dirent	*entry;
	char			*new_path;
	char			**dirtab;

	dirtab = NULL;
	new_path = NULL;
	while ((entry = readdir(dir)))
	{
		new_path = subdir_path(path, entry->d_name);
		if (entry->d_name[0] != '.' || (opts && ft_strchr(opts, 'a')))
		{
			*head = ll_append_node(*head, new_path, entry->d_name);
			if (isdir(*head) && ft_strcmp(entry->d_name, ".")
					&& ft_strcmp(entry->d_name, ".."))
				dirtab = update_args(dirtab, new_path);
		}
		ft_sfree(new_path);
	}
	return (dirtab);
}
