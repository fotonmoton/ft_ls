#include "ft_ls.h"

int 	is_hidden(char *path)
{
	char	*begin;
	char	*end;

	begin = path;
	end = path + ft_strlen(path) - 1;
	if (begin != end)
	{
		while (end != begin && *end != '/')
			end--;
		if (end == begin)
		{
			if (*end == '.')
				return (1);
		}
		else if (*(end + 1) == '.')
			return (1);
	}
	else
		if (*end == '.')
			return (1);
	return (0);
}

//int		out(t_list *entity)
//{
//	t_dir_elm *d_elm;
//
//	d_elm = (t_dir_elm *)entity->content;
//	if (d_elm->flags->a)
//	{
//		column_or_line(entity);
//		return (1);
//	}
//	else
//		if (!is_hidden(d_elm->elm_name))
//		{
//			column_or_line(entity);
//			return (1);
//		}
//	return (0);
//}

void print_full_path(t_ft_ls *s_ls, char *path)
{
	char 	*cur_dir_semi_n;
	char 	*n_cur_dir;

	n_cur_dir = NULL;
	if (!path)
		s_ls->first_print = 0;
	if (s_ls->first_print)
	{
		cur_dir_semi_n = ft_strjoin(path, ":\n");
		s_ls->first_print = 0;
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


int		ft_lstiter_ret(t_list *lst, int (*f)(t_list *elem))
{
	int 	i;

	i = 0;
	while (lst && f)
	{
		if (f(lst))
			i = 1;
		lst = lst->next;
	}
	return (i);
}

void	put_spaces(int num)
{
	while (num--)
		ft_putstr(" ");
}

void	format_string(t_dir_elm *d_elem, t_col_len *padd)
{
	int 	links_len;
	int 	owner_len;
	int 	group_len;
	int 	size_len;

	links_len = ft_num_len(d_elem->stat_buf_struc->st_nlink);
	owner_len = (int)ft_strlen(d_elem->u_name);
	group_len = (int)ft_strlen(d_elem->g_name);
	size_len = ft_num_len(d_elem->stat_buf_struc->st_size);
	ft_putstr(d_elem->attr_str);
	put_spaces(padd->link_col - links_len + 1);
	ft_putnbr((int)d_elem->stat_buf_struc->st_nlink);
	ft_putstr(" ");
	ft_putstr(d_elem->u_name);
	put_spaces(padd->name_col - owner_len + 1);
	ft_putstr(d_elem->g_name);
	put_spaces(padd->group_col - group_len);
	put_spaces(padd->size_col - size_len + 1);
	ft_putnbr((int)d_elem->stat_buf_struc->st_size);
	ft_putstr(" ");
	ft_putstr(d_elem->m_time);
	ft_putstr(" ");
	ft_putstr(d_elem->elm_name);
	ft_putstr("\n");
}

void	long_output(t_ft_ls s_ls)
{
	t_list		*lst_rnr;

	lst_rnr = s_ls.lst_fil_meta;
	while (lst_rnr)
	{
		format_string(lst_rnr->content, s_ls.padding);
		lst_rnr = lst_rnr->next;
	}
}

void output(t_ft_ls s_ls)
{
	if (s_ls.flgs->l)
		long_output(s_ls);
//	else if (s_ls.flgs->col)
//		one_column(s_ls);
//	else
//		mult_column(s_ls);

// ft_lstiter_ret(s_ls.lst_fil_meta, out);
}