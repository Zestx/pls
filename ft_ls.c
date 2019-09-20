/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:44:08 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/20 18:55:23 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	list(char *path, char *opts, int f_flag)
{
	DIR				*dir;
	t_entry			*entries;
	t_entry			*sorted;
	char			**dirtab;
	char			**roam;

	sorted = NULL;
	if (!(dir = opendir(path)))
	{
		perror(path);
		return (0);
	}
	entries = NULL;
	dirtab = ll_generate(&entries, dir, path, opts);
	sorted = sort_ll(entries, ll_size(entries), path, opts);
	if (f_flag)
		ft_putchar('\n');
	f_flag = 1;
	ft_putstr(path);
	ft_putendl(":");
	ll_print(sorted, opts);
	ll_free(sorted);
	if (opts && ft_strchr(opts, 'R') && dirtab)
	{
		roam = dirtab;
		while (*roam)
		{
			list(*roam, opts, f_flag);
			roam++;
		}
	}
	ft_freetab(dirtab);
	closedir(dir);
	return (1);
}

static int	split_args(t_argstabs input, char ***dir_list, char ***reg_list)
{
	char		**roam;
	struct stat	st_buff;

	roam = input.args;
	while (*roam)
	{
		if (stat(*roam, &st_buff))
			perror(*roam);
		else if (S_ISDIR(st_buff.st_mode))
		{
			if (!(check_update(dir_list, *reg_list, *roam, &input)))
				return (0);
		}
		else if (!(check_update(reg_list, *dir_list, *roam, &input)))
			return (0);
		roam++;
	}
	ft_freetab(input.args);
	return (1);
}

static int	ls_dispatch(t_argstabs input)
{
	char		**dir_list;
	char		**reg_list;
	char		**roam;
	int			f_flag;

	f_flag = 0;
	dir_list = NULL;
	reg_list = NULL;
	if (!input.args)
	{
		list(".", input.opts, f_flag);
		return (1);
	}
	sort_args(&input.args, &input);
	if (!split_args(input, &dir_list, &reg_list))
	{
		ft_freetab(dir_list);
		ft_freetab(reg_list);
		return (0);
	}
	if (print_args(reg_list, input.opts))
		f_flag = 1;
	if (dir_list)
	{
		roam = dir_list;
		while (*roam)
		{
			list(*roam, input.opts, f_flag);
			f_flag = 1;
			roam++;
		}
	}
	ft_freetab(dir_list);
	ft_freetab(reg_list);
	return (1);
}

int			main(int argc, char **argv)
{
	t_argstabs input;

	input.args = NULL;
	input.opts = NULL;
	if (!parse(argc, argv, &input.opts, &input.args))
	{
		arg_free(input.args, input.opts);
		return (1);
	}
	if (!check_opt(input.opts, input.args))
		return (1);
	ls_dispatch(input);
	return (0);
}
