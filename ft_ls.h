/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:42:36 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/14 20:56:03 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "libft/libft.h"

typedef struct	s_argstabs
{
	char **args;
	char *opts;
}				t_argstabs;

/* parse.c */
int		parse(int argc, char **argv, char **opt_list, char ***arg_list);
char	**update_args(char **arg_list, char *n_arg);

/* util.c */
int		check_opt(char *opt_list, char **arg_list);
int		check_update(char ***tab1, char **tab2, char *roam, t_argstabs *input);
void	arg_free(char **arg_list, char *opt_list);


#endif
