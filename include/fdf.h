/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 00:16:05 by ahunt             #+#    #+#             */
/*   Updated: 2016/12/01 00:16:06 by ahunt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <math.h>
# define WIDTH 1200
# define HEIGHT 800
# define TRAN_H 0x01
# define TRAN_V  0x02
# define SCL  0x04
# define ROT_X  0x08
# define ROT_Y  0x10
# define ROT_Z  0x20
# define MOUS  0x40
# define SIGN  0x80
# define ROT_X_NEG  0x100
# define ROT_Y_NEG  0x200
# define DRAW_SHAPE 0X400

typedef struct s_vec
{
	double	x;
	double y;
	double	z;
	int color;
}				t_vec;

// int colors[24] = {0};
typedef struct  s_img
{
	void	*i_ptr;
	int bpp;
	int size_line;
	int endian;
	char *data;
}				t_img;

typedef struct 	s_env
{
	void	*mlx;
	void	*win;
	t_img	*img;
	int		len;
	int 	max_strs;
	unsigned int *keys;
	int	key_len;
	double per;
	int STACK_MAX;
	t_vec *pnts;
	t_vec *c_pnts;
	double c_min;
	double c_max;
	unsigned int flags;
	char *file;
	char **files;
	int max_files;
	int file_num;
}				t_env;

typedef int (*t_maps)(int);

typedef struct  s_line
{
	double dx;
	double dy;
	double p;
	double i;
	double j;
	double j_incr;
	int ci_r;
	int ci_g;
	int ci_b;
	int cf_r;
	int cf_g;
	int cf_b;
	int end;
	int start;
}				t_line;


t_env *init_environment(void);
void get_map(t_env *e);
void set_copy(t_env *e);
void draw_map(t_env *e);
void draw_legend(t_env *e);
void draw_shape(t_env *e);
t_line	*get_line_params_x(t_env *e, int index, int inc);
t_line	*get_line_params_y(t_env *e, int index, int inc);
void draw_lines_x(t_env *e, int index, int inc);
void draw_lines_y(t_env *e, int index, int inc);
double mean_x(t_env *e);
double mean_y(t_env *e);
double mean_z(t_env *e);
void rotation_x(t_env *e, double dir);
void rotation_y(t_env *e, double dir);
void rotation_z(t_env *e, double dir);
void perspective(t_env *e, double dir);
void scale(t_env *e, double factor);
void translation_h(t_env *e, double shift);
void translation_v(t_env *e, double shift);
void draw_tri(t_env *e);
void set_color_map(t_env *e, int get_next_map);
void reset_map(t_env *e);
void load_next_map(t_env *e);
char **extract_map_params(t_env *e, char **map);
void parse_map_data(t_env *e, char **map, char *num, int p);
void realloc_keys(t_env *e);
void my_loop(t_env *e);
int expose_hook(t_env *e);
int my_loop_hook(t_env *e);
void my_loop_hook_signed(t_env *e);
void my_loop_hook_unsigned(t_env *e);
int	my_mouse_motion(int x, int y, t_env *e);
int my_mouse_released(int button, int x, int y, t_env *e);
int my_mouse_function(int button, int x, int y, t_env *e);
int my_key_pressed(int keycode, t_env *e);
int my_key_recall(unsigned int keycode, t_env *e);
void my_key_recall_signed(unsigned int keycode, t_env *e);
void my_key_recall_unsigned(unsigned int keycode, t_env *e);
int my_key_funct(int keycode, t_env *e);
void apply_color_map(t_env *e, int color_map_index);
int dawn(int i);
int dusk(int i);
int kryptonite(int i);
int	dawn(int i);
int	red_blue(int i);
int	fire(int i);	
int	ice(int i);
int	seashore(int i);
int	kryptonite_center(int i);
int	seashore_center(int i);
int	fire_center(int i);
int	dawn_center(int i);
t_maps get_color_map(int i);

#endif
