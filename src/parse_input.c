#include "ft_ls.h"

void	parse_input(int ac, char **av, t_flags *flgs)
{
	int 	i;
	int 	paths;

	i = 0;
	set_flags_to_zero(flgs);
	if (ac == 1)
		ft_ls(".", flgs);
	else if (ac > 1)
	{
		while (i < ac - 1 && *av[i + 1] == '-')
			if (chck_flgs(av[i + 1], flgs))
				break ;
			else
				i++;
		paths = i;
		if (paths == ac - 1)
			ft_ls("./", flgs);
		else
			while (paths < ac - 1)
				ft_ls(av[paths++ + 1], flgs);
	}
}