/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:42:36 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/01 15:38:03 by qbackaer         ###   ########.fr       */
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
# include "../libft/libft.h"

typedef struct		s_argstabs
{
	char			**args;
	char			*opts;
}					t_argstabs;

typedef struct		s_entry
{
	char			*filename;
	char			*path;
	struct stat		filestat;
	struct s_entry	*next;
}					t_entry;

typedef struct		s_cursors
{
	t_entry			*wkst_c;
	t_entry			*wkst_p;
	t_entry			*curs_c;
	t_entry			*curs_p;

}					t_cursors;

typedef struct		s_maxlen
{
	size_t			lnk_maxlen;
	size_t			uid_maxlen;
	size_t			grp_maxlen;
	size_t			size_maxlen;
	size_t			ino_maxlen;
}					t_maxlen;

typedef struct		s_flag
{
	int				nl;
	int				rc;
	int				dt;
}					t_flag;

typedef struct		s_split
{
	char			**dir;
	char			**reg;
}					t_split;

/*
**	ft_ls.c
*/
int					list(char *path, t_argstabs input, t_flag flag,
					size_t nb_arg);

/*
**	print_args.c
*/
int					print_args(char **reglist, char *opts, t_flag *flag);

/*
**	parse.c
*/
int					parse(int argc, char **argv, char **opt_list,
					char ***arg_list);
char				**update_args(char **arg_list, char *n_arg);

/*
**	sort_args.c
*/
char				**sort_args(char **raw, t_argstabs *input);

/*
**	sort_args2.c
*/
void				swap_args(char ***args, char **smaller, size_t i);
size_t				get_argslen(char **args);
void				bubble_sort(char ***tab, size_t tablen);

/*
**	sort_ll.c
*/
t_entry				*sort_ll(t_entry *lst, size_t ll_size,
					char *cwd, char *opts);

/*
**	util.c
*/
int					check_opt(char *opt_list, char **arg_list);
int					check_update(char ***tab1, char **tab2,
					char *roam, t_argstabs *input);
void				arg_free(char **arg_list, char *opt_list);
char				*subdir_path(const char *current_path, const char *subdir);

/*
**	 util2.c
*/
void				init_cursors(t_cursors *llc, t_entry *lst);
void				alpha_free_wpr(t_entry *entry, char *path);
int					is_tooold(time_t m_time);
char				*get_year(char *m_time);
size_t				tablen(char **tab);

/*
**	ll_util.c
*/
t_entry				*ll_append_node(t_entry *ll_head, char *path, char *fname);
t_entry				*ll_push_node(t_entry *ll_head, char *path, char *fname);
void				ll_free(t_entry *ll_head);
void				ll_print(t_entry *head, char *opts);

/*
**	ll_util2.c
*/
size_t				count_ll_blocks(t_entry *head);
int					is_tooold(time_t m_time);
t_maxlen			get_maxlen(t_entry *entry);

/*
**	ll_util3.c
*/
size_t				ll_size(t_entry *head);
t_maxlen			get_len(struct stat filestat);
void				compare_max(size_t *max, size_t check);

/*
**	list.c
*/
char				**ll_gen(t_entry **head, DIR *dir,
					char *path, char *opts);

/*
**	display.c
*/
void				display_entry(char *fname, struct stat *fstats,
					int l, t_maxlen data);
void				format_time(char *r_time, int too_old);
void				format_size(long size, size_t maxlen);
void				format_link(int link, t_maxlen pad);
void				format_name(struct stat *fstat, t_maxlen pad);

/*
**	display2.c
*/
void				display_wpr(t_entry *ent, char *opts, t_maxlen pad);
void				display_entry_l(t_entry *ent, struct stat *fstats,
					int l, t_maxlen pad);
void				print_fname(char *fname, char *path, struct stat *fstats);
int					print_minormajor(struct stat *fstats, t_maxlen ml);
void				print_inode(long size, t_maxlen pad, char *opts);

/*
**	display3.c
*/
void				list_helper(char *path, t_argstabs input, t_flag flag,
					size_t nb_arg);
void				recursive_wpr(char **dirtab, t_argstabs input, t_flag flag,
					size_t nb_arg);
void				split_helper(struct stat st_buff, char *opts,
					t_split *split, char **roam);
int					utils(char **tmp, int swap);

/*
**	getstat.c
*/
char				*get_usrname(uid_t user_id);
char				*get_grpname(gid_t group_id);
void				get_mode(mode_t file_mode);
void				get_type(char *buffer, mode_t file_mode);
void				get_perm(char *buffer, mode_t file_mode);

/*
**	util_time.c
*/
char				*format_yun(char *r_time);
char				*format_old(char *r_time);
long				get_time(char *path);
long				get_time_ll(struct stat fstat);

/*
**	args_max.c
*/
t_maxlen			get_maxlen_args(char **args);
void				init_size(t_maxlen *ml);

#endif
