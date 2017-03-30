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
	static t_flags	flgs;
	t_list			*str_paths[2];
	int 			no_errors;

	str_paths[FILES] = NULL;
	str_paths[DIRS] = NULL;
	no_errors = parse_input(argc, argv, str_paths, &flgs);
	if (str_paths[FILES] || str_paths[DIRS])
	{
		ft_ls(str_paths[FILES], str_paths[DIRS], &flgs, NULL);
	}
	else if (no_errors)
	{
		fill_path_lst(&str_paths[DIRS], "./");
		ft_ls(NULL, str_paths[DIRS], &flgs, NULL);
	}
	return 0;
}
