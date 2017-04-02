/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 18:26:51 by gtertysh          #+#    #+#             */
/*   Updated: 2017/04/02 06:33:40 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_str_lst(t_list *curr_cont)
{
	char		*tmp;
	t_list		*tmp1;

	while (curr_cont)
	{
		tmp1 = curr_cont->next;
		if (curr_cont->content)
		{
			tmp = (char *)curr_cont->content;
			free(tmp);
		}
		free(curr_cont);
		curr_cont = tmp1;
	}
}

void	init_base_structs(t_ft_ls *s_ls, t_flags *flgs, t_col_len *padd,
							t_list **fil_dir)
{
	fil_dir[FILS] = NULL;
	fil_dir[DIRS] = NULL;
	s_ls->flgs = flgs;
	s_ls->max_cols_padd = padd;
	s_ls->first_print = 1;
	s_ls->files_print = 0;
	s_ls->dir_content_total = 0;
}

void	ft_ls_start(t_ft_ls *s_ls, t_list **file_and_dirs, int no_error_ops)
{
	t_list		*file_lst;

	if (file_and_dirs[FILS])
	{
		file_lst = operands_parse(file_and_dirs[FILS], s_ls);
		s_ls->files_print = 1;
		ft_ls_fil(s_ls, &file_lst, NULL);
		s_ls->files_print = 0;
		s_ls->first_print = 0;
	}
	if (file_and_dirs[DIRS])
	{
		if (ft_lst_len(file_and_dirs[FILS]) == 0 &&
				ft_lst_len(file_and_dirs[DIRS]) == 1)
			if (!s_ls->flgs->recur)
				s_ls->one_dir = 1;
		ft_ls_dir(s_ls, operands_parse(file_and_dirs[DIRS], s_ls), NULL);
	}
	if (no_error_ops && (!file_and_dirs[DIRS] && !file_and_dirs[FILS]))
	{
		s_ls->one_dir = 1;
		fill_path_lst(&file_and_dirs[DIRS], "./");
		ft_ls_dir(s_ls, operands_parse(file_and_dirs[DIRS], s_ls), NULL);
	}
}

int		main(int argc, char **argv)
{
	static t_flags		flgs;
	static t_col_len	padding;
	static t_ft_ls		s_ls;
	t_list				**file_and_dirs;
	int					no_error_operands;

	file_and_dirs = malloc(sizeof(t_list *) * 2);
	init_base_structs(&s_ls, &flgs, &padding, file_and_dirs);
	no_error_operands = parse_input(argc, argv, file_and_dirs, s_ls.flgs);
	ft_ls_start(&s_ls, file_and_dirs, no_error_operands);
	free_str_lst(file_and_dirs[FILS]);
	free_str_lst(file_and_dirs[DIRS]);
	free(file_and_dirs);
	return (0);
}
