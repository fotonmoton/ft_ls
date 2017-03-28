#include "ft_ls.h"



void	sort_by(t_list **del, int (*f)())
{

}

void	sort(t_list *del, t_flags *flgs)
{
	if (!flgs->t)
		sort_by(&del, lex);
}