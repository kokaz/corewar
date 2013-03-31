/*
** check_prog_live.c for check_prog_live in /home/remi/Projet/corewar/corewar/corewar
**
** Made by remi
** Login   <remi@epitech.net>
**
** Started on  Mon Mar 11 08:18:24 2013 remi
** Last update Sun Mar 31 16:54:34 2013 guillaume fillon
*/

#include "lib.h"
#include "vm.h"
#include "couleur.h"
#include "instructions/instruction.h"

void	init_tab_live(char *tab)
{
  tab[0] = -1;
  tab[1] = -1;
  tab[2] = -1;
  tab[3] = -1;
}

void		gere_prog_live(char *live, t_vm **vm)
{
  int		indice;
  int		suppr;

  indice = 0;
  suppr = 0;
  while (indice < (*vm)->prg_nb)
    {
      if (live[indice] == 0)
	{
	  suppr = suppr + 1;
	  while (free_elem_prog(&((*vm)->proc), indice + 1) == 1);
	}
      ++indice;
    }
  (*vm)->prg_nb = (*vm)->prg_nb - suppr;
}

int	get_condition_count(int count, t_vm *vm)
{
  static SDL_Color	color = {0, 255, 0};
  TTF_Font		*font288;
  SDL_Surface		*surface;
  SDL_Rect		pos;

  if (count == 0)
    {
      if (vm->old_live != -1)
	print_champion(count, vm);
      else
	{
	  font288 = TTF_OpenFont("game_over.ttf", 288);
	  surface = TTF_RenderText_Blended(font288, "No winner", color);
	  pos.x = (WIDTH / 2) - (surface->w / 2);
	  pos.y = (HEIGHT / 2) - (surface->h / 6) + 50;
	  SDL_BlitSurface(surface, NULL, vm->sdl->screen, &pos);
	  SDL_FreeSurface(surface);
	  TTF_CloseFont(font288);
	  SDL_Flip(vm->sdl->screen);
	  my_putstr("Aucun gagnant\n");
	}
      return (1);
    }
  return (0);
}

int		there_is_last_champ(char *live, t_vm *vm)
{
  int		i;
  int		count;

  count = 0;
  i = 0;
  while (i < 4)
    {
      if (live[i] > 0)
	++count;
      ++i;
    }
  if (count == 1)
    {
      count = 0;
      i = 0;
      while (i < 4)
  	{
  	  if (live[i] > 0)
  	    count = i;
  	  ++i;
  	}
      print_champion(count, vm);
      return (1);
    }
  return (get_condition_count(count, vm));
}

int		check_prg_live(t_vm **vm)
{
  t_proc	*cur_proc;
  char		live[4];

  init_tab_live(live);
  if ((*vm)->proc == NULL)
    return (0);
  cur_proc = (*vm)->proc;
  while (cur_proc != NULL)
    {
      if  (cur_proc->live == 1)
	live[cur_proc->nb_proc % 4] = cur_proc->live;
      cur_proc = cur_proc->next;
    }
  gere_prog_live(live, vm);
  if (there_is_last_champ(live, *vm))
    return (0);
  return (1);
}
