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
