/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 17:15:57 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/27 19:24:25 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	list_helper(char *path, t_argstabs input, t_flag flag, size_t nb_arg)
{
	if (flag.nl)
		ft_putchar('\n');
	if (nb_arg > 1 || ((input.opts &&
					ft_strchr(input.opts, 'R')) && flag.dt) || flag.rc == 1)
	{
		ft_putstr(path);
		ft_putendl(":");
	}
	else
		return ;
}

void	recursive_wpr(char **dt, t_argstabs input, t_flag flag, size_t nb_arg)
{
	char **roam;

	roam = dt;
	if (input.opts && ft_strchr(input.opts, 'R') && dt)
	{
		flag.rc = 1;
		while (*roam)
			list(*roam++, input, flag, nb_arg);
	}
}

void	split_helper(struct stat st_buff, char *opts,
		t_split *split, char **roam)
{
	if (S_ISDIR(st_buff.st_mode) &&
			(!opts || (opts && !ft_strchr(opts, 'd'))))
		split->dir = update_args(split->dir, *roam);
	else
		split->reg = update_args(split->reg, *roam);
}

int		utils(char **tmp, int swap)
{
	if (swap == 0)
		ft_putstr(*tmp);
	if (swap == 1)
		ft_putchar(',');
	if (swap == 2)
		free(*tmp);
	return (1);
}
