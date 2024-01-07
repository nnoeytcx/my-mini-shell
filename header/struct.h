/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:11:36 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/07 21:27:42 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_environment
{
	char					*key;
	char					*value;
	struct s_environment	*next;
}	t_env;

typedef struct s_str_with_mode
{
	enum e_type				type;
	char					*value;
	struct s_str_with_mode	*next;
}	t_strm;

typedef struct s_amd
{
	struct s_str_with_mode	*str_mode;
	char					**command_line;
	char					**env;
	char					**path_env;
	char					*cmd_path;
	int						process_id;
	int						process_status;
	int						fd_in;
	int						fd_out;
	struct s_amd			*next;
}	t_cmd;

typedef struct s_token
{
	struct s_environment	*env_token;
	char					**env;
	char					*cur_input;
	int						return_code;
	int						command_count;
	char					*home_dir;
	struct s_amd			*command;
}	t_tok;

typedef struct s_exp
{
	char		*s;
	char		*new_str;
	char		tmp;
	int			i;
	int			*num;
}	t_exp;
#endif