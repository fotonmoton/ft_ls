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

typedef struct 		s_flags
{
	int 			l;
	int 			a;
	int 			R;
	int 			t;
	int 			col;
}					t_flags;

typedef struct 		s_dir_entity
{
	char 			*name;
	char 			*a_time;
	int 			size;
	char 			*g_name;
	char 			*u_name;
	int 			links;
	char 			*attr;
	int 			link_fd;
	struct dirent	*dirent;
	struct stat		*stat_buf;
	t_flags			*flags;
}					t_dir_entity;

#endif
