/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 17:15:57 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/27 18:40:48 by qbackaer         ###   ########.fr       */
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
