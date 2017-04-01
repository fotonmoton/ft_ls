#include "ft_ls.h"

int     is_hidden(char *path)
{
	char    *begin;
	char    *end;

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


char 	*get_full_path(char *path, char *dir_ent_name)
{
	char *tmp;
	char *tmp1;

	if (dir_ent_name && path)
	{
		if (path[ft_strlen(path) - 1] == '/')
		{
			if (*dir_ent_name == '/')
				tmp = ft_strjoin(path, dir_ent_name + 1);
			else
				tmp = ft_strjoin(path, dir_ent_name);
		}
		else
		{
			tmp1 = ft_strjoin(path, "/");
			tmp = ft_strjoin(tmp1, dir_ent_name);
			free(tmp1);
		}
		return (tmp);
	}
	else
		return (ft_strdup(dir_ent_name));
}


char 	get_file_type(t_dir_elm *d_elm)
{
	char 	ch;

	ch = '-';
	if (S_ISDIR(d_elm->stat_copy->st_mode))
		ch = 'd';
	if (S_ISLNK(d_elm->stat_copy->st_mode))
		ch = 'l';
	if (S_ISFIFO(d_elm->stat_copy->st_mode))
		ch = 'p';
	if (S_ISSOCK(d_elm->stat_copy->st_mode))
		ch = 's';
	if (S_ISBLK(d_elm->stat_copy->st_mode))
		ch = 'b';
	if (S_ISCHR(d_elm->stat_copy->st_mode))
		ch = 'c';
	return (ch);
}

void	get_file_permissions(char *attr_str, t_dir_elm *d_elm)
{
	struct stat *st;
	char		r;
	char 		w;
	char 		x;
	char 		f;

	r = 'r';
	w = 'w';
	x = 'x';
	f = '-';
	st = d_elm->stat_copy;
	attr_str[0] = (st->st_mode & S_IRUSR) ? r : f;
	attr_str[1] = (st->st_mode & S_IWUSR) ? w : f;
	attr_str[2] = (st->st_mode & S_IXUSR) ? x : f;
	attr_str[3] = (st->st_mode & S_IRGRP) ? r : f;
	attr_str[4] = (st->st_mode & S_IWGRP) ? w : f;
	attr_str[5] = (st->st_mode & S_IXGRP) ? x : f;
	attr_str[6] = (st->st_mode & S_IROTH) ? r : f;
	attr_str[7] = (st->st_mode & S_IWOTH) ? w : f;
	attr_str[8] = (st->st_mode & S_IXOTH) ? x : f;
}

char 	*get_attr(t_dir_elm *d_elm)
{
	char	*attr_str;

	attr_str = ft_memalloc(sizeof(11));

	attr_str[10] = '\0';
	attr_str[0] = get_file_type(d_elm);
	get_file_permissions(attr_str + 1, d_elm);
	return (attr_str);
}

char	*get_time(t_dir_elm *d_elm)
{
	char	*time;
	char	*time_tmp;

	time_tmp = ctime(&(d_elm->stat_copy->st_mtim.tv_sec));
	time_tmp[16] = 0;
	time = ft_strdup(time_tmp + 4);
	return (time);
}

void	set_columns_padd(t_dir_elm *de)
{
	de->cols_padd.link_col = ft_num_len(de->stat_copy->st_nlink);
	de->cols_padd.name_col = (int)ft_strlen(de->u_name);
	de->cols_padd.group_col = (int)ft_strlen(de->g_name);
	de->cols_padd.size_col = ft_num_len(de->stat_copy->st_size);
}


void	get_info_from_stat(t_dir_elm *dir_elm)
{
	dir_elm->attr_str = get_attr(dir_elm);
	dir_elm->u_name = ft_strdup(getpwuid(dir_elm->stat_copy->st_uid)->pw_name);
	dir_elm->g_name = ft_strdup(getgrgid(dir_elm->stat_copy->st_gid)->gr_name);
	dir_elm->m_time = get_time(dir_elm);
}

void 	to_null(t_dir_elm *de)
{
	de->stat_copy = NULL;
	de->link_name = NULL;
	de->attr_str = NULL;
	de->g_name = NULL;
	de->u_name = NULL;
	de->m_time = NULL;
}

t_list *read_stat(char *full_path, char *filename, t_ft_ls *s_ls)
{
	t_dir_elm		de;
	char 			*tmp_file_path;;

	to_null(&de);
	de.elm_name = ft_strdup(filename);
	tmp_file_path = get_full_path(full_path, filename);
	de.stat_copy = malloc(sizeof(struct stat));
	lstat(tmp_file_path, de.stat_copy);
	free(tmp_file_path);
	if (s_ls->flgs->l)
	{
		if (S_ISLNK(de.stat_copy->st_mode))
		{
			de.link_name = ft_strnew(PATH_MAX);
			if (readlink(tmp_file_path, de.link_name, PATH_MAX) == -1)
				put_error(0);
		}
		else
			de.link_name = NULL;
		get_info_from_stat(&de);
		set_columns_padd(&de);
	}
	return (ft_lstnew(&de, sizeof(t_dir_elm)));
}

t_list *init_content_node(char *full_path, char *filename, t_ft_ls *s_ls)
{
	if (s_ls->flgs->a)
		return (read_stat(full_path, filename, s_ls));
	else if (!is_hidden(filename) || ft_strcmp(filename, ".") == 0)
		return (read_stat(full_path, filename, s_ls));
	return (NULL);
}

t_list *find_dirs(char *full_path, t_ft_ls *s_ls, t_list *curr_dir_content)
{
	char 		*full_path_with_file;
	t_dir_elm	*dir_elm;
	t_list		*dirs;

	dirs = NULL;
	while (curr_dir_content)
	{
		dir_elm = (t_dir_elm *)curr_dir_content->content;
		full_path_with_file = get_full_path(full_path, dir_elm->elm_name);
		if ((S_ISDIR(dir_elm->stat_copy->st_mode)) && (ft_strcmp(dir_elm->elm_name, ".") != 0) && (ft_strcmp(dir_elm->elm_name, "..") != 0))
		{
			if (s_ls->flgs->a)
				ft_lstadd(&dirs, ft_lstnew(dir_elm, sizeof(t_dir_elm)));
			else if (*dir_elm->elm_name != '.')
				ft_lstadd(&dirs, ft_lstnew(dir_elm, sizeof(t_dir_elm)));
		}
		curr_dir_content = curr_dir_content->next;
		free(full_path_with_file);
	}
	return (dirs);
}

void	get_padding_and_blocks(t_ft_ls *s_ls, t_dir_elm *d_elem)
{
	if (d_elem && s_ls && s_ls->flgs->l)
	{
		if (d_elem->cols_padd.link_col > s_ls->max_cols_padd->link_col)
			s_ls->max_cols_padd->link_col = d_elem->cols_padd.link_col;
		if (d_elem->cols_padd.name_col > s_ls->max_cols_padd->name_col)
			s_ls->max_cols_padd->name_col = d_elem->cols_padd.name_col;
		if (d_elem->cols_padd.group_col > s_ls->max_cols_padd->group_col)
			s_ls->max_cols_padd->group_col = d_elem->cols_padd.group_col;
		if (d_elem->cols_padd.size_col > s_ls->max_cols_padd->size_col)
			s_ls->max_cols_padd->size_col = d_elem->cols_padd.size_col;
		if (d_elem->stat_copy)
			s_ls->dir_content_total += d_elem->stat_copy->st_blocks;
	}
}

void	extract_content(char *full_path, t_ft_ls *s_ls, t_list **dir_content)
{
	DIR				*dp;
	struct dirent	*de;
	t_list			*lst_elm;

	*dir_content = NULL;
	if ((dp = opendir(full_path)))
	{
		while ((de = readdir(dp)))
		{
				if ((lst_elm = init_content_node(full_path, de->d_name, s_ls)))
				{
					get_padding_and_blocks(s_ls, lst_elm->content);
					ft_lstadd(dir_content, lst_elm);
				}
		}
		closedir(dp);
	}
}

void	reset_s_ls(t_ft_ls *s_ls)
{
	s_ls->max_cols_padd->group_col = 0;
	s_ls->max_cols_padd->name_col = 0;
	s_ls->max_cols_padd->link_col = 0;
	s_ls->max_cols_padd->size_col = 0;
	s_ls->dir_content_total = 0;
}

void	print_content(t_ft_ls *s_ls, t_list *curr_dir_content, char *cur_path)
{
	if ((!s_ls->one_dir && !s_ls->no_ops) || s_ls->flgs->R)
		print_full_path(s_ls, cur_path);
	output(s_ls, curr_dir_content);
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
			tmp_rnr = tmp_rnr->next;
		}
	}
	return (root);
}


void	free_struct_lst(t_list *curr_cont)
{
	t_dir_elm	*tmp;
	t_list		*tmp1;
	while (curr_cont)
	{
		tmp1 = curr_cont->next;
		if (curr_cont->content)
		{
			tmp = (t_dir_elm *)curr_cont->content;
			free(tmp->attr_str);
			free(tmp->elm_name);
			free(tmp->g_name);
			free(tmp->u_name);
			free(tmp->m_time);
			free(tmp->link_name);
			free(tmp->stat_copy);
			free(tmp);
		}
		free(curr_cont);
		curr_cont = tmp1;
	}
}

void	ft_ls_fil(t_ft_ls *s_ls, t_list *root)
{
	sort_content(&root, s_ls->flgs);
	print_content(s_ls, root, NULL);
	free_struct_lst(root);
}

void	ft_ls_dir(t_ft_ls *s_ls, t_list *root, char *parent_dir)
{
	char		*cur_path;
	t_list		*curr_dir_content;

	curr_dir_content = NULL;
	sort_content(&root, s_ls->flgs);
	reset_s_ls(s_ls);
	while (root)
	{
		cur_path = get_full_path(parent_dir, ((t_dir_elm *)root->content)->elm_name);
		extract_content(cur_path, s_ls, &curr_dir_content);
		if (curr_dir_content)
		{
			sort_content(&curr_dir_content, s_ls->flgs);
			print_content(s_ls, curr_dir_content, cur_path);
		}
		if (s_ls->flgs->R)
			ft_ls_dir(s_ls, find_dirs(cur_path, s_ls, curr_dir_content), cur_path);
		root = root->next;
		free(cur_path);
	}
	free_struct_lst(curr_dir_content);
	free_struct_lst(root);
}