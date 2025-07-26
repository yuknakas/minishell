#include "../../include/minishell.h"

int main(int ac, char **av)
{
	t_token *token_list;

	if (ac != 2)
		return (1);
	token_list = make_token_list(av[1]);
	while (token_list != NULL)
	{
		printf("%s\n",token_list->line);
		token_list = token_list->next;
	}
	return 0;
}
