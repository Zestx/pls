/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:29:01 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/01 17:12:30 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		find_weakest_alpha(t_cursors *llc, char *opts)
{
	while (llc->curs_c)
	{
		if (opts && ft_strchr(opts, 't'))
		{
			if (get_time_ll(llc->wkst_c->filestat)
					< get_time_ll(llc->curs_c->filestat))
			{
				llc->wkst_c = llc->curs_c;
				llc->wkst_p = llc->curs_p;
			}
		}
		else if (ft_strcmp(llc->wkst_c->filename, llc->curs_c->filename) > 0)
		{
			llc->wkst_c = llc->curs_c;
			llc->wkst_p = llc->curs_p;
		}
		llc->curs_p = llc->curs_c;
		llc->curs_c = llc->curs_c->next;
	}
}

static t_entry	*ll_sort(t_entry *lst, size_t ll_size, char *cwd, char *opts)
{
	t_entry		*sorted_lst;
	t_cursors	c;
	size_t		count;
	char		*path;

	sorted_lst = NULL;
	count = 0;
	while (count < ll_size - 1)
	{
		init_cursors(&c, lst);
		find_weakest_alpha(&c, opts);
		path = subdir_path(cwd, c.wkst_c->filename);
		sorted_lst = ll_append_node(sorted_lst, path, c.wkst_c->filename);
		if (c.wkst_c == c.wkst_p)
			lst = c.wkst_c->next;
		else
			c.wkst_p->next = c.wkst_c->next;
		alpha_free_wpr(c.wkst_c, path);
		count++;
	}
	path = subdir_path(cwd, lst->filename);
	sorted_lst = ll_append_node(sorted_lst, path, lst->filename);
	ll_free(lst);
	free(path);
	return (sorted_lst);
}

static t_entry	*ll_revrssort(t_entry *lst, char *cwd)
{
	t_entry		*sorted_lst;
	t_cursors	llc;
	char		*path;

	sorted_lst = NULL;
	llc.curs_c = lst;
	while (llc.curs_c)
	{
		path = subdir_path(cwd, llc.curs_c->filename);
		sorted_lst = ll_push_node(sorted_lst, path, llc.curs_c->filename);
		llc.curs_c = llc.curs_c->next;
		free(path);
	}
	ll_free(lst);
	return (sorted_lst);
}

t_entry			*sort_ll(t_entry *lst, size_t ll_size, char *cwd, char *opts)
{
	t_entry		*sorted_lst;

	if (!lst)
		return (NULL);
	sorted_lst = NULL;
	sorted_lst = ll_sort(lst, ll_size, cwd, "");
	if (opts && ft_strchr(opts, 't'))
		sorted_lst = ll_sort(sorted_lst, ll_size, cwd, opts);
	if (opts && ft_strchr(opts, 'r'))
		sorted_lst = ll_revrssort(sorted_lst, cwd);
	return (sorted_lst);
}
