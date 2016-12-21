/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 15:18:51 by ahunt             #+#    #+#             */
/*   Updated: 2016/12/20 15:18:55 by ahunt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*ft_sort_list(t_list* lst, int (*cmp)(t_dr* , t_dr*))
{
	int		swap;
	t_list	*tmp;
	// t_dr	*data_tmp;
	t_dr	*current;
	t_dr	*next;

	swap = 1;
	if (lst == 0)
		return (lst);
	while (swap)
	{
		swap = 0;
		tmp = lst;
		while (tmp->next)
		{
			current = tmp->content;
		 	next = tmp->next->content;
			if (cmp(tmp->content, tmp->next->content) > 0)
			{
				// data_tmp = tmp->content;
				tmp->content = next;
				tmp->next->content = current;
				swap = 1;
			}
			tmp = tmp->next;
		}
	}
	return (tmp);
}

int	ft_comp_name(t_dr *current, t_dr *next)
{
	return (ft_strcmp(current->name, next->name));
}

int	ft_comp_time(t_dr *current, t_dr *next)
{
	return (next->statbuf.st_mtime - current->statbuf.st_mtime);
}

int main(int argc, char **argv)
{
	// DIR *dir;
	// struct dirent *dp;
	t_datafmt *fmt;
	// t_list *list;
	// t_dr *dr;

	// dr = (t_dr*)malloc(sizeof(t_dr));
	fmt = (t_datafmt*)malloc(sizeof(t_datafmt));
	ft_bzero(fmt, sizeof(t_datafmt));
	fmt->curdir = ft_strdup(".");
	if (argc != 1)
		ft_parse_dir_flags(fmt, argv[1]);
	ft_read_cur_dir(fmt);
	return(0);
}

void	ft_parse_dir_flags(t_datafmt *fmt, char *src_flags)
{
	int i;

	i = 0;
	if (src_flags[i++] != '-')
	{
		ft_putendl("Error: usasge");
		return ;
	}
	while (src_flags[i])
	{
		if (src_flags[i] == 'R')
			fmt->flags |= RECURS_FL;
		else if (src_flags[i] == 'r')
			fmt->flags |= REV_FL;
		else if (src_flags[i] == 't')
			fmt->flags |= MOD_T_FL;
		else if (src_flags[i] == 'a')
			fmt->flags |= DOTS_FL;
		else if (src_flags[i] == 'l')
			fmt->flags |= L_FMT_FL;
		else
		{
			ft_putendl("Error: usasge");
			return ;
		}
		i++;
	}
}
void	ft_read_cur_dir(t_datafmt *fmt)
{
	DIR *dir;
	struct dirent *dp;
	struct stat statbuf;
	t_list *list;
	t_dr *dr;

	dr = (t_dr*)malloc(sizeof(t_dr));
	// fmt = (t_datafmt*)malloc(sizeof(t_datafmt));
	dir = opendir(fmt->curdir);
	list = NULL;
	while ((dp = readdir(dir)) != NULL)
	{
		// printf("Inode number: %llu\nRecord Length: %hu\nType of File:%hhu\nFilename:%s\n\n"
		// 	, dp->d_ino, dp->d_reclen, dp->d_type, dp->d_name);


		//Get Entry info
		if (stat(dp->d_name, &statbuf) == -1)
			continue ;
		if (dp->d_name[0] == '.' && !(fmt->flags & DOTS_FL))
			continue ;
		dr->name = ft_strdup(dp->d_name);
		dr->statbuf = statbuf;
		dr->pwd = getpwuid(statbuf.st_uid);
		dr->grp = getgrgid(statbuf.st_gid);
		ft_lstadd(&list, ft_lstnew(dr, sizeof(t_dr)));
		ft_bzero(dr, sizeof(t_dr));

		//Print out type, permissions and number of links
		// printf("%10.10hu", statbuf.st_mode);
		fmt->blocks += statbuf.st_blocks;
		ft_bzero(&statbuf, sizeof(struct stat));
		// ft_bzero(&dp, sizeof(struct dirent));
		


	}
	closedir(dir);
	ft_sort_list(list, &ft_comp_name);
	if (fmt->flags & MOD_T_FL)
		ft_sort_list(list, &ft_comp_time);
	if (fmt->flags & REV_FL)
		list = ft_lstrev(&list);
	if (fmt->flags & L_FMT_FL)
		ft_putdirlong(list, fmt);
	else
		ft_putdir(list, fmt);
}

void	ft_putdir(t_list *list, t_datafmt *fmt)
{
	t_dr *dr;
	int count;

	count = 1;
	while (list)
	{
		dr = list->content;
		if (count % 3 == 0)
			printf("%-24s\n", dr->name );
		else
			printf("%-24s", dr->name);
		count++;
		list = list->next;
	}
	if (--count % 3 != 0)
		printf("\n");
}

void	ft_putdirlong(t_list *list, t_datafmt *fmt)
{
	struct stat statbuf;
	struct passwd *pwd;
	struct group *grp;
	t_dr *dr;
	char 	*tm;

	ft_get_max_lengths(list, fmt);
	printf("total %ld\n", fmt->blocks);
	while (list)
	{
		dr = list->content;
		statbuf = dr->statbuf;
		pwd = dr->pwd;
		grp = dr->grp;
		printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
	    printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
	    printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
	    printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
	    printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
	    printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
	    printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
	    printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
	    printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
	    printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
		printf("%*d",fmt->max_link + 2, statbuf.st_nlink);

		//Print owners name
		if (pwd != NULL)
			printf(" %-*.*s", fmt->max_pwd + 2, fmt->max_pwd + 2, pwd->pw_name);
		else
			printf(" %-*d", fmt->max_pwd + 2, statbuf.st_uid);

		if (grp  != NULL)
			printf("%-*.*s", fmt->max_grp, fmt->max_grp, grp->gr_name);
		else
			printf("%-*d", fmt->max_grp, statbuf.st_gid);

		//Print size of file
		printf("%*jd", fmt->max_size + 2, (intmax_t)statbuf.st_size);

		tm = ft_strchr(ctime(&statbuf.st_mtime), ' ');
		// len = ft_strlen(tm);
		// tm = ft_strncpy(tm, len - 2);


		//Get localized date string
		printf("%-13.13s %s\n", tm, dr->name);
		tm = NULL;
		list = list->next;
	}
}

void ft_get_max_lengths(t_list *list, t_datafmt *fmt)
{
	t_list *tmp;
	int len;
	t_dr *dr;

	tmp = list;
	while (tmp)
	{
		dr = tmp->content;
		len = 1;
		while (ft_pow(10, len) - 1 < (uintmax_t)dr->statbuf.st_nlink)
			len++;
		fmt->max_link = MAX(fmt->max_link, (int)len);
		fmt->max_pwd = MAX(fmt->max_pwd, ft_strlen(dr->pwd->pw_name));
		fmt->max_grp = MAX(fmt->max_grp, ft_strlen(dr->grp->gr_name));
		len = 1;
		while (ft_pow(10, len) - 1 < (uintmax_t)dr->statbuf.st_size)
			len++;
		fmt->max_size = MAX(fmt->max_size, (int)len);
		tmp = tmp->next;
	}
}