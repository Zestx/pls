/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 19:15:40 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/18 03:59:40 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	arg_free(char **arg_list, char *opt_list)
{
	ft_freetab(arg_list);
	ft_sfree(opt_list);
}

int		check_update(char ***tab1, char **tab2, char *roam, t_argstabs *input)
{
	if (!(*tab1 = update_args(*tab1, roam)))
	{
		ft_freetab(tab2);
		arg_free(input->args, input->opts);
		return (0);
	}
	return (1);
}

int     check_opt(char *opt_list, char **arg_list)
{
	char *roam;

	if (!opt_list)
		return (1);
	roam = opt_list;
	while (*roam != '\0')
	{
		if (!ft_strchr("alrtR", *roam))
		{
			ft_putstr("ft_ls: illegal option -- ");
			ft_putchar(*roam);
			ft_putchar('\n');
			ft_putendl("usage: ./ft_ls [-Ralrst] [file ...]");
			arg_free(arg_list, opt_list);
			return (0);
		}
		roam++;
	}
	return (1);
}
