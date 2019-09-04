/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:30:15 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/04 19:27:31 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	swap_args(char ***args, char **smaller, size_t i)
{
	char *swaptmp;
	char **args_ptr;

	args_ptr = *args;
	if (!(swaptmp = ft_strdup(args_ptr[i])))
	{
		ft_freetab(args_ptr);
		return (0);
	}
	ft_sfree(args_ptr[i]);
	if (!(args_ptr[i] = ft_strdup(*smaller)))
	{
		ft_freetab(args_ptr + 1);
		//		ft_freetab((args + i + 1);
		return (0);
	}
	ft_sfree(*smaller);
	if (!(*smaller = ft_strdup(swaptmp)))
	{
		//		ft_freetab(*(args + (*smaller - **args) + 1));
		ft_freetab(args_ptr);
		return (0);
	}
	ft_sfree(swaptmp);
	return (1);
}

static int	alphasort_args(char ***args)
{
	char	*smaller;
	char	**args_ptr;
	size_t	i;
	size_t	j;

	if (!*args)
		return (0);
	i = 0;
	while (ft_tablen(*args) > 1 && i < ft_tablen(*args) - 1)
	{
		args_ptr = *args;
		j = i + 1;
		smaller = args_ptr[i];
		while (j < ft_tablen(*args))
		{
			if (ft_strcmp(smaller, args_ptr[j]) > 0)
				smaller = args_ptr[j];
			j++;
		}
		if (ft_strcmp(args_ptr[i], smaller))
			if (!(swap_args(&args_ptr, &smaller, i)))
				return (0);
		i++;
	}
	return (1);
}

static int	timesort_args(char ***args)
{
	char	*smaller;
	char	**args_ptr;
	size_t	i;
	size_t	j;

	if (!*args)
		return (0);
	i = 0;
	while (ft_tablen(*args) > 1 && i < ft_tablen(*args) - 1)
	{
		args_ptr = *args;
		j = i + 1;
		smaller = args_ptr[i];

		while (j < ft_tablen(*args))
		{
			if (ft_strcmp(get_time(smaller), get_time(args_ptr[j])) < 0)
				smaller = args_ptr[j];
			j++;

		}
		if (ft_strcmp(get_time(args_ptr[i]), smaller))
			if (!(swap_args(&args_ptr, &smaller, i)))
				return (0);
		i++;
	}
	return (1);
}

static char	**revsort_args(char **args)
{
	char	**sort;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!args)
		return (NULL);
	if (!(sort = malloc(sizeof(sort) * (ft_tablen(args) + 1))))
	{
		free(args);
		return (NULL);
	}
	sort[ft_tablen(args)] = NULL;
	while (i < ft_tablen(args) - 1)
		i++;
	while (j < ft_tablen(args))
	{
		if (!(sort[j++] = ft_strdup(args[i--])))
		{
			ft_freetab(args);
			ft_freetab(sort);
			return (NULL);
		}
	}
	ft_freetab(args);
	return (sort);
}

int			sort_args(char ***raw, t_argstabs *input)
{
	if (input->opts && ft_strchr(input->opts, 't'))
	{
		if (!(timesort_args(&*raw)))
			return (0);
	}
	else if (!(alphasort_args(&*raw)))
	{
		ft_freetab(input->args);
		ft_sfree(input->opts);
		return (0);
	}
	if (input->opts && ft_strchr(input->opts, 'r'))
	{
		if (!(*raw = revsort_args(*raw)))
		{
			ft_freetab(input->args);
			ft_sfree(input->opts);
			return (0);
		}
	}
	return (1);
}
