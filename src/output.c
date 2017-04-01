#include "ft_ls.h"

void print_full_path(t_ft_ls *s_ls, char *path)
{
	char 	*cur_dir_semi_n;
	char 	*n_cur_dir;

	n_cur_dir = NULL;
	if (!s_ls->files_print)
	{
		if (s_ls->first_print)
		{
			s_ls->first_print = 0;
			cur_dir_semi_n = ft_strjoin(path, ":\n");
		}
		else
		{
			n_cur_dir = ft_strjoin("\n", path);
			cur_dir_semi_n = ft_strjoin(n_cur_dir, ":\n");
		}
		ft_putstr(cur_dir_semi_n);
		free(cur_dir_semi_n);
		free(n_cur_dir);
	}
}

void	put_spaces(int num)
{
	while (num--)
		ft_putstr(" ");
}

void	put_total(int total)
{
	ft_putstr("total");
	ft_putstr(" ");
	ft_putnbr(total);
	ft_putstr("\n");
}

void	put_link(t_dir_elm *d_elm)
{
	char *tmp_link;
	tmp_link = ft_strjoin(" -> ", d_elm->link_name);
	ft_putstr(tmp_link);
	free(tmp_link);
}

void	long_format(t_list *lst_d_elm, t_ft_ls *s_ls)
{
	t_dir_elm	*d_elem;

	d_elem = (t_dir_elm *)lst_d_elm->content;
	ft_putstr(d_elem->attr_str);
	put_spaces(s_ls->max_cols_padd->link_col - d_elem->cols_padd.link_col + 1);
	ft_putnbr((int)d_elem->stat_copy->st_nlink);
	ft_putstr(" ");
	ft_putstr(d_elem->u_name);
	put_spaces(s_ls->max_cols_padd->name_col - d_elem->cols_padd.name_col + 1);
	ft_putstr(d_elem->g_name);
	put_spaces(s_ls->max_cols_padd->group_col - d_elem->cols_padd.group_col);
	put_spaces(s_ls->max_cols_padd->size_col - d_elem->cols_padd.size_col + 1);
	ft_putnbr((int)d_elem->stat_copy->st_size);
	ft_putstr(" ");
	ft_putstr(d_elem->m_time);
	ft_putstr(" ");
	ft_putstr(d_elem->elm_name);
	if (S_ISLNK(d_elem->stat_copy->st_mode))
		put_link(d_elem);
	ft_putstr("\n");
}

void	one_line(t_list *lst_d_elm, t_ft_ls *s_ls)
{
	ft_putstr(((t_dir_elm *)lst_d_elm->content)->elm_name);
	s_ls = 0;
	if (lst_d_elm->next)
		ft_putstr("  ");
	else
		ft_putstr("\n");
}

void	one_column(t_list *lst_d_elm, t_ft_ls *s_ls)
{
	s_ls = 0;
	ft_putstr(((t_dir_elm *)lst_d_elm->content)->elm_name);
	ft_putstr("\n");
}

void	out(t_ft_ls *s_ls, t_list *cdc, void (*format_fun)(t_list *, t_ft_ls *))
{
	t_list		*lst_rnr;

	lst_rnr = cdc;
	while (lst_rnr)
	{
		if (s_ls->flgs->a)
			format_fun(lst_rnr, s_ls);
		else if (*((t_dir_elm *)lst_rnr->content)->elm_name != '.')
			format_fun(lst_rnr, s_ls);
		lst_rnr = lst_rnr->next;
	}
}

void output(t_ft_ls *s_ls, t_list *curr_dir_content)
{
	if (s_ls->flgs->l)
	{
		if (!s_ls->files_print)
			put_total(s_ls->dir_content_total / 2);
		out(s_ls, curr_dir_content, long_format);
	}
	else if (s_ls->flgs->col)
		out(s_ls, curr_dir_content, one_column);
	else
		out(s_ls, curr_dir_content, one_line);
//	else if (s_ls.flgs->col)
//		one_column(s_ls);
//	else
//		mult_column(s_ls);

// ft_lstiter_ret(s_ls.lst_dir_content, out);
}
