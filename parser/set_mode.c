/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:04:05 by tpoungla          #+#    #+#             */
/*   Updated: 2024/01/07 16:45:06 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	set_mode(t_strm *str)
{
	t_strm	*stm;

	if (!str)
		return (-1);
	stm = str;
	while (stm)
	{
		if (stm->type == string)
		{
			if (is_same_str(">", stm->value))
				set_type(stm, redout_symbol, file_out_str);
			else if (is_same_str("<", stm->value))
				set_type(stm, redin_symbol, file_in_str);
			else if (is_same_str("<<", stm->value) || \
			is_same_str("<<<", stm->value))
				set_type(stm, h_doc_symbol, h_doc_cut_str);
			else if (is_same_str(">>", stm->value))
				set_type(stm, append_symbol, file_out_append_str);
		}
		dprintf(2, "set [%s] to [%d] mode\n", stm->value, stm->type);
		stm = stm->next;
	}
	return (1);
}

int	ft_isspace(char c)
{
	if (c == '\r' || c == '\n' || c == '\f' )
		return (1);
	else if (c == '\v' || c == '\t' || c == ' ' )
		return (1);
	return (0);
}

int	is_meta(char c)
{
	if (c == '|' || c == '>' || c == '<' )
		return (1);
	return (0);
}

char	*new_str_find(char *s, int num[3], t_tok *tok, char *new)
{
	int		k;
	int		len;
	char	*substr;
	char	*tmpstr;

	k = num[0];
	len = num[1] - 1;
	if (!len)
		return (new);
	substr = ft_substr(s, k, len);
	tmpstr = get_new_str(substr, tok);
	free(substr);
	substr = new;
	new = ft_strjoy(substr, tmpstr);
	free(tmpstr);
	free(substr);
	return (new);
}

char	*new_str_find2(char *s, int num[3], t_tok *tok, char *new)
{
	int		k;
	int		len;
	char	*substr;
	char	*tmpstr;

	k = num[0];
	len = num[1];
	if (!num[1] || !num[2])
		return (new);
	substr = ft_substr(s, k, len);
	tmpstr = get_new_str(substr, tok);
	free(substr);
	substr = new;
	new = ft_strjoy(substr, tmpstr);
	free(tmpstr);
	free(substr);
	return (new);
}
