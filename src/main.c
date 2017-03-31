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
	static t_ft_ls	s_ls;
	int 			no_errors_and_valid_args;

	s_ls.flgs = &flgs;
	s_ls.first_print = 1;
	no_errors_and_valid_args = parse_input(argc, argv, &s_ls);
	if (s_ls.lst_dir_paths || s_ls.lst_fil_names)
	{
		if (ft_lst_len(s_ls.lst_dir_paths) == 1 && ft_lst_len(s_ls.lst_fil_names) == 0 && !s_ls.flgs->R)
			s_ls.one_dir = 1;
		ft_ls(&s_ls);
	}
	else if (no_errors_and_valid_args)
	{
		s_ls.no_ops = 1;
		fill_path_lst(&s_ls.lst_dir_paths, "./");
		ft_ls(&s_ls);
	}
	return 0;
}
