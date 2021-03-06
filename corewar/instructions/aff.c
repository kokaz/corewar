#include "lib.h"
#include "vm.h"
#include "couleur.h"

/*
** affiche la valeur ascii contenu dans un registre
*/
void		op_aff(t_vm *vm, t_proc **lproc)
{
  debug(vm, lproc, -1);
  if ((*lproc)->cmd[1] > 16)
    {
      (*lproc)->pc += 1;
      return ;
    }
  if ((*lproc)->cmd[1] - 1 < 0)
    (*lproc)->cmd[1] = REG_NUMBER - (*lproc)->cmd[1];
  my_putchar((*lproc)->reg[((int)(((*lproc)->cmd[1] - 1) & 0xFF))
			   % REG_NUMBER]);
  (*lproc)->pc += interval_memory((*lproc)->cmd, (*lproc)->code, 0, 0);
}
