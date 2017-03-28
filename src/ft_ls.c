#include "ft_ls.h"

void	put_error(char *arg)
{
	char 	*final_str;
	char 	*arg_colon_errno;
	char 	*colon_errno;

	colon_errno = ft_strjoin(": ", strerror(errno));
	arg_colon_errno = ft_strjoin(arg, colon_errno);
	final_str = ft_strjoin("ls: ", arg_colon_errno);
	ft_putstr(final_str);
	ft_putstr("\n");
	free(final_str);
	free(arg_colon_errno);
	free(colon_errno);
}

void	init_dir_ent_list(DIR *dp, t_list **del, t_flags *flgs)
{
	t_dir_entity	de;


	while ((de.dirent = readdir(dp)) && (de.flags = flgs))
		ft_lstadd(del, ft_lstnew(&de, sizeof(t_dir_entity)));
}

void	ft_ls(char *path, t_flags *flgs)
{
	DIR				*dp;
//	int 			blocks;
//	char 			*tmp_path;
	t_list			*dir_ent_list;

//	tmp_path = 0;
//	blocks = 0;
	dir_ent_list = NULL;
	if (!(dp = opendir(path)) || open(path, O_RDONLY) == -1)
		put_error(path);
	else
	{
		init_dir_ent_list(dp, &dir_ent_list, flgs);
		sort(dir_ent_list, flgs);
		output(dir_ent_list);
	}

}