#include "ft_ls.h"

void	column_out(t_list *entity)
{
	t_dir_entity *d_ent;

	d_ent = (t_dir_entity *)entity->content;
	if (d_ent->flags->a)
		printf("%s\t", d_ent->dirent->d_name);
	else
	if (*d_ent->dirent->d_name != '.')
		printf("%s\t\n", d_ent->dirent->d_name);
}

void	output(t_list *del)
{
	ft_lstiter(del, column_out);
}