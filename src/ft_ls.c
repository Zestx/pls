/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:44:08 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/01 15:40:46 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				list(char *path, t_argstabs input, t_flag flag, size_t nb_arg)
{
	DIR				*dir;
	t_entry			*entries;
	t_entry			*sorted;
	char			**dirtab;

	if (!(dir = opendir(path)))
	{
		perror(path);
		return (0);
	}
	entries = NULL;
	if ((dirtab = sort_args(ll_gen(&entries, dir, path, input.opts), &input)))
		flag.dt = 1;
	sorted = sort_ll(entries, ll_size(entries), path, input.opts);
	list_helper(path, input, flag, nb_arg);
	flag.nl = 1;
	ll_print(sorted, input.opts);
	ll_free(sorted);
	recursive_wpr(dirtab, input, flag, nb_arg);
	ft_freetab(dirtab);
	closedir(dir);
	return (1);
}

static void		split_args(t_argstabs input, t_split *split)
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
				perror(*roam++);
				continue ;
			}
		}
		else if (stat(*roam, &st_buff))
		{
			perror(*roam++);
			continue ;
		}
		split_helper(st_buff, input.opts, split, roam);
		roam++;
	}
	ft_freetab(input.args);
}

static void		flag_init(t_flag *flag)
{
	flag->nl = 0;
	flag->rc = 0;
	flag->dt = 0;
}

static int		ls_dispatch(t_argstabs input)
{
	t_split		split;
	char		**roam;
	t_flag		flag;
	size_t		nb_arg;

	flag_init(&flag);
	split.dir = NULL;
	split.reg = NULL;
	nb_arg = tablen(input.args);
	input.args = sort_args(input.args, &input);
	if (!input.args)
		input.args = update_args(input.args, ".");
	split_args(input, &split);
	print_args(split.reg, input.opts, &flag);
	roam = split.dir;
	if (split.dir)
		while (*roam)
		{
			list(*roam++, input, flag, nb_arg);
			flag.nl = 1;
		}
	ft_freetab(split.dir);
	ft_freetab(split.reg);
	return (1);
}

int				main(int argc, char **argv)
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
