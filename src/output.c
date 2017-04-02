/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 03:10:41 by gtertysh          #+#    #+#             */
/*   Updated: 2017/04/02 03:12:09 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_full_path(t_ft_ls *s_ls, char *path)
{
	char	*cur_dir_semi_n;
	char	*n_cur_dir;

	n_cur_dir = NULL;
	if (!s_ls->files_print)
	{
		if (s_ls->first_print)
		{
			s_ls->first_print = 0;
			cur_dir_semi_n = ft_strjoin(path, ":\n");
		}
		else
		{
			n_cur_dir = ft_strjoin("\n", path);
			cur_dir_semi_n = ft_strjoin(n_cur_dir, ":\n");
		}
		ft_putstr(cur_dir_semi_n);
		free(cur_dir_semi_n);
		free(n_cur_dir);
	}
}

void	one_line(t_list *lst_d_elm, t_ft_ls *s_ls)
{
	s_ls = 0;
	ft_putstr(((t_dir_elm *)lst_d_elm->content)->elm_name);
	if (lst_d_elm->next)
		ft_putstr("  ");
	else
		ft_putstr("\n");
}

void	one_column(t_list *lst_d_elm, t_ft_ls *s_ls)
{
	s_ls = 0;
	ft_putstr(((t_dir_elm *)lst_d_elm->content)->elm_name);
	ft_putstr("\n");
}

void	out(t_ft_ls *s_ls, t_list *cdc, void (*format_fun)(t_list *, t_ft_ls *))
{
	t_list		*lst_rnr;

	lst_rnr = cdc;
	while (lst_rnr)
	{
		if (s_ls->flgs->a)
			format_fun(lst_rnr, s_ls);
		else if (!is_hidden(((t_dir_elm *)lst_rnr->content)->elm_name))
			format_fun(lst_rnr, s_ls);
		lst_rnr = lst_rnr->next;
	}
}

void	output(t_ft_ls *s_ls, t_list *curr_dir_content)
{
	if (s_ls->flgs->l)
	{
		if (!s_ls->files_print)
			put_total(s_ls->dir_content_total / 2);
		out(s_ls, curr_dir_content, long_format);
	}
	else if (s_ls->flgs->col)
		out(s_ls, curr_dir_content, one_column);
	else
	{
		out(s_ls, curr_dir_content, one_line);
		if (s_ls->flgs->r)
			ft_putstr("\n");
	}
}
