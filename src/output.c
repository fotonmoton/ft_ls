#include "ft_ls.h"

void	column_or_line(t_list *entity)
{
	t_dir_elm *d_elm;

	d_elm = (t_dir_elm *)entity->content;
	ft_putstr(d_elm->elm_name);
	if (entity->next)
	{
		if (d_elm->flags->col)
			ft_putstr("\n");
		else
			ft_putstr("  ");
	}
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
		if (*d_elm->elm_name != '.')
		{
			column_or_line(entity);
			return (1);
		}
	return (0);
}

void	print_full_path(char *path)
{
	char 	*cur_dir_semi_n;

	cur_dir_semi_n = ft_strjoin(path, ":\n");
	ft_putstr(cur_dir_semi_n);
	free(cur_dir_semi_n);
}

void 	put_current_dir(char *cur_dir, t_flags *flgs)
{
	if (flgs->a)
		print_full_path(cur_dir);
	else
	{
		if (*cur_dir != '.')
			print_full_path(cur_dir);
	}
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

void output(t_list *del, char *current_dir, t_flags *flgs)
{
	if (current_dir)
		put_current_dir(current_dir, flgs);
	if (ft_lstiter_ret(del, out))
		ft_putstr("\n");
}