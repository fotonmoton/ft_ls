#include "ft_ls.h"

int 	by_name_and_same_type(t_dir_elm *a, t_dir_elm *b)
{
	if ((S_ISDIR(a->stat_copy->st_mode) &&
		 S_ISDIR(b->stat_copy->st_mode)) ||
			(S_ISREG(a->stat_copy->st_mode) &&
			 S_ISREG(b->stat_copy->st_mode)))
		if (ft_strcmp(a->elm_name, b->elm_name) <= 0)
			return (1);
	return (0);
}

int 	by_name_lex(t_dir_elm *a, t_dir_elm *b)
{
	if (ft_strcmp_lex(a->elm_name, b->elm_name) <= 0)
		return (1);
	return (0);
}

int 	by_name(t_dir_elm *a, t_dir_elm *b)
{
	if (ft_strcmp(a->elm_name, b->elm_name) <= 0)
		return (1);
	return (0);
}

int 	by_size(t_dir_elm *a, t_dir_elm *b)
{
	if (a->stat_copy->st_size <= b->stat_copy->st_size)
		return (1);
	return (0);
}

int 	by_m_time(t_dir_elm *a, t_dir_elm *b)
{
	long 	dif;

	dif = a->stat_copy->st_mtimespec.tv_sec - b->stat_copy->st_mtimespec.tv_sec;
	if (!dif)
		dif = a->stat_copy->st_mtimespec.tv_nsec -
				b->stat_copy->st_mtimespec.tv_nsec;
	if (dif < 0)
		return (0);
	else if (dif > 0)
		return (1);
	else
		return (by_name(a, b));
}

int 	by_type(t_dir_elm *a, t_dir_elm *b)
{
	if (S_ISREG(b->stat_copy->st_mode) && a)
		return (1);
	return (0);
}

int 	path_by_name(char *a, char *b)
{
	if (ft_strcmp(a, b) <= 0)
		return (1);
	return (0);
}

int 	path_by_name_lex(char *a, char *b)
{
	if (ft_strcmp_lex(a, b) <= 0)
		return (1);
	return (0);
}

void	by_type_and_name(t_list **del)
{
	ft_lst_merge_sort(del, by_type);
	ft_lst_merge_sort(del, by_name_and_same_type);

}

void	sort_content(t_list **del, t_flags *flgs)
{
	if (flgs->t)
		ft_lst_merge_sort(del, by_m_time);
	else if (flgs->abn)
		ft_lst_merge_sort(del, by_name_lex);
	else
		ft_lst_merge_sort(del, by_name);
	if (flgs->r)
		ft_lst_rev(del);
}

void sort_paths(t_list **paths)
{

		ft_lst_merge_sort(paths, path_by_name);
}