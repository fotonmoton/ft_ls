/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_dir.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 18:27:54 by gtertysh          #+#    #+#             */
/*   Updated: 2017/04/02 06:52:30 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <sys/types.h>
# include <errno.h>
# include <limits.h>

# define FILS 0
# define DIRS 1

typedef struct		s_flags
{
	int				l;
	int				a;
	int				recur;
	int				size;
	int				r;
	int				t;
	int				u;
	int				col;
	int				abn;
}					t_flags;

typedef struct		s_col_len
{
	int				link_col;
	int				name_col;
	int				size_mn_col;
	int				group_col;
}					t_col_len;

typedef struct		s_dir_elm
{
	char			*elm_name;
	char			*link_name;
	char			*m_time;
	char			*g_name;
	char			*u_name;
	char			*attr_str;
	struct stat		*stat_copy;
	t_col_len		cols_padd;
}					t_dir_elm;

typedef struct		s_ft_ls
{
	t_flags			*flgs;
	t_col_len		*max_cols_padd;
	int				dir_content_total;
	int				one_dir;
	int				no_ops;
	int				first_print;
	int				files_print;
}					t_ft_ls;

void				ft_ls_dir(t_ft_ls *s_ls, t_list *root, char *parent_dir);
void				ft_ls_fil(t_ft_ls *s_ls, t_list **files, char *path);
void				extract_content(char *full_path, t_ft_ls *s_ls,
									t_list **dir_content);
void				find_dirs(char *full_path, t_ft_ls *s_ls,
									t_list *cur_dir_con, t_list **dirs);
t_list				*operands_parse(t_list *ops, t_ft_ls *s_ls);

int					parse_input(int ac, char **av, t_list **file_and_dirs,
									t_flags *flgs);

t_list				*init_content_node(char *full_path, char *filename,
									t_ft_ls *s_ls);

void				get_padding_and_blocks(t_ft_ls *s_ls, t_dir_elm *d_elem);
char				*get_time(t_dir_elm *d_elm);
char				*get_attr(t_dir_elm *d_elm);

void				sort_content(t_list **del, t_flags *flgs);
int					by_name_lex(t_dir_elm *a, t_dir_elm *b);
int					by_name(t_dir_elm *a, t_dir_elm *b);
int					by_size(t_dir_elm *a, t_dir_elm *b);
int					by_m_time(t_dir_elm *a, t_dir_elm *b);
int					by_a_time(t_dir_elm *a, t_dir_elm *b);

void				output(t_ft_ls *s_ls, t_list *curr_dir_content);
void				long_format(t_list *lst_d_elm, t_ft_ls *s_ls);
void				put_total(int total);
void				print_content(t_ft_ls *s_ls, t_list *curr_dir_content,
									char *cur_path);

void				print_full_path(t_ft_ls *s_ls, char *path);
void				fill_path_lst(t_list **path_lst, char *path);
int					chck_flgs(char *flg, t_flags *flgs);
void				put_error(char *arg);
void				free_struct_lst(t_list **curr_cont);
char				*get_full_path(char *path, char *dir_ent_name);
void				file_node_init(t_dir_elm *de);
int					is_hidden(char *path);

#endif
