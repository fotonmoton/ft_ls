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
	if (S_ISDIR(d_elm->stat_buf_struc->st_mode))
		ch = 'd';
	if (S_ISLNK(d_elm->stat_buf_struc->st_mode))
		ch = 'l';
	if (S_ISFIFO(d_elm->stat_buf_struc->st_mode))
		ch = 'p';
	if (S_ISSOCK(d_elm->stat_buf_struc->st_mode))
		ch = 's';
	if (S_ISBLK(d_elm->stat_buf_struc->st_mode))
		ch = 'b';
	if (S_ISCHR(d_elm->stat_buf_struc->st_mode))
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
	st = d_elm->stat_buf_struc;
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

	time_tmp = ctime(&(d_elm->stat_buf_struc->st_mtim.tv_sec));
	time_tmp[16] = 0;
	time = ft_strdup(time_tmp + 4);
	return (time);
}

void	get_padding(t_ft_ls *s_ls, t_dir_elm *d_elem)
{
	int 	links_len;
	int 	name_len;
	int 	group_len;
	int 	size_len;

	links_len = ft_num_len(d_elem->stat_buf_struc->st_nlink);
	name_len = (int)ft_strlen(d_elem->u_name);
	group_len = (int)ft_strlen(d_elem->g_name);
	size_len = ft_num_len(d_elem->stat_buf_struc->st_size);
	if (links_len > s_ls->padding->link_col)
		s_ls->padding->link_col = links_len;
	if (name_len > s_ls->padding->name_col)
		s_ls->padding->name_col = name_len;
	if (group_len > s_ls->padding->group_col)
		s_ls->padding->group_col = group_len;
	if (size_len > s_ls->padding->size_col)
		s_ls->padding->size_col = size_len;
}

void	get_info_from_stat(t_dir_elm *dir_elm, t_ft_ls *s_ls)
{
	dir_elm->attr_str = get_attr(dir_elm);
	dir_elm->u_name = ft_strdup(getpwuid(dir_elm->stat_buf_struc->st_uid)->pw_name);
	dir_elm->g_name = ft_strdup(getgrgid(dir_elm->stat_buf_struc->st_gid)->gr_name);
	dir_elm->m_time = get_time(dir_elm);
	get_padding(s_ls, dir_elm);
}


void init_file_meta_lst(t_ft_ls *s_ls, char *full_path)
{
	t_dir_elm		de;
	char 			*tmp_path;
	t_list			*lst_rnr;

	lst_rnr = s_ls->lst_fil_names;
	s_ls->lst_fil_meta = NULL;
	while (lst_rnr)
	{
		de.stat_buf_struc = malloc(sizeof(struct stat));
		de.elm_name = (char *)lst_rnr->content;
		tmp_path = get_full_path(full_path, de.elm_name);
		stat(tmp_path, de.stat_buf_struc);
		get_info_from_stat(&de, s_ls);
		ft_lstadd(&s_ls->lst_fil_meta, ft_lstnew(&de, sizeof(t_dir_elm)));
		free(tmp_path);
		lst_rnr = lst_rnr->next;
	}
}

t_list	*extract_filenames_from_dir(char *full_path)
{
	DIR				*dp;
	struct dirent	*dir_ent;
	t_list			*dir_files;

	dp = opendir(full_path);
	dir_files = NULL;
	if (dp != NULL)
		while ((dir_ent = readdir(dp)))
			fill_path_lst(&dir_files, dir_ent->d_name);
	closedir(dp);
	return (dir_files);
}

t_ft_ls		extract_dirs_from_filenames(t_ft_ls s_ls, char *full_path)
{
	char 		*full_path_with_file;

	s_ls.lst_dir_paths = NULL;
	while (s_ls.lst_fil_names)
	{
		full_path_with_file = get_full_path(full_path, s_ls.lst_fil_names->content);
		if (access(full_path_with_file, F_OK))
			if (access(full_path_with_file, R_OK) && (ft_strcmp(s_ls.lst_fil_names->content, ".") != 0) && (ft_strcmp(s_ls.lst_fil_names->content, "..") != 0))
			{
				if (s_ls.flgs->a)
					fill_path_lst(&s_ls.lst_dir_paths, s_ls.lst_fil_names->content);
				else if (*(char *)s_ls.lst_fil_names->content != '.')
					fill_path_lst(&s_ls.lst_dir_paths, s_ls.lst_fil_names->content);
			}
		s_ls.lst_fil_names = s_ls.lst_fil_names->next;
		free(full_path_with_file);
	}
	return (s_ls);
}

void ft_ls_dir(t_ft_ls s_ls, char *full_path)
{
	char 		*full_path_next;
	t_list		*tmp_rnr;

	sort_dirs(&s_ls.lst_dir_paths, s_ls.flgs);
	tmp_rnr = s_ls.lst_dir_paths;
	while (tmp_rnr)
	{
		full_path_next = get_full_path(full_path, tmp_rnr->content);
		s_ls.lst_fil_names = extract_filenames_from_dir(full_path_next);
		ft_ls_fil(&s_ls, full_path_next);
		if (s_ls.flgs->R)
			ft_ls_dir(extract_dirs_from_filenames(s_ls, full_path_next), full_path_next);
		tmp_rnr = tmp_rnr->next;
	}
}

void ft_ls_fil(t_ft_ls *s_ls, char *full_path)
{

	init_file_meta_lst(s_ls, full_path);
	sort_files(&s_ls->lst_fil_meta, s_ls->flgs);
	if ((!s_ls->one_dir && !s_ls->no_ops) || s_ls->flgs->R)
		print_full_path(s_ls, full_path);
	output(*s_ls);
}

void ft_ls(t_ft_ls s_ls)
{
	if (s_ls.lst_fil_names)
		ft_ls_fil(&s_ls, NULL);
	if (s_ls.lst_dir_paths)
		ft_ls_dir(s_ls, NULL);
}