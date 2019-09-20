/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:42:36 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/20 17:25:47 by qbackaer         ###   ########.fr       */
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
	char			*path;
	struct stat		filestat;
	struct s_entry	*next;
}				t_entry;

typedef struct  s_cursors
{
	t_entry *wkst_c;
	t_entry *wkst_p;
	t_entry *curs_c;
	t_entry *curs_p;

}               t_cursors;

typedef struct	s_maxlen
{
	size_t		lnk_maxlen;
	size_t		uid_maxlen;
	size_t		grp_maxlen;
	size_t		size_maxlen;
}				t_maxlen;

/*print_args.c*/
int     print_args(char **reglist, char *opts);

/* parse.c */
int		parse(int argc, char **argv, char **opt_list, char ***arg_list);
char		**update_args(char **arg_list, char *n_arg);

/* sort_args.c */
int		sort_args(char ***raw, t_argstabs *input);

/* sort_ll.c */
t_entry                 *sort_ll(t_entry *lst, size_t ll_size, char *cwd, char *opts);

/* util.c */
int		check_opt(char *opt_list, char **arg_list);
int		check_update(char ***tab1, char **tab2, char *roam, t_argstabs *input);
void		arg_free(char **arg_list, char *opt_list);
char		*subdir_path(const char *current_path, const char *subdir);
long    get_time(char *path);

/* util2.c */
void        init_cursors(t_cursors *llc, t_entry *lst);
void        alpha_free_wpr(t_entry *entry, char *path);
int			is_tooold(time_t m_time);
char		*get_year(char *m_time);

/* ll_util.c */
t_entry		*ll_append_node(t_entry *ll_head, char *path, char *fname);
t_entry		*ll_push_node(t_entry *ll_head, char *path, char *fname);
void		ll_free(t_entry *ll_head);
void		ll_print(t_entry *head, char *opts);

/* ll_util2.c */
size_t		ll_size(t_entry *head);
size_t		count_ll_blocks(t_entry *head);
int			is_tooold(time_t m_time);
t_maxlen	get_len(struct stat filestat);
t_maxlen	get_maxlen(t_entry *entry);

/* list.c */
char		**ll_generate(t_entry **head, DIR *dir, char *path, char *opts);

/* display.c */
void	display_wpr(t_entry *entry, char *options, t_maxlen data);
void	display_entry(char *fname, struct stat *fstats, int l_mode, t_maxlen data);
void	format_time(char *r_time, int too_old);
void	format_size(long size, t_maxlen data);
void	format_link(int link, t_maxlen pad);
void	format_name(struct stat *fstat, t_maxlen pad);

/* getstat.c */
char	*get_usrname(uid_t user_id);
char	*get_grpname(gid_t group_id);
void	get_mode(mode_t file_mode);
void	get_type(char *buffer, mode_t file_mode);
void	get_perm(char *buffer, mode_t file_mode);

/* util_time.c */
char	*format_yun(char *r_time);
char	*format_old(char *r_time);

#endif
