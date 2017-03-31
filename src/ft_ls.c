#include "ft_ls.h"

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

void	get_max_padd(t_ft_ls *s_ls, t_dir_elm *d_elem)
{
	if (d_elem && s_ls)
	{
		if (d_elem->cols_padd.link_col > s_ls->max_cols_padd->link_col)
			s_ls->max_cols_padd->link_col = d_elem->cols_padd.link_col;
		if (d_elem->cols_padd.name_col > s_ls->max_cols_padd->name_col)
			s_ls->max_cols_padd->name_col = d_elem->cols_padd.name_col;
		if (d_elem->cols_padd.group_col > s_ls->max_cols_padd->group_col)
			s_ls->max_cols_padd->group_col = d_elem->cols_padd.group_col;
		if (d_elem->cols_padd.size_col > s_ls->max_cols_padd->size_col)
			s_ls->max_cols_padd->size_col = d_elem->cols_padd.size_col;
	}
}

void	get_info_from_stat(t_dir_elm *dir_elm)
{
	dir_elm->attr_str = get_attr(dir_elm);
	dir_elm->u_name = ft_strdup(getpwuid(dir_elm->stat_copy->st_uid)->pw_name);
	dir_elm->g_name = ft_strdup(getgrgid(dir_elm->stat_copy->st_gid)->gr_name);
	dir_elm->m_time = get_time(dir_elm);
}

void	set_columns_padd(t_dir_elm *de)
{
	de->cols_padd.link_col = ft_num_len(de->stat_copy->st_nlink);
	de->cols_padd.name_col = (int)ft_strlen(de->u_name);
	de->cols_padd.group_col = (int)ft_strlen(de->g_name);
	de->cols_padd.size_col = ft_num_len(de->stat_copy->st_size);
}

t_list *read_stat(char *full_path, char *filename, t_ft_ls *s_ls)
{
	t_dir_elm		de;
	char 			*tmp_file_path;

	de.elm_name = ft_strdup(filename);
	if (s_ls->flgs->l)
	{
		tmp_file_path = get_full_path(full_path, filename);
		de.stat_copy = malloc(sizeof(struct stat));
		lstat(tmp_file_path, de.stat_copy);
		if (S_ISLNK(de.stat_copy->st_mode))
		{
			de.link_name = ft_strnew(PATH_MAX);
			if (readlink(tmp_file_path, de.link_name, PATH_MAX) == -1)
				put_error(0);
		}
		get_info_from_stat(&de);
		set_columns_padd(&de);
		free(tmp_file_path);
	}
	return (ft_lstnew(&de, sizeof(t_dir_elm)));
}

t_list *init_content_node(char *full_path, char *filename, t_ft_ls *s_ls)
{
	if (s_ls->flgs->a)
		return (read_stat(full_path, filename, s_ls));
	else if (*filename != '.')
		return (read_stat(full_path, filename, s_ls));
	return (NULL);
}

t_list *extract_dirs_from_filenames(char *full_path, t_ft_ls *s_ls)
{
	char 		*full_path_with_file;
	t_dir_elm	*dir_elm;
	t_list		*dir_paths;
	t_list		*dir_content;

	dir_content = s_ls->lst_dir_content;
	dir_paths = NULL;
	while (dir_content)
	{
		dir_elm = (t_dir_elm *)dir_content->content;
		full_path_with_file = get_full_path(full_path, dir_elm->elm_name);
//		if (S_ISDIR(dir_elm->stat_copy->st_mode) && (ft_strcmp(dir_elm->elm_name, ".") != 0) && (ft_strcmp(dir_elm->elm_name, "..") != 0))
//		{
//			if (s_ls->flgs->a)
//				fill_path_lst(&dir_paths, dir_elm->elm_name);
//			else if (*dir_elm->elm_name != '.')
//				fill_path_lst(&dir_paths, dir_elm->elm_name);
//		}
		if (opendir(full_path_with_file) && (ft_strcmp(dir_elm->elm_name, ".") != 0) && (ft_strcmp(dir_elm->elm_name, "..") != 0))
		{
			if (s_ls->flgs->a)
				fill_path_lst(&dir_paths, dir_elm->elm_name);
			else if (*dir_elm->elm_name != '.')
				fill_path_lst(&dir_paths, dir_elm->elm_name);
		}
		dir_content = dir_content->next;
		free(full_path_with_file);
	}
	return (dir_paths);
}

void	get_padding_and_blocks(t_ft_ls *s_ls, t_dir_elm *d_elem)
{
	if (d_elem && s_ls)
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

void	extract_content(char *full_path, t_ft_ls *s_ls)
{
	DIR				*dp;
	struct dirent	*de;
	t_list			*lst_elm;

	s_ls->lst_dir_content = NULL;
	if ((dp = opendir(full_path)))
	{
		while ((de = readdir(dp)))
		{
				if ((lst_elm = init_content_node(full_path, de->d_name, s_ls)))
				{
					get_max_padd(s_ls, lst_elm->content);
					get_padding_and_blocks(s_ls, lst_elm->content);
					ft_lstadd(&s_ls->lst_dir_content, lst_elm);
				}
		}
		closedir(dp);
	}
	else
	{
		lst_elm = init_content_node(NULL, full_path, s_ls);
		get_max_padd(s_ls, lst_elm->content);
		ft_lstadd(&s_ls->lst_dir_content, lst_elm);
	}
}

void	reset_max_cols(t_ft_ls *s_ls)
{
	s_ls->max_cols_padd->group_col = 0;
	s_ls->max_cols_padd->name_col = 0;
	s_ls->max_cols_padd->link_col = 0;
	s_ls->max_cols_padd->size_col = 0;
}

void	print_content(t_ft_ls *s_ls, char *full_path_curr)
{
	t_list		*dirs;

	sort_files(&s_ls->lst_dir_content, s_ls->flgs);
	if ((!s_ls->one_dir && !s_ls->no_ops) || s_ls->flgs->R)
		print_full_path(s_ls, full_path_curr);
	output(s_ls);
	if (s_ls->flgs->R)
	{
		dirs = extract_dirs_from_filenames(full_path_curr, s_ls);
		reset_max_cols(s_ls);
		ft_ls(s_ls, dirs, full_path_curr);
	}
}

void ft_ls(t_ft_ls *s_ls, t_list *paths, char *curr_path)
{
	char 	*cur_filename;

	sort_paths(&paths, s_ls->flgs);
	while (paths)
	{
		cur_filename = get_full_path(curr_path, paths->content);
		extract_content(cur_filename, s_ls);
		print_content(s_ls, cur_filename);
		paths = paths->next;
	}
}