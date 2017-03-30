#include "ft_ls.h"

int		chck_long_flgs(char *flg, t_flags *flgs)
{
	if (*(flg + 1) && (flg += 1))
	{
		if (flgs->abn == 0) flgs->abn = (ft_strcmp(flg, "all-by-name") == 0)
										? 1 : 0;
		return (0);
	}
	return (1);
}
void	chck_short_flgs(char *flg, t_flags *flgs)
{
	if (flgs->l == 0) flgs->l = (ft_strcmp(flg, "l") == 0) ? 1 : 0;
	if (flgs->a == 0) flgs->a = (ft_strcmp(flg, "a") == 0) ? 1 : 0;
	if (flgs->R == 0) flgs->R = (ft_strcmp(flg, "R") == 0) ? 1 : 0;
	if (flgs->t == 0) flgs->t = (ft_strcmp(flg, "t") == 0) ? 1 : 0;
	if (flgs->col == 0) flgs->col = (ft_strcmp(flg, "1") == 0) ? 1 : 0;
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

