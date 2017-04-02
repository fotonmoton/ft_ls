/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 06:31:57 by gtertysh          #+#    #+#             */
/*   Updated: 2017/04/02 06:31:59 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_struct_lst(t_list **curr_cont)
{
	t_dir_elm	*tmp;
	t_list		*tmp1;

	while (*curr_cont)
	{
		tmp1 = (*curr_cont)->next;
		if ((*curr_cont)->content)
		{
			tmp = (t_dir_elm *)(*curr_cont)->content;
			free(tmp->attr_str);
			free(tmp->link_name);
			free(tmp->elm_name);
			free(tmp->g_name);
			free(tmp->u_name);
			free(tmp->m_time);
			free(tmp->stat_copy);
			free(tmp);
		}
		free(*curr_cont);
		*curr_cont = tmp1;
	}
}

int		is_hidden(char *path)
{
	char	*begin;
	char	*end;

	begin = path;
	end = path + ft_strlen(path) - 1;
	if (begin != end)
	{
		while (end != begin && *end != '/')
			end--;
		if (end == begin)
		{
			if (*end == '.')
				return (1);
		}
		else if (*(end + 1) == '.')
			return (1);
	}
	else if (*end == '.')
		return (1);
	return (0);
}

char	*get_full_path(char *path, char *dir_ent_name)
{
	char *tmp;
	char *tmp1;

	if (dir_ent_name && path)
	{
		if (path[ft_strlen(path) - 1] == '/')
		{
			if (*dir_ent_name == '/')
				tmp = ft_strjoin(path, dir_ent_name + 1);
			else
				tmp = ft_strjoin(path, dir_ent_name);
		}
		else
		{
			tmp1 = ft_strjoin(path, "/");
			tmp = ft_strjoin(tmp1, dir_ent_name);
			free(tmp1);
		}
		return (tmp);
	}
	else
		return (ft_strdup(dir_ent_name));
}

void	file_node_init(t_dir_elm *de)
{
	de->stat_copy = NULL;
	de->link_name = NULL;
	de->attr_str = NULL;
	de->g_name = NULL;
	de->u_name = NULL;
	de->m_time = NULL;
	de->elm_name = NULL;
}
