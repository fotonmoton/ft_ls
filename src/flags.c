/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 06:24:44 by gtertysh          #+#    #+#             */
/*   Updated: 2017/04/02 06:28:32 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		chck_long_flgs(char *flg, t_flags *flgs)
{
	if (*(flg + 1) && (flg += 1))
	{
		if (flgs->abn == 0)
			flgs->abn = (ft_strcmp(flg, "lex") == 0) ? 1 : 0;
		return (0);
	}
	return (1);
}

void	chck_short_flgs(char *flg, t_flags *flgs)
{
	if (flgs->size == 0)
		flgs->size = (ft_strchr(flg, 'S') != NULL) ? 1 : 0;
	if (flgs->l == 0)
		flgs->l = (ft_strchr(flg, 'l') != NULL) ? 1 : 0;
	if (flgs->a == 0)
		flgs->a = (ft_strchr(flg, 'a') != NULL) ? 1 : 0;
	if (flgs->recur == 0)
		flgs->recur = (ft_strchr(flg, 'R') != NULL) ? 1 : 0;
	if (flgs->t == 0)
		flgs->t = (ft_strchr(flg, 't') != NULL) ? 1 : 0;
	if (flgs->r == 0)
		flgs->r = (ft_strchr(flg, 'r') != NULL) ? 1 : 0;
	if (flgs->u == 0)
		flgs->u = (ft_strchr(flg, 'u') != NULL) ? 1 : 0;
	if (flgs->col == 0)
		flgs->col = (ft_strchr(flg, '1') != NULL) ? 1 : 0;

}

int		chck_flgs(char *flg, t_flags *flgs)
{
	if (*flg == '-' && *(flg + 1) && (flg += 1))
	{
		if (*(flg) == '-')
		{
			if (!chck_long_flgs(flg, flgs))
				return (0);
			else
				return (1);
		}
		chck_short_flgs(flg, flgs);
		return (0);
	}
	return (1);
}
