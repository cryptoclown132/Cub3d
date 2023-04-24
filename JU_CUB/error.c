/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:31:07 by jkroger           #+#    #+#             */
/*   Updated: 2023/04/14 15:55:32 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *err_msg)
{
	printf("Error: %s\n", err_msg);
	exit(1);
}

void	error_free(char *err_msg, t_cub *cub)
{
	printf("Error: %s\n", err_msg);
	close_and_free(cub);
	exit(1);
}
