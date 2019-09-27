/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:51:07 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/23 19:37:36 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*refill_options(char *opt_list, char *n_opt, char *n_list)
{
	size_t i;
	size_t j;

	i = 0;
	while (opt_list && i < ft_strlen(opt_list))
	{
		n_list[i] = opt_list[i];
		i++;
	}
	j = 1;
	while (j < ft_strlen(n_opt))
	{
		n_list[i] = n_opt[j];
		j++;
		i++;
	}
	n_list[i] = '\0';
	return (n_list);
}

static char	*update_options(char *opt_list, char *n_opt)
{
	char *n_list;

	if (!opt_list)
	{
		if (!(n_list = malloc(ft_strlen(n_opt) + 1)))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (!(n_list = malloc(ft_strlen(opt_list) + ft_strlen(n_opt) + 1)))
			exit(EXIT_FAILURE);
	}
	n_list = refill_options(opt_list, n_opt, n_list);
	if (opt_list)
		free(opt_list);
	return (n_list);
}

static char	**refill(char **arg_list, char *n_arg, char **n_list, size_t len)
{
	char **ptr;
	char **sav;

	ptr = n_list;
	sav = arg_list;
	while (len && *arg_list != NULL)
	{
		if (!(*ptr = ft_strdup(*arg_list)))
			exit(EXIT_FAILURE);
		arg_list++;
		ptr++;
	}
	*ptr = ft_strdup(n_arg);
	*(ptr + 1) = NULL;
	return (n_list);
}

char		**update_args(char **arg_list, char *n_arg)
{
	char	**n_list;
	size_t	tab_len;

	tab_len = ft_tablen(arg_list);
	if (!(n_list = malloc(sizeof(n_list) * (tab_len + 2))))
		exit(EXIT_FAILURE);
	n_list = refill(arg_list, n_arg, n_list, tab_len);
	ft_freetab(arg_list);
	return (n_list);
}

int			parse(int argc, char **argv, char **opt_list, char ***arg_list)
{
	int i;
	int stop_opt;

	i = 1;
	stop_opt = 0;
	while (i < argc)
	{
		if (!ft_strcmp("--", argv[i]) && stop_opt == 0)
		{
			stop_opt = 1;
			i++;
			continue ;
		}
		if (!stop_opt && argv[i][0] == '-' && ft_strlen(argv[i]) > 1)
			*opt_list = update_options(*opt_list, argv[i]);
		else
		{
			stop_opt = 1;
			*arg_list = update_args(*arg_list, argv[i]);
		}
		i++;
	}
	return (1);
}
