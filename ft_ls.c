/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:44:08 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/18 04:04:03 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"



//check the input args and separate files from directories, then call list on them.
//to implement:  error checking and frees.
static int	ls_dispatch(t_argstabs input)
{
	char		**roam;
	char		**dir_list;
	char		**reg_list;
	struct stat	st_buff;

	dir_list = NULL;
	reg_list = NULL;
	if (!input.args)
	{
		// list home directory (".")
		return (1);
	}
	roam = input.args;
	while (*roam)
	{
		stat(*roam, &st_buff);
		if (S_ISDIR(st_buff.st_mode))
		{
			if (!(check_update(&dir_list, reg_list, *roam, &input)))
				return (0);
		}
		else
		{
			if (!(check_update(&reg_list, dir_list, *roam, &input)))
				return (0);
		}	
		roam++;
	}
	ft_putendl("files: ");
	ft_printab(reg_list);
	ft_putendl("directories: ");
	ft_printab(dir_list);
	//list all files from reg_list first, respecting options.
	//loop on reg_list and list their content.
	ft_freetab(dir_list);
	ft_freetab(reg_list);
	return (1);
}

//review error checking and frees.
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
	ft_putendl("input.opts:");
	ft_putendl(input.opts);
	ft_putendl("input.args:");
	ft_printab(input.args);
	ls_dispatch(input);
	arg_free(input.args, input.opts);
	return (0);
}
