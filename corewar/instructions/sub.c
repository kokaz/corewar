#include "lib.h"
#include "vm.h"

void		op_sub(t_vm *vm, t_proc **lproc)
{
  debug(vm, lproc, -1);
  if ((*lproc)->cmd[1] > 16 || (*lproc)->cmd[2] > 16 || (*lproc)->cmd[3] > 16)
    {
      (*lproc)->pc += 1;
      return ;
    }
  (*lproc)->reg[(int)((*lproc)->cmd[3] - 1) % REG_NUMBER] =
    (*lproc)->reg[(int)(((*lproc)->cmd[1] - 1) & 0xFF) % REG_NUMBER] -
    (*lproc)->reg[(int)(((*lproc)->cmd[2] - 1) & 0xFF) % REG_NUMBER];
  if (vm->option[0].debug != -1)
    print_debug((*lproc)->reg[(int)((*lproc)->cmd[3] - 1) % REG_NUMBER],
		"result : ", 0);
  set_carry(lproc,
	    (*lproc)->reg[(int)(((*lproc)->cmd[3] - 1) & 0xFF) % REG_NUMBER]);
  (*lproc)->pc += interval_memory((*lproc)->cmd, (*lproc)->code, 0, 0);
 }
