/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 19:15:40 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/13 18:08:12 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	arg_free(char **arg_list, char *opt_list)
{
	ft_freetab(arg_list);
	ft_sfree(opt_list);
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
			ft_putendl("ft_ls: illegal option -- ");
			ft_putchar(*roam);
			ft_putchar('\n');
			arg_free(arg_list, opt_list);
			return (0);
		}
		roam++;
	}
	return (1);
}
