#include "ft_ls.h"

void	column_or_line(t_list *entity)
{
	t_dir_elm *d_elm;

	d_elm = (t_dir_elm *)entity->content;
	ft_putstr(d_elm->elm_name);
	if (!entity->next)
		ft_putstr("\n");
	else if (d_elm->flags->col)
		ft_putstr("\n");
	else
		ft_putstr("  ");
}

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

int		out(t_list *entity)
{
	t_dir_elm *d_elm;

	d_elm = (t_dir_elm *)entity->content;
	if (d_elm->flags->a)
	{
		column_or_line(entity);
		return (1);
	}
	else
		if (!is_hidden(d_elm->elm_name))
		{
			column_or_line(entity);
			return (1);
		}
	return (0);
}

void print_full_path(t_ft_ls *s_ls, char *path)
{
	char 	*cur_dir_semi_n;

	s_ls = s_ls;
	cur_dir_semi_n = ft_strjoin(path, ":\n");
	ft_putstr(cur_dir_semi_n);
	free(cur_dir_semi_n);
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

void output(t_ft_ls *s_ls)
{
	ft_lstiter_ret(s_ls->lst_fil_meta, out);
	ft_putstr("\n");
}