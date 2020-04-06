/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 13:36:17 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/03 10:39:12 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>

# define FLAG "RNSWEFC"
# define MAP "012NSWE "

# define R 1
# define NO 2
# define SO 4
# define WE 8
# define EA 16
# define S 32
# define F 64
# define C 128
# define PLAYER 256
# define NORTH 512
# define SOUTH 1024
# define WEST 2048
# define EAST 4096
# define MAP_ON 8192
# define MAP_OFF 16384
# define TAILLE_MAX_X 2560
# define TAILLE_MAX_Y 1440
# define POV 0.58
# define MOVESPEED 0.1
# define ROTSPEED 0.1
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define SAVE "save.bmp"
//# define MAX_NUMBER_OF_SPRITE 100

enum {N_FACE, S_FACE, W_FACE, E_FACE};
enum {EMPTY, WALL, SPRITE, ME};

typedef struct	s_save
{
	int				h;
	int				w;
	int				pad;
	unsigned char	file_header[14];
	unsigned char	img_header[40];
	int				fd;
}				t_save;

typedef struct	s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}				t_color;

typedef struct s_imagedata
{
	void	*img;
	char	*addr;
	int		bit_per_pixel;
	int		line_length;
	int		endian;
}				t_imagedata;

typedef struct	s_xy
{
	double		x;
	double		y;
}				t_xy;

typedef	struct	s_map
{
	int			column;
	int			line;
	char		*map;
}				t_map;

typedef struct	s_move
{
	int			up;
	int			down;
	int			rot_l;
	int			rot_r;
	int			right;
	int			left;
}				t_move;

typedef	struct	s_data
{
	//partie parsing
	short int	flag;
	t_xy    	screen;//definition ecran
	t_xy    	pos;//position joueur
	t_xy    	dir;//direction joueur
	t_xy		plane;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*sprite;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
	int			error;
	int			numsprite;
	t_xy		*spritepos;

	//partie graphique
	void    	*mlx;
	void    	*win;
	t_imagedata	img;
    double  	camerax;//rayon / ecran
    t_xy    	raydir;//vecteur rayon
    int     	mapx;//dans quelle case nous sommes (determine side dist)
    int     	mapy;
    t_xy    	sidedist;//length of ray jusqu'au prochain bord
    t_xy    	deltadist; //longueur ray jusqu'à prochain x y  side
    double  	perpwalldist;
    int     	stepx;//direction to step 9 +
    int     	stepy;
    int     	hit;
    int     	side;//quel mur touche ?
    int     	lineheight;
    int     	drawstart;
    int			drawend;
    int			wallcolor;//a remplacer ensuite par texture
    double		movespeed;
    double  	rotspeed;
	int			save;
	t_imagedata	texeast;
	t_imagedata	texsouth;
	t_imagedata texnorth;
	t_imagedata texwest;
	t_imagedata currenttex;
	t_imagedata	texsprite;
	double		wallx; // where the wall was hit
	int			texx; // x coordinate of texture
	double		step; //step in texture y
	double		texpos; //texture coordinate
	int			texy;//coordonnee caste en int
	double		zbuffer[TAILLE_MAX_X];//1DZbuffer
	int			*spriteorder;
	double		*spritedistance;
	double		spritex;
	double		spritey;
	//double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spriteheight;
	int			drawstarty;
	int			drawendy;
	int			spritewidth;
	int			drawstartx;
	int			drawendx;
	t_move		move;
}				t_data;



/*
** libft
*/
int				ft_printf(const char *text, ...);
int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_strlen(const char *s);
int				get_next_line(int fd, char **line);
char			*ft_strtrim(char const *s1, char const *set);
int				ft_isinstring(int c, char *str);
char			*ft_strdup(const char *s1);
int				ft_isspace(int c);
int				ft_atoi(const char *str);
char			**ft_split(char const *s, char c);
int				ft_isdigit(int c);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_putstr_fd(char *s, int fd);


/*
** check_file.c
*/
int				check_name(char *arg);
int				check_argument_error(int argc, char *argv[], t_data *data);
int				check_file(int fd, t_data *data);

/*
** errors.c
*/
int				error_freestruct(t_data *data, int errornb, int ret, char* line);
void			error_freestruct_fd(t_data *data, int fd, int errornb);
int				display_error(int errornbr);

/*
** floor_and_ceiling.c
*/
int				ceiling_data(char *line, t_data *data);
int				floor_data(char *line, t_data *data);

/*
** graphic_part.c
*/
void			opening(t_data *data);
void			variable_value(t_data *data, int x);
void			step_and_initial_sidedist(t_data *data);
void			perform_dda(t_data *data);
void			calculate_distance(t_data *data);
void			calculate_column(t_data *data);
void			wall_color(t_data *data);
int 			deal_key(int key, void *param, t_data *data);
void			petitmain();
void    		calculate_wallx_and_x_text(t_data *data);
int 			find_textel_color_and_put(t_data *data, int x, t_imagedata *img);
void    		wall_color_tex(t_data *data);




/*
** map.c
*/
char			*parsing_line(char *line);
int				map_writing(char *line, t_data *data);
int				first_line_map(char *line, t_data *data);
int				create_map(t_map *map, int w, int h);

/*
** move.c
*/
void			forward(t_data *data);
void			backward(t_data *data);
void			sideleft(t_data *data);
void			sideright(t_data *data);
void 			rotation_right(t_data *data);
void 			rotation_left(t_data *data);
int				move(t_data *data);
int				let_s_move(t_data *data);



/*
** player_vector_init
*/
void			player_vectors_init(t_data *data, char direction, int i);

/*
** read_line.c
*/
int				read_line(char *line, t_data *data, int fd, int ret);

/*
** resolution.c
*/
int				resolution_data(char *line, t_data *data);

/*
** sprite_texture.c
*/
int				sprite_texture_data(char *line, t_data *data);

/*
** struct_gestion.c
s*/
void			free_struct(t_data *data);
void			initialize_struct(t_data *data);

/*
** wall_texture.c
*/
int				texture_ea_data(char *line, t_data *data);
int				texture_no_data(char *line, t_data *data);
int				texture_so_data(char *line, t_data *data);
int				texture_we_data(char *line, t_data *data);

/*
** my_mlx_color_fonctions
*/
int				create_color_int(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
/*
** my_mlx_image_fonctions
*/
void			my_mlx_pixel_put(t_imagedata *img, int x, int y, int color);
int				my_texcolor_extractor(t_imagedata *img, int x, int y);

/*
** let_s_play.c
*/
int				let_s_play(t_data *data);
int				keyboard(int keycode, t_data *data);
int				closing(t_data *data);
int				zobizobi(t_imagedata *img, t_data *data);


/*
** texture_image.c
*/
int				texture_creation(t_data *data);
int				create_img_east(t_data *data);
int				create_img_north(t_data *data);
int				create_img_west(t_data *data);
int				create_img_south(t_data *data);
int				create_img_sprite(t_data *data);

/*
**	sort_sprite.c
*/
void			sort_sprite(t_data *data);
void			sprite_height_width(t_data *data);
void			transform_sprite(t_data *data, int i);
void 			sprite_drawing_loop(t_data *data, t_imagedata *img);
int				sprite_drawing(t_data *data, t_imagedata *img);
/*
**  check_map.c
*/
int				check_map(t_data *data, int w, int h);
int				check_point(t_data *data, int i, int *j);
int				create_sprite_data(t_data *data, int n);
/*
**  save.c
*/
void			set_in_char(unsigned char *start, int n);
void			create_file_header(t_data *data, int pad, unsigned char *fileheader);
void			create_img_header(int h, int w, int pad, unsigned char *header);
int				init_save(t_data *data, t_save *save);
int				write_header(t_save *save);
unsigned char	*put_bgr(t_data *data, int x, int y, unsigned char *bgr);
int				write_picture(t_save *save, t_data *data);
int				ft_save(t_data *data);		//renvoie 22 si ouvertureko, 23 si ecriture ko

/*
//	keys.c
*/
int				hit_key(int	key, t_data *data);
int				release_key(int	key, t_data *data);


#endif
