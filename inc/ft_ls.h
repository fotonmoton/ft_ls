/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_dir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 18:27:54 by gtertysh          #+#    #+#             */
/*   Updated: 2017/03/25 21:18:30 by gtertysh         ###   ########.fr       */
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

typedef struct 		s_flags
{
	int 			l;
	int 			a;
	int 			R;
	int 			r;
	int 			t;
	int 			col;
	int 			abn;
}					t_flags;

typedef struct 		s_col_len
{
	int 			link_col;
	int 			name_col;
	int 			size_col;
	int 			group_col;
}					t_col_len;


typedef struct 		s_dir_elm
{
	char 			*elm_name;
	char 			*link_name;
	char 			*m_time;
	char 			*g_name;
	char 			*u_name;
	char 			*attr_str;
	struct stat		*stat_copy;
	t_col_len		cols_padd;
}					t_dir_elm;

typedef struct 		s_ft_ls
{
	t_flags			*flgs;
	t_col_len		*max_cols_padd;
	int 			dir_content_total;
	int 			one_dir;
	int 			no_ops;
	int 			first_print;
	int 			files_print;
}					t_ft_ls;

void				ft_ls_dir(t_ft_ls *s_ls, t_list *root, char *parent_dir);
void				ft_ls_fil(t_ft_ls *s_ls, t_list *root);

t_list				*operands_parse(t_list *ops, t_ft_ls *s_ls);

void				print_content(t_ft_ls *s_ls, t_list *curr_dir_content,
								  char *cur_path);

int					parse_input(int ac, char **av, t_list **file_and_dirs,
								   t_flags *flgs);

t_list				*init_content_node(char *full_path, char *filename,
										 t_ft_ls *s_ls);

void				fill_path_lst(t_list **path_lst, char *path);
void				sort_content(t_list **del, t_flags *flgs);
void				sort_paths(t_list **paths);

void				output(t_ft_ls *s_ls, t_list *curr_dir_content);
void				print_full_path(t_ft_ls *s_ls, char *path);

int					chck_flgs(char *flg, t_flags *flgs);
void				put_error(char *arg);

#endif
