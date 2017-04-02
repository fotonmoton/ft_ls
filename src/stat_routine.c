/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 06:33:59 by gtertysh          #+#    #+#             */
/*   Updated: 2017/04/02 06:34:00 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_columns_padd(t_dir_elm *de)
{
	de->cols_padd.link_col = ft_num_len(de->stat_copy->st_nlink);
	de->cols_padd.name_col = (int)ft_strlen(de->u_name);
	de->cols_padd.group_col = (int)ft_strlen(de->g_name);
	if (S_ISBLK(de->stat_copy->st_mode) ||
		S_ISCHR(de->stat_copy->st_mode))
	{
		de->cols_padd.size_mn_col = ft_num_len(major(de->stat_copy->st_rdev)) +
									ft_num_len(minor(de->stat_copy->st_rdev)) +
									2;
	}
	else
		de->cols_padd.size_mn_col = ft_num_len(de->stat_copy->st_size);
}

void	get_info_from_stat(t_dir_elm *dir_elm)
{
	dir_elm->attr_str = get_attr(dir_elm);
	dir_elm->u_name = ft_strdup(getpwuid(dir_elm->stat_copy->st_uid)->pw_name);
	dir_elm->g_name = ft_strdup(getgrgid(dir_elm->stat_copy->st_gid)->gr_name);
	dir_elm->m_time = get_time(dir_elm);
}

t_list	*read_stat(char *tmp_full_path, char *filename, t_ft_ls *s_ls)
{
	t_dir_elm		de;
	t_list			*dir_node;

	file_node_init(&de);
	de.elm_name = ft_strdup(filename);
	de.stat_copy = malloc(sizeof(struct stat));
	lstat(tmp_full_path, de.stat_copy);
	if (s_ls->flgs->l)
	{
		if (S_ISLNK(de.stat_copy->st_mode) && (de.link_name = ft_strnew(1024)))
		{
			if (readlink(tmp_full_path, de.link_name, PATH_MAX) == -1)
				put_error(0);
		}
		else
			de.link_name = NULL;
		get_info_from_stat(&de);
		set_columns_padd(&de);
	}
	dir_node = ft_lstnew(&de, sizeof(t_dir_elm));
	return (dir_node);
}

t_list	*init_read_stat(char *full_path, char *filename, t_ft_ls *s_ls)
{
	t_list	*dir_node;
	char	*tmp_file_path;

	tmp_file_path = get_full_path(full_path, filename);
	if (access(tmp_file_path, F_OK) == 0)
	{
		dir_node = read_stat(tmp_file_path, filename, s_ls);
		free(tmp_file_path);
		return (dir_node);
	}
	else
	{
		put_error(filename);
		free(tmp_file_path);
		return (NULL);
	}
}

t_list	*init_content_node(char *full_path, char *filename, t_ft_ls *s_ls)
{
	if (s_ls->flgs->a)
		return (init_read_stat(full_path, filename, s_ls));
	else if (!is_hidden(filename) || ft_strcmp(filename, ".") == 0)
		return (init_read_stat(full_path, filename, s_ls));
	return (NULL);
}
