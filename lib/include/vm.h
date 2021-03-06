/*
** main.h for main.h in /home/bridou_n//corewar
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Wed Jan 16 17:58:40 2013 nicolas bridoux
** Last update Sun Mar 31 19:35:18 2013 guillaume fillon
*/

#ifndef VM_H_
# define VM_H_

# include <stdio.h>
# include <stdlib.h>
# include "op.h"
# include "couleur.h"
# include <SDL/SDL.h>
# include <SDL/SDL_mixer.h>
# include <SDL/SDL_ttf.h>

# define READ		4096
# define WIDTH		1920
# define HEIGHT		1024
# define SIDEBAR_SIZE	172
# define MEM_OCTET	16
# define FONT_SIZE1	4 * 72
# define FONT_SIZE2	32

typedef	struct	s_prog
{
  char		*prog_name;
  int		prog_numb;
  int		load_add;
  int		debug;
  int		mem;
  int		dump;
}		t_prog;

typedef struct	s_options
{
  int		options;
  int		dump_nbr;
  int		prog_nbr;
  int		load_address;
}		t_options;

typedef struct	s_proc
{
  char		carry;
  int		code;
  char		cmd[17];
  int		reg[REG_NUMBER];
  int		pc;
  int		live;
  int		wait;
  int		num_proc;
  int		nb_proc;
  struct s_proc	*next;
  struct s_proc	*back;
}		t_proc;

typedef struct	s_sdl
{
  SDL_Surface	*screen;
  Mix_Music	*music;
}		t_sdl;

typedef struct	s_vm
{
  header_t	*header;
  int		old_live;
  int		nb_live;
  char		prg_nb;
  t_prog	*option;
  char		prg_alive[4];
  char		nbr_live;
  int		nb_proc;
  int		cycle;
  int		ctd;
  char		*mem;
  t_sdl		*sdl;
  int		cycle_champion[4];
  t_proc	*proc;
}		t_vm;

/*
** Parseur
*/
int		syntax_error(char *msg);
void		initialize_tab(t_prog *tab);
int		parsing_param(char **av, t_prog *tab, int dump);
int		my_get_nbr_hex(char *str);
int		fill_prog_tab(char **av, t_prog *tab, int rk, int ret);
int		fill_prog_name(char **av, t_prog *tab, int rk);
t_prog		prog_name(char **av);
t_prog		prog_number(char **av);
t_prog		load_address(char **av);
int		my_strcmp(char *a, char *b);
int		my_getnbr(char *str);
void		my_put_nbr(int nb);

/*
** sdl_gui.c
*/
SDL_Surface	*init_sdl(SDL_Surface *screen);
int		launch_sdl(t_sdl *sdl);
void	intro_corewar(TTF_Font *font, char *label, SDL_Surface *screen, int);

/*
** sdl_gui.c
*/
void		handle_event2(SDL_Event *event);
void		handle_event(SDL_Event *event, t_sdl *sdl);
void		sdl_free(Mix_Music *music);
Mix_Music	*play_music(Mix_Music *music);

/*
** display_intro.c
*/
void		display_intro(char *label, char type, SDL_Surface *screen);
void		display_sidebar(SDL_Surface *screen);
void		display_octet(SDL_Surface *screen, int color, int i, int j);
void		display_mem_grid(t_vm *vm, t_proc *lproc);

/*
** display_data.c
*/
void	display_data(SDL_Surface *sc, int value, char *(*f)(), char *name);
char	*display_nb_proc(char *name, int value, SDL_Rect *p);
char	*display_nb_live(char *name, int value, SDL_Rect *p);
char	*display_cycle(char *name, int value, SDL_Rect *p);
char	*display_ctd(char *name, int value, SDL_Rect *p);

/*
** misc
*/
void		free_champ(header_t *header, int nb);
void		free_vm(t_vm *vm);
void		my_putstr(char *str);
void		print_champion(int nb, t_vm *vm);
void		init_option_number_proc(t_proc *lproc , int option);

/*
** open_file.c
*/
int	open_file_champion(char *path, header_t *header);
char	*read_file(const int fd, int *nb_carac);
char	*get_champ(char *file, int *size);

/*
** wait_proc.c
*/
int		wait_proc(int nb_proc);

/*
** list.c
*/
t_proc	*suppr_elem_list(t_proc **, t_proc **);
int	free_elem_prog(t_proc **, int);
void	init_elem(t_proc **, int, int, int);
void	add_to_list(t_proc **, int, int);

/*
** check_header.c
*/
header_t	*check_header(const int fd, header_t *header);

/*
** set_carry.c
*/
void	set_carry(t_proc **, int);

/*
** fork.c
*/
t_proc	*add_fork(t_proc **, t_proc **);
void	init_new_proc(t_vm *, t_proc **, t_proc **, int);

/*
** vm_utils.c
*/
int	calc_interval(int nb_elem, int total_size);
void	reset_mem(t_vm **vm);
void	dump_memory(t_vm *vm);
void	init_reg(int *buf, int cid);

/*
** init_vm.c
*/
int	load_champ(char *file, t_vm **vm, header_t *header, int pos_mem);
t_vm	*init_vm(int mem_tmp, t_proc *lproc,
		 int prg_nb, header_t *header);
int	launch_vm(t_proc *l_proc, header_t *header, t_prog *tab, int nb_ch);

/*
** check_prog_live.c
*/
void	init_tab_live(char *);
void	gere_prog_live(char *, t_vm **);
int	check_prg_live(t_vm **);

/*
** parser.c
*/
void	parser(t_vm *vm, t_proc *l_proc, int add);

/*
** doubly linked list
*/
t_proc	*create_list(void);
void	free_proc(t_proc *lproc);
void	queue(t_proc **root, int pc, int cid);
void	pop(t_proc *elem);

/*
** display_intro.c
*/
void		display_champions(t_vm *vm);

/*
** run_cycle.c
*/
void	reset_live_prg(t_vm **vm);
void	sync_cycle(t_vm *vm);
int	handle_schedule(t_vm **vm);
int	exec_instruction(t_vm *vm, t_proc **proc);
int	get_cmd(char code);

/*
** instruction / interval_mem.c
*/
int	interval_memory(char *cmd, int i, int interval, int indice);
int	return_param_op(t_proc **lproc, int *indice, t_vm *vm, int offset);
int	check_carry_champion(t_proc *ptete, int num_champion);
void	load_reg(t_vm *, t_proc **, char *, int *);
void	get_adress_st(t_vm *, t_proc **, int *);
void	set_ld(t_vm *, t_proc **, int);
int	get_adress_reg(t_vm *, t_proc **, int *);
int	get_direct_reg(t_vm *, t_proc **, int *);
void	get_reg_reg(t_vm *, t_proc **, int *, char *);
int	get_direct_ldi(t_vm *, t_proc **, int, int *);
int	get_adress_ldi(t_vm *, t_proc **, int, int *);
void	debug(t_vm *, t_proc **, int);
void	print_debug(int, char *, int);
int	get_last_num_proc(t_vm *, int);
void	init_cmd_proc(t_vm *);

/*
** init_memory.c
*/
void		reset_mem(t_vm **);
void		init_memory_by_zero(t_vm **);
void		init_memory_by_random(t_vm **, int);

#endif /* VM_H_ */
