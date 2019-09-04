/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:42:36 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/04 19:19:41 by qbackaer         ###   ########.fr       */
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
	char 			**args;
	char 			*opts;
}				t_argstabs;

typedef struct	s_entry
{
	char			*filename;
	struct stat		filestat;
	struct s_entry	*next;
}				t_entry;

/* parse.c */
int		parse(int argc, char **argv, char **opt_list, char ***arg_list);
char		**update_args(char **arg_list, char *n_arg);

/* sort_args.c */
int		sort_args(char ***raw, t_argstabs *input);

/* util.c */
int		check_opt(char *opt_list, char **arg_list);
int		check_update(char ***tab1, char **tab2, char *roam, t_argstabs *input);
void		arg_free(char **arg_list, char *opt_list);
char		*subdir_path(const char *current_path, const char *subdir);
char    *get_time(char *path);

/* ll_util.c */
t_entry		*ll_append_node(t_entry *ll_head, char *path, char *fname);
void		ll_free(t_entry *ll_head);
void		ll_print(t_entry *head, char *opts);

/* list.c */
char		**ll_generate(t_entry **head, DIR *dir, char *path, char *opts);

/* display.c */
void	display_wpr(t_entry *entry, char *options);
void	display_entry(char *fname, struct stat *fstats, int l_mode);
void	format_time(char *r_time);
void	format_size(int size);
void	format_link(int link);

/* getstat.c */
char	*get_usrname(uid_t user_id);
char	*get_grpname(gid_t group_id);
void	get_mode(mode_t file_mode);
void	get_type(char *buffer, mode_t file_mode);
void	get_perm(char *buffer, mode_t file_mode);

#endif
