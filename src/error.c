#include "../inc/cub3d.h"

void	ft_error(char *err_msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(1);
}

void	error_free(char *err_msg, t_hold *hold)
{
	(void)hold;
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);

	//close_and_free(hold);
	exit(1);
}
