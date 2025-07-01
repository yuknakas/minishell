/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raosmona <raosmona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:51:22 by yuknakas          #+#    #+#             */
/*   Updated: 2025/07/01 15:28:54 by raosmona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Standard C libraries
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// File & Directory
# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>

// Process control
# include <signal.h>
# include <sys/wait.h>

// Terminal & Readline
# include <readline/history.h>
# include <readline/readline.h>
# include <term.h>
# include <termios.h>

#endif