/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:44:08 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/26 20:46:29 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	list(char *path, t_argstabs input, t_flag flag, size_t nb_arg)
{
	DIR				*dir;
	t_entry			*entries;
	t_entry			*sorted;
	char			**dirtab;
	char			**roam;
	
	if (!(dir = opendir(path)))
	{
		perror(path);
		return (0);
	}
	entries = NULL;
	dirtab = sort_args(ll_generate(&entries, dir, path, input.opts), &input);
	ft_printab(dirtab);
	sorted = sort_ll(entries, ll_size(entries), path, input.opts);
	if (flag.nl)
		ft_putchar('\n');
	if (nb_arg > 1 || ((input.opts && ft_strchr(input.opts, 'R')) && dirtab) || flag.rc == 1)
	{
		ft_putstr(path);
		ft_putendl(":");
	}
	flag.nl = 1;
	ll_print(sorted, input.opts);
	ll_free(sorted);
	roam = dirtab;
	if (input.opts && ft_strchr(input.opts, 'R') && dirtab)
	{
		flag.rc = 1;
		while (*roam)
			list(*roam++, input, flag, nb_arg);
	}
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

static void		flag_init(t_flag *flag)
{
	flag->nl = 0;
	flag->rc = 0;
}

static int		ls_dispatch(t_argstabs input)
{
	char		**dir_list;
	char		**reg_list;
	char		**roam;
	t_flag		flag;
	size_t		nb_arg;

	flag_init(&flag);
	dir_list = NULL;
	reg_list = NULL;
	nb_arg = tablen(input.args);
	input.args = sort_args(input.args, &input);
	if (!input.args)
		input.args = update_args(input.args, ".");
	split_args(input, &dir_list, &reg_list);
	if (print_args(reg_list, input.opts))
		flag.nl = 1;
	roam = dir_list;
	if (dir_list)
		while (*roam)
		{
			list(*roam++, input, flag, nb_arg);
			flag.nl = 1;
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
