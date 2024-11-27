#include "../include/minishell.h"

//function created to create nodes
t_node *create_command_node(const char *command)
{
	t_node	*new_node;
	new_node = malloc(sizeof(t_node));
	if (!new_node)
	{
		perror("Error!\nFailed to allocate memory for new_node\n");
		return (NULL);
	}
	new_node->command = ft_strdup(command);
	new_node->next = NULL;
	return (new_node);
}
//function created to add commands to linked list
void	add_command_node(t_node **list, const char *command)
{
	t_node	*new_node;
	t_node	*current;

	new_node = create_command_node(command);
	if (!new_node)
		return ;
	if (!*list)
	{
		printf("Point 2: %s\n", command);
		*list = new_node;
	}
	else
	{
		printf("Point 3: %s\n", command);
		current = *list;
		while (current->next)
			current = current->next;
		current->next = new_node;
		printf("added command to list: %s\n", command);
	}
}

static int	is_delimeter(char c, const char *delim)
{
	while(*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

char	*ft_strtok(char *str, const char *delim)
{
	static	char	*cur = NULL;
	char		*token_start;

	if (str != NULL)
		cur = str;
	if (cur == NULL)
		return (NULL);
	while (*cur && is_delimeter(*cur, delim))
	{
		if (*cur == '|')
		{
			cur++;
			return (ft_strdup("|"));
		}
		else if((*cur == '>' && *(cur + 1) == '>') || (*cur == '<' && *(cur + 1) == '<'))
		{
			char	double_char[3] = {*cur, *(cur + 1), '\0'};
			cur += 2;
			return (ft_strdup(double_char));
		}
		else if (*cur == '>' || *cur == '<')
		{
			char	single_char[2] = {*cur, '\0'};
			cur++;
			ft_strdup(single_char);
		}
		else
			cur++;
	}
	if (*cur == '\0')
		return (NULL);
	token_start = cur;
	while (*cur && !is_delimeter(*cur, delim))
	{
		if (*cur == '\\') // Handle escape character
			cur += 2; // Skip escaped character
		else if (*cur == '"' || *cur == '\'') // Handle quoted strings
			{
				char quote = *cur++;
				while (*cur && *cur != quote)
					cur++;
				if (*cur)
					cur++; // Skip closing quoteui
			}
		else
			cur++;
	}
	if (*cur)
	{
		*cur = '\0';
		cur++;
	}
	else
		cur = NULL;
	return (token_start);
}

//function created to split each command from an input
void	split_and_add_commands(t_node **list, const char *input)
{
	char	*token;
	char	*delimeters = "| \"";
	char	*input_copy = ft_strdup(input);

	free_list(*list);
	*list = NULL;

	token = ft_strtok(input_copy, delimeters);
	while (token != NULL)
	{
		add_command_node(list, token);
		token = ft_strtok(NULL, delimeters);
	}
	free(input_copy);
}
//function created to free the linked list
void	free_list(t_node *list)
{
	t_node	*current;
	while (list)
	{
		current = list;
		list = list->next;
		free(current->command);
		free(current);
	}
}
