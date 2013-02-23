/*
** lldi.c for Corewar in /home/fillon_g/projets/groups/corewar/corewar/instructions
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Mon Jan 28 20:27:49 2013 guillaume fillon
** Last update Sat Feb 23 12:29:04 2013 remi robert
*/

#include "lib.h"
#include "vm.h"

void		op_lldi(t_vm *vm, t_proc *lproc)
{
  printf("%sLLDI%s\n", F_CYAN, REZ);
  lproc->pc += interval_memory(lproc->cmd, 0, 0, 0);
}
