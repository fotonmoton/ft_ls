/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 03:12:44 by gtertysh          #+#    #+#             */
/*   Updated: 2017/04/02 03:13:40 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	reset_s_ls(t_ft_ls *s_ls)
{
	s_ls->max_cols_padd->group_col = 0;
	s_ls->max_cols_padd->name_col = 0;
	s_ls->max_cols_padd->link_col = 0;
	s_ls->max_cols_padd->size_mn_col = 0;
	s_ls->dir_content_total = 0;
}

void	print_content(t_ft_ls *s_ls, t_list *curr_dir_content, char *cur_path)
{
	if ((!s_ls->one_dir && !s_ls->no_ops) || s_ls->flgs->recur)
		print_full_path(s_ls, cur_path);
	output(s_ls, curr_dir_content);
}

void	ft_ls_fil(t_ft_ls *s_ls, t_list **files, char *path)
{
	sort_content(files, s_ls->flgs);
	print_content(s_ls, *files, path);
}

void	ft_ls_dir(t_ft_ls *s_ls, t_list *root, char *parent_dir)
{
	char		*cur_path;
	t_list		*curr_dir_content;
	t_list		*dirs;

	sort_content(&root, s_ls->flgs);
	reset_s_ls(s_ls);
	while (root)
	{
		cur_path = get_full_path(parent_dir,
								((t_dir_elm *)root->content)->elm_name);
		extract_content(cur_path, s_ls, &curr_dir_content);
		if (curr_dir_content)
			ft_ls_fil(s_ls, &curr_dir_content, cur_path);
		if (s_ls->flgs->recur)
		{
			find_dirs(cur_path, s_ls, curr_dir_content, &dirs);
			ft_ls_dir(s_ls, dirs, cur_path);
			free_struct_lst(&curr_dir_content);
		}
		free(cur_path);
		root = root->next;
	}
}
