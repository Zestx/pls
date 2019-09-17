/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:29:01 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/17 16:54:29 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		find_weakest_alpha(t_cursors *llc, char *opts)
{
	while (llc->curs_c)
	{
		if (opts && ft_strchr(opts, 't'))
		{

			if (get_time(llc->wkst_c->filename) < get_time(llc->curs_c->filename))
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

static t_entry		*ll_alpha_time_sort(t_entry *lst, size_t ll_size, char *cwd, char *opts)
{
	t_entry		*sorted_lst;
	t_cursors	llc;
	size_t		count;
	char		*path;

	sorted_lst = NULL;
	count = 0;
	while (count < ll_size - 1)
	{
		init_cursors(&llc, lst);
		find_weakest_alpha(&llc, opts);
		path = subdir_path(cwd, llc.wkst_c->filename);
		sorted_lst = ll_append_node(sorted_lst, path, llc.wkst_c->filename);
		if (llc.wkst_c == llc.wkst_p)
			lst = llc.wkst_c->next;
		else
			llc.wkst_p->next = llc.wkst_c->next;	
		alpha_free_wpr(llc.wkst_c, path);
		count++;
	}
	printf("====LIST====\n");
	ll_print(sorted_lst, opts);
	printf("============\n");
	path = subdir_path(cwd, lst->filename);
	sorted_lst = ll_append_node(sorted_lst, path, lst->filename);
	free(path);
	ll_free(lst);
	return (sorted_lst);
}

static t_entry		*ll_revrssort(t_entry *lst, char *cwd)
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
	}
	return (sorted_lst);
}

t_entry					*sort_ll(t_entry *lst, size_t ll_size, char *cwd, char *opts)
{
	t_entry		*sorted_lst;

	sorted_lst = NULL;
	sorted_lst = ll_alpha_time_sort(lst, ll_size, cwd, "");
	if (opts && ft_strchr(opts, 't'))
		sorted_lst = ll_alpha_time_sort(sorted_lst , ll_size, cwd, "t");
	if (opts && ft_strchr(opts, 'r'))
		sorted_lst = ll_revrssort(sorted_lst, cwd);
	return (sorted_lst);
}
