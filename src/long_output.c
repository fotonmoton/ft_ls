/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 06:30:33 by gtertysh          #+#    #+#             */
/*   Updated: 2017/04/02 06:30:55 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	put_sp(int num)
{
	while (num--)
		ft_putstr(" ");
}

void	put_total(int total)
{
	ft_putstr("total");
	ft_putstr(" ");
	ft_putnbr(total);
	ft_putstr("\n");
}

void	put_link(t_dir_elm *d_elm)
{
	char *tmp_link;

	tmp_link = ft_strjoin(" -> ", d_elm->link_name);
	ft_putstr(tmp_link);
	free(tmp_link);
}

void	put_minor_major(t_dir_elm *d_elm)
{
	ft_putnbr(major(d_elm->stat_copy->st_rdev));
	ft_putstr(",");
	ft_putstr(" ");
	ft_putnbr(minor(d_elm->stat_copy->st_rdev));
}

void	long_format(t_list *lst_d_elm, t_ft_ls *s_ls)
{
	t_dir_elm	*de;

	de = (t_dir_elm *)lst_d_elm->content;
	ft_putstr(de->attr_str);
	put_sp(s_ls->max_cols_padd->link_col - de->cols_padd.link_col + 1);
	ft_putnbr((int)de->stat_copy->st_nlink);
	ft_putstr(" ");
	ft_putstr(de->u_name);
	put_sp(s_ls->max_cols_padd->name_col - de->cols_padd.name_col + 2);
	ft_putstr(de->g_name);
	put_sp(s_ls->max_cols_padd->group_col - de->cols_padd.group_col + 1);
	put_sp(s_ls->max_cols_padd->size_mn_col - de->cols_padd.size_mn_col + 2);
	if (S_ISBLK(de->stat_copy->st_mode) ||
		S_ISCHR(de->stat_copy->st_mode))
		put_minor_major(de);
	else
		ft_putnbr((int)de->stat_copy->st_size);
	ft_putstr(" ");
	ft_putstr(de->m_time);
	ft_putstr(" ");
	ft_putstr(de->elm_name);
	if (S_ISLNK(de->stat_copy->st_mode))
		put_link(de);
	ft_putstr("\n");
}
