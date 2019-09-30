/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 19:15:40 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/30 18:05:59 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*subdir_path(const char *current_path, const char *subdir)
{
	char	*full_path;
	int		i;
	int		j;

	if (!(full_path = malloc(ft_strlen(current_path) + ft_strlen(subdir) + 2)))
		exit(EXIT_FAILURE);
	i = 0;
	while (current_path[i] != '\0')
	{
		full_path[i] = current_path[i];
		i++;
	}
	if (!(full_path[i - 1] == '/'))
	{
		full_path[i] = '/';
		i++;
	}
	j = 0;
	while (subdir[j] != '\0')
	{
		full_path[i + j] = subdir[j];
		j++;
	}
	full_path[i + j] = '\0';
	return (full_path);
}

void	arg_free(char **arg_list, char *opt_list)
{
	ft_freetab(arg_list);
	ft_sfree(opt_list);
}

int		check_update(char ***tab1, char **tab2, char *roam, t_argstabs *input)
{
	if (!(*tab1 = update_args(*tab1, roam)))
	{
		ft_freetab(tab2);
		arg_free(input->args, input->opts);
		return (0);
	}
	return (1);
}

int		check_opt(char *opt_list, char **arg_list)
{
	char *roam;

	if (!opt_list)
		return (1);
	roam = opt_list;
	while (*roam != '\0')
	{
		if (!ft_strchr("Radilrt", *roam))
		{
			ft_putstr("ft_ls: illegal option -- ");
			ft_putchar(*roam);
			ft_putchar('\n');
			ft_putendl("usage: ./ft_ls [-Radilrt] [file ...]");
			arg_free(arg_list, opt_list);
			return (0);
		}
		roam++;
	}
	return (1);
}
