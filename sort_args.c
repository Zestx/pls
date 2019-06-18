/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:30:15 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/18 04:04:04 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char **swap_args(char ***args, char **smaller, int i)
{
	char *swaptmp;

	if (!(swaptmp = ft_strdup(*args[i])))
	{
		ft_freetab(*args);
		return (NULL);
	}
	ft_sfree(*args[i]);
	if (!(*args[i] = ft_strdup(*smaller)))
	{
		ft_freetab(*(args + 1));
		ft_freetab(*(args + i + 1));
		return (NULL);
	}
	ft_sfree(*smaller);
	if (!(*smaller = ft_strdup(swaptmp)))
	{
		ft_freetab(*(args + (*smaller - **args) + 1));
		ft_freetab(*args);
		return (NULL);
	}
	ft_sfree(swaptmp);
	return (*args);
}

static char	**alphasort_args(char **args)
{
	char	*smaller;
	char	*swaptmp;
	size_t	i;
	size_t	j;

	if (!args)
		return (NULL);
	i = 0;
	while (i < ft_tablen(args) - 1)
	{
		j = i + 1;
		smaller = args[i];
		while (j < ft_tablen(args))
		{
			if (ft_strcmp(args[j], smaller) > 0)
				smaller = args[j];
			j++;
		}
		if(!swap_args(&args, &smaller, i))
			return (NULL);
		i++;
	}
	return (args);
}

static char **revsort_args(char **args)
{
	char **sort;
	char **roam_args;
	char **roam_sort;

	if (!args)
		return (NULL);
	if (!(sort = malloc(sizeof(sort) * (ft_tablen(args) + 1))))
	{
		free(args);
		return (NULL);
	}
	roam_args = args;
	while (*roam_args)
		roam_args++;
	roam_sort = sort;
	while (*roam_sort)
	{
		if (!(*roam_sort = ft_strdup(*roam_args)))
		{
			ft_freetab(args);
			ft_freetab(sort);
			return (NULL);
		}
		roam_args--;
		roam_sort++;
	}
	free(args);
	return (sort);
}

//sort the input args before dispatching them, depending on options (t,r)
int			sort_args(t_argstabs *input)
{
	if (!(input->args = alphasort_args(input->args)))
	{
		ft_sfree(input->opts);
		return (0);
	}
/*	if (ft_strchr(input->opts, 't'))
	{
		if (!(input->args = timesort_args(input->args)))
		{
			ft_sfree(input->opts);
			return (0);
		}
	} */
	if (ft_strchr(input->opts, 'r'))
	{
		if (!(input->args = revsort_args(input->args)))
		{
			ft_sfree(input->opts);
			return (0);
		}
	}
	return (1);
}
