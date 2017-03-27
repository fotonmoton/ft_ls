/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 18:26:51 by gtertysh          #+#    #+#             */
/*   Updated: 2017/03/25 18:27:42 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		chck_flgs(char *flg, t_flags *flgs)
{
	if ((!*(flg + 1)) && (flg += 1))
		return (1);
	if (flgs->l == 0) flgs->l = (unsigned int)ft_strchr(flg, 'l');
	if (flgs->a == 0) flgs->a = (unsigned int)ft_strchr(flg, 'a');
	if (flgs->R == 0) flgs->R = (unsigned int)ft_strchr(flg, 'R');
	if (flgs->t == 0) flgs->t = (unsigned int)ft_strchr(flg, 't');
	return (0);
}

void	init_dir_ent_list(DIR *dp, t_list **del, t_flags *flgs)
{
	t_dir_entity	de;


	while ((de.dirent = readdir(dp)) && (de.flags = flgs))
		ft_lstadd(del, ft_lstnew(&de, sizeof(t_dir_entity)));
}

void	column_out(t_list *entity)
{
	t_dir_entity *d_ent;

	d_ent = (t_dir_entity *)entity->content;
	if (!d_ent->flags->a)
		printf("%s\t", d_ent->dirent->d_name);
	else
		if (*d_ent->dirent->d_name != '.')
			printf("%s\t", d_ent->dirent->d_name);

}

void	ft_ls(char *path, t_flags *flgs)
{
	DIR				*dp;
	int 			blocks;
	char 			*tmp_path;
	t_list			*dir_ent_list;

	tmp_path = 0;
	blocks = 0;
	dir_ent_list = NULL;
	if (!(dp = opendir(path)) || open(path, O_RDONLY) == -1)
		put_error(path);
	else
	{
		init_dir_ent_list(dp, &dir_ent_list, flgs);
		ft_lstiter(dir_ent_list, column_out);
	}

}

void	parse_input(int ac, char **av, t_flags *flgs)
{
	int 	i;
	int 	paths;

	i = 0;
	if (ac == 1)
		ft_ls("./", NULL);
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

int		main(int argc, char **argv)
{
//	DIR				*dp;
//	struct dirent 	*ep;
//	struct stat		*stat_buf;
//	char 			*str_tmp;
//	int 			blocks;
	t_flags			flgs;

	parse_input(argc, argv, &flgs);

//	dp = opendir (argv[1]);
//	blocks = 0;
//	if (dp != NULL)
//	{
//		while ((ep = readdir (dp)))
//		{
//			str_tmp = ft_strjoin("../", ep->d_name);
//			stat_buf = malloc(sizeof(struct stat));
//			stat(str_tmp, stat_buf);
//			printf("%s:\n", str_tmp);
//			printf("  nlinks: %d\n", (int)stat_buf->st_nlink);
//			printf("  st_mode: %d\n", S_ISCHR(stat_buf->st_mode));
//			printf("  MAJOR: %d\n", (int)major(stat_buf->st_rdev));
//			printf("  MINOR: %d\n", (int)minor(stat_buf->st_rdev));
//			printf("  st_uid: %s\n", getpwuid(stat_buf->st_uid)->pw_name);
//			printf("  st_gid: %s\n", getgrgid(stat_buf->st_gid)->gr_name);
//			printf("  st_size: %d\n", (int)stat_buf->st_size);
//			printf("  st_atime: %s", ctime(&stat_buf->st_atimespec.tv_sec));
//			printf("  st_blocks: %d\n\n", (int)stat_buf->st_blocks);
//			blocks += stat_buf->st_blocks;
//			free(stat_buf);
//			free(str_tmp);
//		}
//		(void) closedir (dp);
//		printf("  total blocks: %d\n", blocks);
//	}
//	else
//		printf("%s\n", strerror(errno));
	return 0;
}
