/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
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

# define FILES		0
# define DIRS		1

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

typedef struct 		s_dir_elm
{
	char 			*elm_name;
	char 			*parent_dir;
	char 			*a_time_str;
	int 			size;
	char 			*g_name;
	char 			*u_name;
	int 			links;
	char 			*attr_str;
	int 			link_fd;
	struct stat		*stat_buf_struc;
	t_flags			*flags;
}					t_dir_elm;

typedef struct 		s_ft_ls
{
	t_list			*lst_fil_names;
	t_list			*lst_dir_paths;
	t_list			*lst_fil_meta;
	int 			one_dir;
	int 			no_ops;
	int 			first_print;
	t_flags			*flgs;
}					t_ft_ls;

void				ft_ls(t_ft_ls *s_ls);

void 				ft_ls_fil(t_ft_ls *s_ls, char *full_path);

void				ft_ls_dir(t_ft_ls *s_ls, char *full_path);

int					parse_input(int ac, char **av, t_ft_ls *ft_ls_strct);

void				init_file_meta_lst(t_ft_ls *s_ls, char *full_path);

void				fill_path_lst(t_list **path_lst, char *path);
void				sort_files(t_list **del, t_flags *flgs);
void				sort_dirs(t_list **dirs, t_flags *flgs);

void				output(t_ft_ls *s_ls);
void				print_full_path(t_ft_ls *s_ls, char *path);

int					chck_flgs(char *flg, t_flags *flgs);
void				put_error(char *arg);

#endif
