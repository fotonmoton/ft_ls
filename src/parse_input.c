#include "ft_ls.h"

int 	chck_opn(char *path)
{
	DIR		*d_stream;

	if (access(path, F_OK) == 0)
		if ((d_stream = opendir(path)))
		{
			closedir(d_stream);
			return (1);
		}
		else
			return (0);
	else
	{
		put_error(path);
		return (-1);
	}
}

void	fill_path_lst(t_list **path_lst, char *path)
{
	ft_lstadd(path_lst, ft_lstnew(path, ft_strlen(path) + 1));
}

int parse_input(int ac, char **av, t_list **file_and_dirs, t_flags *flgs)
{
	int 	i;
	int 	open_type;
	int 	no_errors;

	i = 0;
	no_errors = 1;
	if (ac == 1)
		return (no_errors);
	while (i < ac - 1)
	{
		if (chck_flgs(av[i + 1], flgs))
		{
			open_type = chck_opn(av[i + 1]);
			if (open_type == 0)
				fill_path_lst(&file_and_dirs[FILS], av[i + 1]);
			else if (open_type == 1)
				fill_path_lst(&file_and_dirs[DIRS], av[i + 1]);
			else if (open_type == -1)
				no_errors = 0;
		}
		i++;
	}
	return (no_errors);
}