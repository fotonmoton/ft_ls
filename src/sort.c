#include "ft_ls.h"

int 	by_name_and_same_type(t_dir_elm *a, t_dir_elm *b)
{
	if ((S_ISDIR(a->stat_buf_struc->st_mode) &&
		 S_ISDIR(b->stat_buf_struc->st_mode)) ||
			(S_ISREG(a->stat_buf_struc->st_mode) &&
			 S_ISREG(b->stat_buf_struc->st_mode)))
		if (ft_strcmp(a->elm_name, b->elm_name) <= 0)
			return (1);
	return (0);
}

int 	all_lex(t_dir_elm *a, t_dir_elm *b)
{
	if (ft_strcmp_lex(a->elm_name, b->elm_name) <= 0)
		return (1);
	return (0);
}

int 	by_size(t_dir_elm *a, t_dir_elm *b)
{
	if (a->stat_buf_struc->st_size <= b->stat_buf_struc->st_size)
		return (1);
	return (0);
}

int 	by_m_time(t_dir_elm *a, t_dir_elm *b)
{
	if (a->stat_buf_struc->st_mtim.tv_sec >=
			b->stat_buf_struc->st_mtim.tv_sec)
		return (1);
	return (0);
}

int 	by_type(t_dir_elm *a, t_dir_elm *b)
{
	if (S_ISREG(b->stat_buf_struc->st_mode) && a)
		return (1);
	return (0);
}

int 	path_by_name(char *a, char *b)
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

void	sort_elms(t_list **del, t_flags *flgs)
{
	if (flgs->t)
		ft_lst_merge_sort(del, by_m_time);
	if (flgs->abn)
		ft_lst_merge_sort(del, all_lex);
	else
		by_type_and_name(del);
}

void	sort_dirs(t_list **dirs, t_flags *flgs)
{
	flgs = flgs;
	ft_lst_merge_sort(dirs, path_by_name);
}