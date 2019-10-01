/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:01:35 by srobin            #+#    #+#             */
/*   Updated: 2019/10/01 16:46:39 by qbackaer         ###   ########.fr       */
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

void	bubble_sort(char ***tab, size_t n)
{
	size_t		i;
	size_t		j;
	char		*tmp;

	j = 0;
	while (j < n - 1)
	{
		i = j + 1;
		while (i < n)
		{
			if ((ft_strcmp((*tab)[j], (*tab)[i]) > 0)
				&& (get_time((*tab)[j]) == get_time((*tab)[i])))
			{
				if (!(tmp = ft_strdup((*tab)[i])))
					exit(EXIT_FAILURE);
				ft_strcpy((*tab)[i], (*tab)[j]);
				ft_strcpy((*tab)[j], tmp);
				ft_sfree(tmp);
			}
			i++;
		}
		j++;
	}
}
