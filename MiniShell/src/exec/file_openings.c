/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_openings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:19:36 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/23 17:22:48 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

static void	handle_hd_sigint(int code)
{
	(void)code;
	g_signal_id = 128 + 2;
	printf("\n");
	clear_rl_line();
	close(STDIN_FILENO);
}

///
/// @param nav_cmd
/// @param nav_block
/// @param mo_shell
/// @return
t_error	heredoc_fork(t_cmd *nav_cmd, t_block *nav_block, t_mo_shell *mo_shell)
{
	heredoc_handler(nav_block, nav_cmd, mo_shell);
	exit (EXIT_SUCCESS);
}

///
/// @param nav_block
/// @param nv_c
/// @param mode
/// @param mo_shell
/// @return
t_error	open_file_hd(t_block *nav_block, t_cmd *nv_c, t_mo_shell *mo_shell)
{
	int	array[3];

	init_open_file_hd(array, nv_c);
	array[HEREDOC_PID] = fork();
	if (array[HEREDOC_PID] == -1)
		return (err_msg(FORK_ERR_MSG, NULL), ERROR);
	if (array[HEREDOC_PID] == 0)
		(signal(SIGINT, &handle_hd_sigint), \
			heredoc_fork(nv_c, nav_block, mo_shell));
	else if (array[HEREDOC_PID] != 0)
	{
		close(nv_c->fd_i);
		if (waitpid(array[HEREDOC_PID], &array[STATUS], 0) == -1)
			(perror("waitpid"), exit(EXIT_FAILURE));
		if (WTERMSIG(array[STATUS]))
			array[EXT_STS] = 128 + WTERMSIG(array[STATUS]);
		else if (WIFEXITED(array[STATUS]))
			array[EXT_STS] = WEXITSTATUS(array[STATUS]);
		if (array[EXT_STS] != 0)
			return (mo_shell->les = array[EXT_STS], ERROR);
		if (nv_c->fd_i != STDIN_FILENO)
			(close(nv_c->fd_i), nv_c->fd_i = STDIN_FILENO);
	}
	return (mo_shell->les = 0, NO_ERROR);
}

/**
 * @brief 
 *
 * @param nav_block 
 * @param nav_cmd 
 * @param mode 1 = INPUT ; 2 = HEREDOC
 * @return 
 */
t_error	open_file_in(t_block *nav_block, t_cmd *nav_cmd)
{
	if (nav_cmd->fd_i != STDIN_FILENO)
		(close(nav_cmd->fd_i), nav_cmd->fd_i = STDIN_FILENO);
	nav_cmd->fd_i = open(nav_block->str, O_RDWR);
	if (nav_cmd->fd_i < 0)
		return (ERROR);
	return (NO_ERROR);
}

/// @brief 
/// @param nav_block
/// @param nav_cmd 
/// @param mode 1 == truncate ; 2 == append
/// @return 
t_error	open_file_out(t_block *nav_block, t_cmd *nav_cmd, int mode)
{
	if (mode == 1)
	{
		if (nav_cmd->fd_o != STDOUT_FILENO)
			(close(nav_cmd->fd_o), nav_cmd->fd_o = STDOUT_FILENO);
		nav_cmd->fd_o = open(nav_block->str, O_RDWR | O_CREAT | O_TRUNC, \
			0666);
		if (nav_cmd->fd_o < 0)
			return (ERROR);
		write(nav_cmd->fd_o, "", 0);
	}
	if (mode == 2)
	{
		if (nav_cmd->fd_o != STDOUT_FILENO)
			(close(nav_cmd->fd_o), nav_cmd->fd_o = STDOUT_FILENO);
		nav_cmd->fd_o = open(nav_block->str, O_RDWR | O_APPEND | O_CREAT, \
			0666);
		if (nav_cmd->fd_o < 0)
			return (ERROR);
	}
	return (NO_ERROR);
}
