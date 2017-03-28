#include "ft_ls.h"

void	set_flags_to_zero(t_flags *flgs)
{
	flgs->a = 0;
	flgs->l = 0;
	flgs->R = 0;
	flgs->t = 0;
	flgs->col = 0;
}

int		chck_flgs(char *flg, t_flags *flgs)
{
	if ((!*(flg + 1)) && (flg += 1))
		return (1);
	if (flgs->l == 0) flgs->l = (ft_strchr(flg, 'l') != NULL) ? 1 : 0;
	if (flgs->a == 0) flgs->a = (ft_strchr(flg, 'a') != NULL) ? 1 : 0;
	if (flgs->R == 0) flgs->R = (ft_strchr(flg, 'R') != NULL) ? 1 : 0;
	if (flgs->t == 0) flgs->t = (ft_strchr(flg, 't') != NULL) ? 1 : 0;
	if (flgs->col == 0) flgs->col = (ft_strchr(flg, '1') != NULL) ? 1 : 0;
	return (0);
}