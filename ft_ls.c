/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:44:08 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/12 19:40:10 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	char *opt_list;
	char **arg_list;

	opt_list = NULL;
	arg_list = NULL;
	if (!parse(argc, argv, &opt_list, &arg_list))
	{
		ft_putendl("memory error");
		arg_free(arg_list, opt_list);
		return (1);
	}
	if (!check_opt(opt_list, arg_list))
		return (1);
	ft_freetab(arg_list);
	ft_sfree(opt_list);
	return (0);
}
