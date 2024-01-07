/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:04:29 by tpoungla          #+#    #+#             */
/*   Updated: 2024/01/07 21:37:01 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	get_value_from_struct(t_strm *str_tab, t_tok *token)
{
	t_strm	*s;
	char	*str;

	s = str_tab;
	while (s)
	{
		str = s->value;
		printf("tab : {%s}\n", str);
		str = trim_and_expand(str, token);
		free(s->value);
		printf("new : %s\n", str);
		s->value = str;
		s->type = string;
		s = s->next;
	}
	return (0);
}

void	num_mode(int num[3], int mode, int i)
{
	if (mode == 1)
	{
		num[0] = 0;
		num[1] = 0;
		num[2] = 0;
	}
	else if (mode == 2)
	{
		num[2] = 1;
		num[0] = i + 1;
		num[1] = 0;
	}
	else if (mode == 3)
	{
		num[2] = 0;
		num[1] = 0;
	}
}

char	*find_dollarsign(char *str, t_tok *token)
{
	int		i;
	int		num[3];
	char	*new_str;

	i = -1;
	num_mode(num, 1, 0);
	new_str = ft_strdup("");
	while (str[++i])
	{
		num[1]++;
		if (str[i] == '$')
		{
			if (num[2] == 1)
				new_str = new_str_find(str, num, token, new_str);
			num_mode(num, 2, i);
		}
		if (is_submeta(str[i]) && num[1] && num[2])
		{
			new_str = new_str_find(str, num, token, new_str);
			num_mode(num, 3, i);
		}
		new_str = to_join(new_str, num[2], str[i]);
	}
	new_str = new_str_find2(str, num, token, new_str);
	return (new_str);
}

char	*get_expand(char *str_tab, t_tok *token)
{
	t_exp	*exp;

	exp->i = -1;
	init_arr_number(exp->num, 0, 0);
	exp->tmp = 0;
	exp->s = str_tab;
	exp->new_str = ft_strdup("");
	exp->new_str = out_get_expand(exp, token);
	exp->new_str = new_str_getex(exp->s, exp->num, token, exp->new_str);
	return (exp->new_str);
}

char	*trim_and_expand(char *str_tab, t_tok *token)
{
	char	*s;
	char	tmp;
	char	*new_str;
	int		i;
	int		num[2];

	i = -1;
	init_arr_number(num, 0, 0);
	tmp = 0;
	s = str_tab;
	new_str = ft_strdup("");
	while (s[++i])
	{
		num[0]++;
		if (is_quote(s[i]) && tmp == s[i])
		{
			if (tmp == '\"')
				new_str = get_newstr_expand(num, new_str, s, token);
			if (num[0] > 2 && tmp == '\'')
				new_str = joy_str(s, num, new_str);
			tmp = 0;
			init_arr_number(num, 0, i + 1);
			i++;
			continue ;
		}
		if (is_quote(s[i]) && tmp == 0)
			tmp = s[i];
		if ((!is_quote(s[i]) && tmp == 0) && (s[i + 1] && is_quote(s[i + 1])))
		{
			new_str = get_newstr_expand(num, new_str, s, token);
			tmp = 0;
			init_arr_number(num, 0, i + 1);
		}
	}
	if (num[0])
		new_str = get_newstr_expand(num, new_str, s, token);
	return (new_str);
}
