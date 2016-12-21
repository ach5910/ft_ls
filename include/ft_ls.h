/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 15:19:38 by ahunt             #+#    #+#             */
/*   Updated: 2016/12/20 15:19:46 by ahunt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <unistd.h>
# include <pwd.h>
# include <sys/xattr.h>
# include <time.h>
# include <grp.h>
# define L_FMT_FL	0x01
# define DOTS_FL	0x02
# define MOD_T_FL	0x04
# define REV_FL		0x08
# define RECURS_FL	0x10
# define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct	s_datafmt
{
	char			*curdir;
	long			blocks;
	unsigned int	flags;
	int				max_link;
	int				max_pwd;
	int				max_grp;
	int				max_size;
}				t_datafmt;

typedef struct s_dr
{
	char *name;
	struct stat statbuf;
	struct passwd *pwd;
	struct group *grp;
}				t_dr;

void	ft_putdirlong(t_list *list, t_datafmt *fmt);
void	ft_putdir(t_list *list, t_datafmt *fmt);
void	ft_parse_dir_flags(t_datafmt *fmt, char *src_flags);
void	ft_read_cur_dir(t_datafmt *fmt);
void 	ft_get_max_lengths(t_list *list, t_datafmt *fmt);
int		ft_comp_name(t_dr *current, t_dr *next);
int		ft_comp_time(t_dr *current, t_dr *next);

#endif 
