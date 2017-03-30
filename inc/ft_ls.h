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

void				ft_ls(
						t_list *filenames,
						t_list *dir_paths,
						t_flags *flgs,
						char *par_dir);

int					parse_input(
						int ac,
						char **av,
						t_list **str_paths,
						t_flags *flgs);

void				init_dir_con_lst(
						t_list **dir_content_lst, t_list *filenames,
						t_flags *flgs, char *par_dir);

void				fill_path_lst(t_list **path_lst, char *path);
void				sort_elms(t_list **del, t_flags *flgs);
void				sort_dirs(t_list **dirs, t_flags *flgs);
void				output(t_list *del, char *current_dir, t_flags *flgs);
int					chck_flgs(char *flg, t_flags *flgs);
void				put_error(char *arg);

#endif
