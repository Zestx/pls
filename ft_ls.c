/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:44:08 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/22 11:10:14 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	list(char *path, char *options)
{
	DIR		*dir;
	struct dirent *de;

	ft_putendl(path);
	dir = opendir(path);
	while ((de = readdir(dir)))
	{
		ft_putendl(de->d_name);
	}
	return (1);
}

static int	split_args(t_argstabs input, char ***dir_list, char ***reg_list)
{
	char **roam;
	struct stat	st_buff;

	roam = input.args;
	while (*roam)
	{
		if (stat(*roam, &st_buff))
		{
			perror("error: ");
			ft_freetab(*dir_list);
			ft_freetab(*reg_list);
			return (0);
		}
		if (S_ISDIR(st_buff.st_mode))
		{
			if (!(check_update(dir_list, *reg_list, *roam, &input)))
				return (0);
		}
		else
			if (!(check_update(reg_list, *dir_list, *roam, &input)))
				return (0);
		roam++;
	}
	return (1);
}

static int	ls_dispatch(t_argstabs input)
{
	char		**dir_list;
	char		**reg_list;
	char		**roam;

	dir_list = NULL;
	reg_list = NULL;
	if (!input.args)
	{
		list(".", input.opts);
		return (1);
	}
	split_args(input, &dir_list, &reg_list);
	ft_printab(reg_list);
	ft_putchar('\n');
	if (dir_list)
	{
		roam = dir_list;
		while (*roam)
		{
			list(*roam, input.opts);
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
	arg_free(input.args, input.opts);
	return (0);
}
