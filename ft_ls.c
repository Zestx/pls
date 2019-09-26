/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:44:08 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/26 16:51:30 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	list(char *path, t_argstabs input, int f_flag)
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
	dirtab = ll_generate(&entries, dir, path, input.opts);
	sorted = sort_ll(entries, ll_size(entries), path, input.opts);
	if (f_flag)
		ft_putchar('\n');
	f_flag = 1;
	ll_print(sorted, input.opts);
	ll_free(sorted);
	roam = dirtab;
	if (input.opts && ft_strchr(input.opts, 'R') && dirtab)
		while (*roam)
			list(*roam++, input, f_flag);
	ft_freetab(dirtab);
	closedir(dir);
	return (1);
}

static void	split_args(t_argstabs input, char ***dir_list, char ***reg_list)
{
	char		**roam;
	struct stat	st_buff;

	roam = input.args;
	while (*roam)
	{
		if (input.opts && ft_strchr(input.opts, 'l'))
		{
			if (lstat(*roam, &st_buff))
			{
				perror(*roam);
				roam++;
				continue ;
			}
		}
		else if (stat(*roam, &st_buff))
		{
			perror(*roam);
			roam++;
			continue;
		}
		if (S_ISDIR(st_buff.st_mode))
			*dir_list = update_args(*dir_list, *roam);
		else
			*reg_list = update_args(*reg_list, *roam);
		roam++;
	}
	ft_freetab(input.args);
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
	input.args = sort_args(input.args, &input);
	if (!input.args)
		input.args = update_args(input.args, ".");
	split_args(input, &dir_list, &reg_list);
	if (print_args(reg_list, input.opts))
		f_flag = 1;
	roam = dir_list;
	if (dir_list)
		while (*roam)
		{
			list(*roam++, input, f_flag);
			f_flag = 1;
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
	ft_sfree(input.opts);
	return (0);
}
