/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:44:08 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/12 18:10:14 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	char *opt_table;
	char **dir_table;

	opt_table = NULL;
	dir_table = NULL;
	if (!parse(argc, argv, &opt_table, &dir_table))
		return (1);
	printf("options: [%s]\n", opt_table);
	ft_printab(dir_table);
	return (0);
}
