/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:44:08 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/13 20:15:04 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	list(char *path)
{
	DIR				*dir;
	struct dirent	*de;

	if (!(dir = opendir(path)))
	{
		perror("error: ");
		return (0);
	}
	while ((de = readdir(dir)))
		ft_putendl(de->d_name);
	return (1);
}

int			main(int argc, char **argv)
{
	char *opt_list;
	char **arg_list;

	opt_list = NULL;
	arg_list = NULL;
	if (!parse(argc, argv, &opt_list, &arg_list))
	{
		arg_free(arg_list, opt_list);
		return (1);
	}
	if (!check_opt(opt_list, arg_list))
		return (1);
	list("/Users/xbackaer");
	ft_freetab(arg_list);
	ft_sfree(opt_list);
	return (0);
}
