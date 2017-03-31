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

void init_file_meta_lst(t_ft_ls *s_ls, char *full_path)
{
	t_dir_elm		de;
	char 			*tmp_path;
	t_list			*lst_rnr;

	lst_rnr = s_ls->lst_fil_names;
	s_ls->lst_fil_meta = NULL;
	while (lst_rnr)
	{
		de.flags = s_ls->flgs;
		de.stat_buf_struc = malloc(sizeof(struct stat));
		de.elm_name = (char *)lst_rnr->content;
		tmp_path = get_full_path(full_path, de.elm_name);
		stat(tmp_path, de.stat_buf_struc);
		ft_lstadd(&s_ls->lst_fil_meta, ft_lstnew(&de, sizeof(t_dir_elm)));
		free(tmp_path);
		lst_rnr = lst_rnr->next;
	}
}

//void	init_dir_ent_lst(t_list **fil_ent_lst, t_list *dirs, t_flags *flgs)
//{
//
//	t_dir_elm		de;
//
//	while (dirs)
//	{
//		de.flags = flgs;
//		de.stat_buf_struc = malloc(sizeof(struct stat));
//		de.elm_name = (char *)dirs->content;
//		de.full_path =(char *)dirs->content;
//		stat(de.full_path, de.stat_buf_struc);
//		ft_lstadd(fil_ent_lst, ft_lstnew(&de, sizeof(t_dir_elm)));
//		dirs = dirs->next;
//	}
//}
//
//void	init_dir_ent_list(t_list **del, t_flags *flgs, char *path)
//{
//	DIR				*dp;
//	t_dir_elm		de;
//	struct dirent	*dir_ent;
//
//	dp = opendir(path);
//	while ((dir_ent = readdir(dp)))
//	{
//		de.flags = flgs;
//		de.stat_buf_struc = malloc(sizeof(struct stat));
//		de.elm_name = ft_strdup(dir_ent->d_name);
//		de.full_path = get_full_path(path, dir_ent->d_name);
//		stat(de.full_path, de.stat_buf_struc);
//		ft_lstadd(del, ft_lstnew(&de, sizeof(t_dir_elm)));
//	}
//	closedir(dp);
//}

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

t_ft_ls		*extract_dirs_from_filenames(t_ft_ls *s_ls, char *full_path)
{
	char 		*full_path_with_file;

	s_ls->lst_dir_paths = NULL;
	while (s_ls->lst_fil_names)
	{
		full_path_with_file = get_full_path(full_path, s_ls->lst_fil_names->content);
		if (opendir(full_path_with_file) && (ft_strcmp(s_ls->lst_fil_names->content, ".") != 0) && (ft_strcmp(s_ls->lst_fil_names->content, "..") != 0))
		{
			if (s_ls->flgs->a)
				fill_path_lst(&s_ls->lst_dir_paths, s_ls->lst_fil_names->content);
			else if (*(char *)s_ls->lst_fil_names->content != '.')
				fill_path_lst(&s_ls->lst_dir_paths, s_ls->lst_fil_names->content);
		}
		s_ls->lst_fil_names = s_ls->lst_fil_names->next;
		free(full_path_with_file);
	}
	return (s_ls);
}

void ft_ls_dir(t_ft_ls *s_ls, char *full_path)
{
	char 		*full_path_next;
	t_list		*tmp_rnr;

	sort_dirs(&s_ls->lst_dir_paths, s_ls->flgs);
	tmp_rnr = s_ls->lst_dir_paths;
	while (tmp_rnr)
	{
		full_path_next = get_full_path(full_path, tmp_rnr->content);
		s_ls->lst_fil_names = extract_filenames_from_dir(full_path_next);
		ft_ls_fil(s_ls, full_path_next);
		if (s_ls->flgs->R)
			ft_ls_dir(extract_dirs_from_filenames(s_ls, full_path_next), full_path_next);
		tmp_rnr = tmp_rnr->next;
	}
}

void ft_ls_fil(t_ft_ls *s_ls, char *full_path)
{

	init_file_meta_lst(s_ls, full_path);
	sort_files(&s_ls->lst_fil_meta, s_ls->flgs);
	if (full_path && !s_ls->one_dir && !s_ls->no_ops)
		print_full_path(s_ls, full_path);
	output(s_ls);
}

void ft_ls(t_ft_ls *s_ls)
{
	if (s_ls->lst_fil_names)
		ft_ls_fil(s_ls, NULL);
	if (s_ls->lst_dir_paths)
		ft_ls_dir(s_ls, NULL);
}