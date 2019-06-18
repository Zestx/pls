/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:30:15 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/18 06:46:25 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char **swap_args(char ***args, char **smaller, int i)
{
	char *swaptmp;

	printf("ARGS[i]: [%s]\n", *args[i]);
	if (!(swaptmp = ft_strdup(*args[i])))
	{
		ft_freetab(*args);
		return (NULL);
	}
	printf("OK0\n");
	ft_sfree(*args[i]);
	if (!(*args[i] = ft_strdup(*smaller)))
	{
		ft_freetab(*(args + 1));
		ft_freetab(*(args + i + 1));
		return (NULL);
	}
	printf("OK1\n");
	ft_sfree(*smaller);
	if (!(*smaller = ft_strdup(swaptmp)))
	{
		ft_freetab(*(args + (*smaller - **args) + 1));
		ft_freetab(*args);
		return (NULL);
	}
	printf("OK2\n");
	ft_sfree(swaptmp);
	printf("ENDSWAP\n");
	return (*args);
}

static char	**alphasort_args(char **args)
{
	char	*smaller;
	size_t	i;
	size_t	j;

	printf("ALPHASORT, tablen %zu\n", ft_tablen(args));
	if (!args)
		return (NULL);
	i = 0;
	while (ft_tablen(args) > 1 && i < ft_tablen(args) - 1)
	{
		printf("---> LOOP\n");
		ft_printab(args);
		j = i + 1;
		printf("	init: %s\n", args[j]);
		smaller = args[i];
		while (j < ft_tablen(args))
		{
			printf("-------> loop\n");
			if (ft_strcmp(smaller, args[j]) > 0)
			{
				printf("smaller!\n");
				smaller = args[j];
			}
			j++;
		}
		printf("SMALLEST: %s\n", smaller);
		if(!swap_args(&args, &smaller, i))
			return (NULL);
		i++;
	}
	printf("END ALPHASORT\n");
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

//sort the input lists before dispatching them, depending on options:
//by default alphebtical sorting, if (t option) then by time and /or 
//reversed (r option). Doesn't work well right now.
//sorting is done using the selection sort algorithm:
//https://www.geeksforgeeks.org/program-to-sort-an-array-of-strings-using-selection-sort/
//!\ le triage alpha et par temps sont faits en place. le triage en reverse est fait sur une copie,
//mais dans tout les cas le selectin sort est utilise.
int			sort_args(char ***raw, t_argstabs *input)
{
/*	if (ft_strchr(input->opts, 't'))
	{
		if (!(input->args = timesort_args(input->args)))
		{
			ft_sfree(input->opts);
			return (0);
		}
	} */
	if (!(*raw = alphasort_args(*raw)))
	{
		ft_freetab(input->args);
		ft_sfree(input->opts);
		return (0);
	}
	if (ft_strchr(input->opts, 'r'))
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
