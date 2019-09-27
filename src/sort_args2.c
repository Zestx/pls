/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:01:35 by srobin            #+#    #+#             */
/*   Updated: 2019/09/26 16:04:51 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	swap_args(char ***args, char **smaller, size_t i)
{
	char	*swaptmp;
	char	**args_ptr;

	args_ptr = *args;
	if (!(swaptmp = ft_strdup(args_ptr[i])))
		exit(EXIT_FAILURE);
	args_ptr[i] = ft_strcpy(args_ptr[i], *smaller);
	*smaller = ft_strcpy(*smaller, swaptmp);
	ft_sfree(swaptmp);
}

size_t	get_argslen(char **args)
{
	size_t	max;
	char	**roam;

	max = 0;
	roam = args;
	while (*roam)
	{
		if (ft_strlen(*roam) > max)
			max = ft_strlen(*roam);
		roam++;
	}
	return (max);
}
