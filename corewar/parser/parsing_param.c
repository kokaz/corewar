#include "lib.h"
#include "vm.h"

int	syntax_error(char *msg)
{
  write(2, msg, my_strlen(msg));
  return (-1);
}

void	initialize_tab(t_prog *tab)
{
  int	rk;

  rk = -1;
  while (++rk < 4)
    {
      tab[rk].prog_name = NULL;
      tab[rk].prog_numb = -1;
      tab[rk].load_add = -1;
      tab[rk].debug = 1;
      tab[rk].mem = -1;
      tab[rk].dump = -1;
    }
}

int	parsing_param(char **av, t_prog *tab, int dump)
{
  int	rk;
  int	j;

  rk = -1;
  j = 0;
  while (av[++rk])
    {
      if (!my_strcmp(av[rk], "-dump"))
	{
	  if (av[++rk])
	    dump = my_getnbr(av[rk]);
	  else
	    return (syntax_error("Syntax error.\n"));
	}
      else
	{
	  if ((j = fill_prog_tab(&av[rk], tab, j, 0)) == -1)
	    return (-1);
	  if (av[rk][0] == '-' && av[rk][1] && (av[rk][1] != 'v') &&
	      (av[rk][1] != 'z'))
	    ++rk;
	}
    }
  return (dump);
}
