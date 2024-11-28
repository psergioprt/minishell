/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:49:08 by jcavadas          #+#    #+#             */
/*   Updated: 2024/11/28 16:02:03 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// void    echo(t_node *data)
// {
//     //Dar handle a ' -> nao tem de expandir a variavel, copia literalmente o que tem la '\t', '\n', etc... incluido
//     //Dar handle a " -> Tem de expandir variavel mas copia tambem os "\t", "\n", etc...
//     //Detect $VARS e trocar pelo valor dela com get_env()
//     //Dar handle a -n ou -e
		
// }


// Function to write a string to standard output using `write`
void write_string(const char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

// Expands variables starting with `$`
void expand_variable(const char *input, char *output) {
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
			printf("get_env is getting %s\n", var_name);
            const char *value = getenv(var_name);
			printf("get_env is giving %s\n", value);
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
                    expand_variable(src, expanded);
                    size_t len = strlen(expanded);
                    for (size_t i = 0; i < len; i++) {
                        *dest++ = expanded[i];
                    }
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
                expand_variable(src, expanded);
                size_t len = strlen(expanded);
                for (size_t i = 0; i < len; i++) {
                    *dest++ = expanded[i];
                }
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

// Custom echo function to handle a linked list of tokens
void custom_echo(t_node *data) {
    int first = 1; // Flag to manage space placement
	data = data->next;
    while (data) {
        char processed[1024];
        handle_quotes(data->token, processed); // Process each token

        if (!first) {
            write(1, " ", 1); // Add space before every token except the first
        }
        write_string(processed);
        first = 0;

        data = data->next; // Move to the next node
    }
    write(1, "\n", 1); // Print newline at the end
}