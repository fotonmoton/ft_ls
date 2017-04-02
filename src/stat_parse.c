/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 03:08:48 by gtertysh          #+#    #+#             */
/*   Updated: 2017/04/02 03:08:50 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_padding_and_blocks(t_ft_ls *s_ls, t_dir_elm *d_elem)
{
	if (d_elem && s_ls && s_ls->flgs->l)
	{
		if (d_elem->cols_padd.link_col > s_ls->max_cols_padd->link_col)
			s_ls->max_cols_padd->link_col = d_elem->cols_padd.link_col;
		if (d_elem->cols_padd.name_col > s_ls->max_cols_padd->name_col)
			s_ls->max_cols_padd->name_col = d_elem->cols_padd.name_col;
		if (d_elem->cols_padd.group_col > s_ls->max_cols_padd->group_col)
			s_ls->max_cols_padd->group_col = d_elem->cols_padd.group_col;
		if (d_elem->cols_padd.size_mn_col > s_ls->max_cols_padd->size_mn_col)
			s_ls->max_cols_padd->size_mn_col = d_elem->cols_padd.size_mn_col;
		if (d_elem->stat_copy)
		{
			if (s_ls->flgs->a)
				s_ls->dir_content_total += d_elem->stat_copy->st_blocks * 2;
			else if (!is_hidden(d_elem->elm_name))
				s_ls->dir_content_total += d_elem->stat_copy->st_blocks * 2;
		}
	}
}

char	get_file_type(t_dir_elm *d_elm)
{
	char	ch;

	ch = '-';
	if (S_ISDIR(d_elm->stat_copy->st_mode))
		ch = 'd';
	if (S_ISLNK(d_elm->stat_copy->st_mode))
		ch = 'l';
	if (S_ISFIFO(d_elm->stat_copy->st_mode))
		ch = 'p';
	if (S_ISSOCK(d_elm->stat_copy->st_mode))
		ch = 's';
	if (S_ISBLK(d_elm->stat_copy->st_mode))
		ch = 'b';
	if (S_ISCHR(d_elm->stat_copy->st_mode))
		ch = 'c';
	return (ch);
}

void	get_file_permissions(char *attr_str, t_dir_elm *d_elm)
{
	struct stat	*st;
	char		r;
	char		w;
	char		x;
	char		f;

	r = 'r';
	w = 'w';
	x = 'x';
	f = '-';
	st = d_elm->stat_copy;
	attr_str[0] = (st->st_mode & S_IRUSR) ? r : f;
	attr_str[1] = (st->st_mode & S_IWUSR) ? w : f;
	attr_str[2] = (st->st_mode & S_IXUSR) ? x : f;
	attr_str[3] = (st->st_mode & S_IRGRP) ? r : f;
	attr_str[4] = (st->st_mode & S_IWGRP) ? w : f;
	attr_str[5] = (st->st_mode & S_IXGRP) ? x : f;
	attr_str[6] = (st->st_mode & S_IROTH) ? r : f;
	attr_str[7] = (st->st_mode & S_IWOTH) ? w : f;
	attr_str[8] = (st->st_mode & S_IXOTH) ? x : f;
}

char	*get_attr(t_dir_elm *d_elm)
{
	char	*attr_str;

	attr_str = ft_memalloc(sizeof(11));
	attr_str[10] = '\0';
	attr_str[0] = get_file_type(d_elm);
	get_file_permissions(attr_str + 1, d_elm);
	return (attr_str);
}

char	*get_time(t_dir_elm *d_elm)
{
	char	*time;
	char	*time_tmp;

	time_tmp = ctime(&(d_elm->stat_copy->st_mtimespec.tv_sec));
	time_tmp[16] = 0;
	time = ft_strdup(time_tmp + 4);
	return (time);
}
