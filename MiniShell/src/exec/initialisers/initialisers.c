/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:07:20 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/24 14:24:51 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "minishell.h"

void	init_cmd_args_fill(t_mo_shell *mo_shell, t_block **nav_block, \
	t_cmd **nav_cmd, bool *block_has_cmd)
{
	*nav_cmd = mo_shell->cmds_table;
	*nav_block = mo_shell->splitted_input;
	*block_has_cmd = false;
}

t_cmd	*init_exec_seq(t_mo_shell *mo_shell, t_pipes *pipes, t_pids *pids)
{
	t_cmd	*to_launch;
	t_cmd	*nav;

	to_launch = mo_shell->cmds_table;
	nav = to_launch;
	nav->cp_i = dup(STDIN_FILENO);
	nav->cp_o = dup(STDOUT_FILENO);
	while (nav)
	{
		ft_memset(pids->pid, 0, sizeof(pids->pid));
		ft_memset(pipes->pipe, -1, sizeof(pipes->pipe));
		pipes->pipe_i = -1;
		pids->pid_i = -1;
		if (nav->hd_fn)
			nav->fd_i = open(nav->hd_fn, O_RDONLY);
		nav = nav->next;
	}
	return (to_launch);
}

t_block	*init_spl_to_cmdb(t_cmd **ret, t_cmd **tmp, int *number_of_cmds, \
	t_block **head)
{
	t_block	*nav;

	*ret = NULL;
	*tmp = NULL;
	*number_of_cmds = 1;
	nav = *head;
	return (nav);
}

int	init_hd_fork(int *hd_pid, int *exit_status)
{
	*hd_pid = fork();
	*exit_status = 0;
	return (1);
}

int	init_open_file_hd(int *array, t_cmd *nv_c)
{
	array[HEREDOC_PID] = 0;
	array[EXT_STS] = 0;
	array[STATUS] = 0;
	if (nv_c->hd_fn)
		(free(nv_c->hd_fn), nv_c->hd_fn = NULL);
	nv_c->fd_i = numerator(&nv_c->hd_fn);
	close(nv_c->fd_i);
	nv_c->fd_i = open(nv_c->hd_fn, O_CREAT | O_RDWR);
	return (1);
}
