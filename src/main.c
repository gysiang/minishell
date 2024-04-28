/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/28 14:32:32 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***
for (int i = 0; s[i] != NULL; i++) {
	printf("av[%d]: %s\n", i, s[i]);
}; **/

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char		*line;
	t_token		*token_lst;
	t_ast_node	*ast_tree;

	using_history();
	setup_signal_handler();
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
		{
			printf("exit\n");
			break;
		}
		if (*line == '\0')
			continue;
		add_history(line);
		//printf("This is user input: %s\n", line);
		token_lst = token_processor(line);
		//print_tokenlst(token_lst);
		// make and print ast_tree
		ast_tree = make_ast_tree(token_lst);
		print_ast_tree(ast_tree);
		if (hist_feature(line) == 1)
			return (1);
		pipex(token_lst, env);
		free_tokenlst(token_lst);
		free_ast_tree(ast_tree);
	}
	return (0);
}
