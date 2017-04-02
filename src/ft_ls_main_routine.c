/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_main_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 06:28:59 by gtertysh          #+#    #+#             */
/*   Updated: 2017/04/02 06:29:28 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	find_dirs(char *full_path, t_ft_ls *s_ls, t_list *cur_dir_con,
														t_list **dirs)
{
	char		*full_path_with_file;
	t_dir_elm	*dir_elm;

	*dirs = NULL;
	while (cur_dir_con)
	{
		dir_elm = (t_dir_elm *)cur_dir_con->content;
		full_path_with_file = get_full_path(full_path, dir_elm->elm_name);
		if ((S_ISDIR(dir_elm->stat_copy->st_mode)) &&
				(ft_strcmp(dir_elm->elm_name, ".") != 0) &&
				(ft_strcmp(dir_elm->elm_name, "..") != 0))
		{
			if (access(full_path_with_file, F_OK) != 0)
				put_error(full_path_with_file);
			else if (s_ls->flgs->a)
				ft_lstadd(dirs, ft_lstnew(dir_elm, sizeof(t_dir_elm)));
			else if (*dir_elm->elm_name != '.')
				ft_lstadd(dirs, ft_lstnew(dir_elm, sizeof(t_dir_elm)));
		}
		cur_dir_con = cur_dir_con->next;
		free(full_path_with_file);
	}
}

void	extract_content(char *full_path, t_ft_ls *s_ls, t_list **dir_content)
{
	DIR				*dp;
	struct dirent	*de;
	t_list			*lst_elm;

	*dir_content = NULL;
	if ((dp = opendir(full_path)))
	{
		while ((de = readdir(dp)))
		{
			if ((lst_elm = init_content_node(full_path, de->d_name, s_ls)))
			{
				get_padding_and_blocks(s_ls, lst_elm->content);
				ft_lstadd(dir_content, lst_elm);
			}
		}
		closedir(dp);
	}
}
