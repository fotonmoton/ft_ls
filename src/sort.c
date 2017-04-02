/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 03:13:59 by gtertysh          #+#    #+#             */
/*   Updated: 2017/04/02 03:14:03 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_content(t_list **del, t_flags *flgs)
{
	if (flgs->t)
	{
		if (flgs->u)
			ft_lst_merge_sort(del, by_a_time);
		ft_lst_merge_sort(del, by_m_time);
	}
	else if (flgs->abn)
		ft_lst_merge_sort(del, by_name_lex);
	else if (flgs->size)
		ft_lst_merge_sort(del, by_size);
	else
		ft_lst_merge_sort(del, by_name);
	if (flgs->r)
		ft_lst_rev(del);
}
