/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 06:34:52 by gtertysh          #+#    #+#             */
/*   Updated: 2017/04/02 06:37:10 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		by_name_lex(t_dir_elm *a, t_dir_elm *b)
{
	if (ft_strcmp_lex(a->elm_name, b->elm_name) <= 0)
		return (1);
	return (0);
}

int		by_name(t_dir_elm *a, t_dir_elm *b)
{
	if (ft_strcmp(a->elm_name, b->elm_name) <= 0)
		return (1);
	return (0);
}

int		by_size(t_dir_elm *a, t_dir_elm *b)
{
	if (a->stat_copy->st_size > b->stat_copy->st_size)
		return (1);
	return (0);
}

int		by_m_time(t_dir_elm *a, t_dir_elm *b)
{
	long	dif;

	dif = a->stat_copy->st_mtimespec.tv_sec - b->stat_copy->st_mtimespec.tv_sec;
	if (!dif)
		dif = a->stat_copy->st_mtimespec.tv_nsec -
				b->stat_copy->st_mtimespec.tv_nsec;
	if (dif < 0)
		return (0);
	else if (dif > 0)
		return (1);
	else
		return (by_name(a, b));
}

int		by_a_time(t_dir_elm *a, t_dir_elm *b)
{
	long	dif;

	dif = a->stat_copy->st_atimespec.tv_sec - b->stat_copy->st_atimespec.tv_sec;
	if (!dif)
		dif = a->stat_copy->st_atimespec.tv_nsec -
				b->stat_copy->st_atimespec.tv_nsec;
	if (dif < 0)
		return (0);
	else if (dif > 0)
		return (1);
	else
		return (by_name(a, b));
}
