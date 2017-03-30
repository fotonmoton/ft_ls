#include "ft_ls.h"

//void	cannot_acces(char *arg)
//{
//	char 	*ls_ca_quo;
//	char 	*ls_ca;
//
//	ls_ca = ft_strjoin("ls: cannot access '", arg);
//	ls_ca_quo = ft_strjoin(ls_ca, "'");
//	perror(ls_ca_quo);
//	free(ls_ca_quo);
//	free(ls_ca);
//}

void	put_error(char *arg)
{
	char 	*ls_ca_quo;
	char 	*ls_ca;

	ls_ca = ft_strjoin("ls: cannot access '", arg);
	ls_ca_quo = ft_strjoin(ls_ca, "'");
	perror(ls_ca_quo);
	free(ls_ca_quo);
	free(ls_ca);
}