/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:45:31 by jcavadas          #+#    #+#             */
/*   Updated: 2025/01/08 11:09:05 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void write_string(const char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

// Expands variables starting with `$`
void expand_variable(const char *input, char *output)
{
	const char *src = input;
	char *dest = output;

	while (*src) {
		if (*src == '$') {
			src++; // Skip the `$`
			// Extract the variable name
			const char *start = src;
			while (*src && (isalnum(*src) || *src == '_')) {
				src++;
			}
			size_t var_len = src - start;
			char var_name[256];
			strncpy(var_name, start, var_len);
			var_name[var_len] = '\0';

			// Get the variable value from the environment
			const char *value = getenv(var_name);
			if (value) {
				while (*value) {
					*dest++ = *value++;
				}
			}
		} else {
			*dest++ = *src++; // Copy other characters as-is
		}
	}
	*dest = '\0'; // Null-terminate the output string
}

// Handles single and double quotes in arguments
// Handles single and double quotes in arguments
void handle_quotes(const char *input, char *output) {
	const char *src = input;
	char *dest = output;

	while (*src) {
		if (*src == '\'') {
			// Single-quoted string: copy literally
			src++; // Skip opening quote
			while (*src && *src != '\'') {
				*dest++ = *src++;
			}
			if (*src == '\'') {
				src++; // Skip closing quote
			}
		} else if (*src == '"') {
			// Double-quoted string: expand variables
			src++; // Skip opening quote
			while (*src && *src != '"') {
				if (*src == '$') {
					char expanded[1024];
					//const char *start = src; // Save position in case of error
					expand_variable(src, expanded); // Expand the variable
					size_t len = strlen(expanded);
					for (size_t i = 0; i < len; i++) {
						*dest++ = expanded[i];
					}
					// Move `src` past the variable name
					src++;
					while (*src && (isalnum(*src) || *src == '_')) {
						src++;
					}
				} else {
					*dest++ = *src++;
				}
			}
			if (*src == '"') {
				src++; // Skip closing quote
			}
		} else {
			// No quotes: expand variables
			if (*src == '$') {
				char expanded[1024];
				expand_variable(src, expanded); // Expand the variable
				size_t len = strlen(expanded);
				for (size_t i = 0; i < len; i++) {
					*dest++ = expanded[i];
				}
				// Move `src` past the variable name
				src++;
				while (*src && (isalnum(*src) || *src == '_')) {
					src++;
				}
			} else {
				*dest++ = *src++;
			}
		}
	}
	*dest = '\0'; // Null-terminate the output string
}

//TODO: mudar a logica para o novo metodo de parsing que vamos ter

// Custom echo function to handle a linked list of tokens
int custom_echo(t_minishell *mini)
{
	int 	first; // Flag to manage space placement
	int		i;
	t_node	*node;
	bool	has_flag;

	first = 1;
	i = 0;
	has_flag = false;
	node = mini->tokenlst;
	node = node->next;
	while (node && node->token[i] == '-' && node->token[i + 1] == 'n' && !(node->token[i + 2]))
	{
		has_flag = true;
		node = node->next;
	}
	while (node)
	{
		char processed[1024];
		handle_quotes(node->token, processed); // Process each token

		if (!first) {
			write(1, " ", 1); // Add space before every token except the first
		}
		write_string(processed);
		first = 0;

		node = node->next; // Move to the next node
	}
	if (!has_flag)
		write(1, "\n", 1); // Print newline at the end
	return (1);
}
