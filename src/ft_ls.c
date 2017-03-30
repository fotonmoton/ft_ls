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

void	init_dir_con_lst(t_list **dir_content_lst, t_list *filenames,
						 t_flags *flgs, char *par_dir)
{
	t_dir_elm		de;
	char 			*tmp_path;

	while (filenames)
	{
		de.flags = flgs;
		de.stat_buf_struc = malloc(sizeof(struct stat));
		de.elm_name = (char *)filenames->content;
		tmp_path = get_full_path(par_dir, de.elm_name);
		stat(tmp_path, de.stat_buf_struc);
		ft_lstadd(dir_content_lst, ft_lstnew(&de, sizeof(t_dir_elm)));
		free(tmp_path);
		filenames = filenames->next;
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

t_list	*extract_files_from_dir(char *dir, char *par_dir)
{
	DIR				*dp;
	struct dirent	*dir_ent;
	t_list			*dir_files;
	char 			*tmp_path;

	tmp_path = get_full_path(par_dir, dir);
	dp = opendir(tmp_path);
	dir_files = NULL;
	while ((dir_ent = readdir(dp)))
		fill_path_lst(&dir_files, dir_ent->d_name);
	closedir(dp);
	free(tmp_path);
	return (dir_files);
}

t_list	*extract_dirs_from_filenames(t_list *filenames, char *par_d)
{
	t_list		*dirs;
	char 		*tmp_full_path;
	dirs = NULL;

	while (filenames)
	{
		tmp_full_path = get_full_path(par_d, filenames->content);
		if (opendir(tmp_full_path) && (ft_strcmp(filenames->content, ".") != 0) && (ft_strcmp(filenames->content, "..") != 0))
			fill_path_lst(&dirs, tmp_full_path);
		free(tmp_full_path);
		filenames = filenames->next;
	}
	return (dirs);
}

void		ft_ls(t_list *filenames, t_list *dir_paths, t_flags *flgs,
				  char *par_dir)
{
	t_list		*dir_content_lst;

	dir_content_lst = NULL;
	if (filenames)
	{
		init_dir_con_lst(&dir_content_lst, filenames, flgs, par_dir);
		sort_elms(&dir_content_lst, flgs);
		output(dir_content_lst, par_dir, flgs);
		if (flgs->R)
			ft_ls(NULL, extract_dirs_from_filenames(filenames, par_dir), flgs, NULL);
	}
	if (dir_paths)
	{
		sort_dirs(&dir_paths, flgs);
		while (dir_paths)
		{
			ft_ls(extract_files_from_dir(dir_paths->content, par_dir), NULL, flgs, dir_paths->content);
			dir_paths = dir_paths->next;
		}
	}
}