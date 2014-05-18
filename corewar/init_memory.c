#include "lib.h"
#include "vm.h"

/*
** init la memoire d une incrementation passer en option -m
*/
void	init_memory_by_random(t_vm **vm, int max)
{
  int	i;
  int	val;

  i = 0;
  val = 1;
  while (i < MEM_SIZE)
    {
      (*vm)->mem[i++ % MEM_SIZE] = val;
      val += 1;
      if (val == max)
	val = 1;
    }
}

/*
** initialise la vm à 0
*/
void	init_memory_by_zero(t_vm **vm)
{
  int	i;

  i = 0;
  while (i < MEM_SIZE)
    (*vm)->mem[i++ % MEM_SIZE] = 0x0;
}

void	reset_mem(t_vm **vm)
{
  if ((*vm)->option[0].mem == -1)
    init_memory_by_zero(vm);
  else
    init_memory_by_random(vm, (*vm)->option[0].mem);
}
