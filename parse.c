/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:51:07 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/12 18:14:40 by qbackaer         ###   ########.fr       */
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
		if (!(n_list = malloc(ft_strlen(opt_list) + 1)))
			return (NULL);
	}
	else
	{
		if (!(n_list = malloc(ft_strlen(opt_list) + ft_strlen(n_opt) + 1)))
			return (NULL);
	}
	n_list = refill_options(opt_list, n_opt, n_list);
	if (opt_list)
		free(opt_list);
	return (n_list);
}

static char	**refill_args(char **arg_list, char *n_arg, char **n_list, size_t tab_len)
{
	char **ptr;
	char **sav;

	ptr = n_list;
	sav = arg_list;
	while (tab_len && *arg_list != NULL)
	{
		if (!(*ptr = ft_strdup(*arg_list)))
			return (NULL); //free if necessary and exit.
		arg_list++;
		ptr++;
	}
	*ptr = ft_strdup(n_arg);
	*(ptr + 1) = NULL;
	ft_freetab(sav); //free arg_list
	return (n_list);
}

static char	**update_args(char **arg_list, char *n_arg)
{
	char	**n_list;
	size_t	arg_len;
	size_t	tab_len;

	arg_len = ft_strlen(n_arg);
	tab_len = ft_tablen(arg_list);
	if (!(n_list = malloc(sizeof(n_list) * (tab_len + 2))))
		return (NULL);
	n_list = refill_args(arg_list, n_arg, n_list, tab_len);
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
		if (!stop_opt && argv[i][0] == '-')
		{
			if (!(*opt_list = update_options(*opt_list, argv[i])))
				return (0); //free opt_table, dir_table, exit_failure
		}
		else if (!(*arg_list = update_args(*arg_list, argv[i])))
			return (0); //free opt_table, dir_table, exit_failure
		i++;
	}
	return (1);
}
