/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 02:29:34 by gtertysh          #+#    #+#             */
/*   Updated: 2017/04/02 02:29:37 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		chck_opn(char *path)
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

t_list	*operands_parse(t_list *ops, t_ft_ls *s_ls)
{
	t_list	*tmp_rnr;
	t_list	*root;
	t_list	*lst_elm;

	root = NULL;
	tmp_rnr = ops;
	while (tmp_rnr)
	{
		if ((lst_elm = init_content_node(NULL, tmp_rnr->content, s_ls)))
		{
			get_padding_and_blocks(s_ls, lst_elm->content);
			ft_lstadd(&root, lst_elm);
		}
		tmp_rnr = tmp_rnr->next;
	}
	return (root);
}

int		parse_input(int ac, char **av, t_list **file_and_dirs, t_flags *flgs)
{
	int		i;
	int		open_type;
	int		no_errors;

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
