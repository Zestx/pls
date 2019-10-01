/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:30:15 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/01 16:47:43 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	**copy_tab(char **args)
{
	char	**new;
	char	**arg_ptr;
	char	**new_ptr;
	size_t	max;

	if (!(new = malloc(sizeof(char**) * (ft_tablen(args) + 1))))
		exit(EXIT_FAILURE);
	new[ft_tablen(args)] = NULL;
	new_ptr = new;
	arg_ptr = args;
	max = get_argslen(args);
	while (*arg_ptr)
	{
		if (!(*new_ptr = malloc(sizeof(char) * (max + 1))))
			exit(EXIT_FAILURE);
		*new_ptr = ft_strcpy(*new_ptr, *arg_ptr);
		arg_ptr++;
		new_ptr++;
	}
	ft_freetab(args);
	return (new);
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
			swap_args(&args_ptr, &smaller, i);
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
			if (get_time(smaller) < get_time(args_ptr[j]))
				smaller = args_ptr[j];
			j++;
		}
		if (get_time(args_ptr[i]) != get_time(smaller))
			swap_args(&args_ptr, &smaller, i);
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
		exit(EXIT_FAILURE);
	sort[ft_tablen(args)] = NULL;
	while (i < ft_tablen(args) - 1)
		i++;
	while (j < ft_tablen(args))
		if (!(sort[j++] = ft_strdup(args[i--])))
		{
			ft_freetab(args);
			ft_freetab(sort);
			return (NULL);
		}
	ft_freetab(args);
	return (sort);
}

char		**sort_args(char **raw, t_argstabs *input)
{
	char	**tab;

	if (!raw)
		return (raw);
	tab = copy_tab(raw);
	alphasort_args(&tab);
	if (input->opts && ft_strchr(input->opts, 't'))
	{
		timesort_args(&tab);
		bubble_sort(&tab, ft_tablen(tab));
	}
	if (input->opts && ft_strchr(input->opts, 'r'))
		tab = revsort_args(tab);
	return (tab);
}
