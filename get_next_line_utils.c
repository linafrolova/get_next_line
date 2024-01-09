/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrolova <lfrolova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:00:01 by lfrolova          #+#    #+#             */
/*   Updated: 2024/01/09 22:51:09 by lfrolova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include <string.h>

char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (dest[i] != '\0')
		++i;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		++j;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dest;
	// Calculate the length of the input string
	i = 0;
	while (s[i] != '\0')
		i++;

	// Allocate memory for the destination string
	dest = (char *)malloc((i + 1) * sizeof(char));
	// Check if memory allocation was successful
	if (!dest)
		return (NULL);
	// Copy the characters from the source to the destination
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	// Add the null terminator to the destination string
	dest[i] = '\0';
	// Return the pointer to the duplicated string
	return (dest);
}

void append_node(t_buffer **head, char *str_buf) {
    t_buffer *last_node;
    t_buffer *new_node;

    new_node = malloc(sizeof(t_buffer));
    if (new_node == NULL)
        return;
    new_node->data = ft_strdup(str_buf);  
    new_node->next = NULL;
    if (*head == NULL)
        *head = new_node;
    else {
        last_node = *head;
        while (last_node->next != NULL)
            last_node = last_node->next;
        last_node->next = new_node;
    }
}

int is_newline(char *str_buf)
{
    char *tmp = str_buf;
    
    while (*tmp != '\0')
    {
        if (*tmp == '\n')
            return 1;
        tmp++;
    }
    return 0; 
}

void create_list(t_buffer **list, int fd) 
{
    char buffer[BUFFER_SIZE + 1];
    ssize_t bytesRead;
    int foundNewline = 0;

    while (!foundNewline && (bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) 
    {
        buffer[bytesRead] = '\0';
        append_node(list, buffer);

        if (is_newline(buffer))
            foundNewline = 1;
    }
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	destlen;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (!dest)
		destlen = 0;
	else
		destlen = ft_strlen(dest);
	if (destlen >= size)
	{
		destlen = size;
		return (destlen + srclen);
	}
	while (destlen + i < size - 1 && src[i] != '\0')
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (destlen + srclen);
}

char *get_line(t_buffer *head) {
    t_buffer *current = head;
    size_t total_length = 0;

    // Calculate the total length of the strings in the list
    while (current != NULL) {
        total_length += ft_strlen(current->data);
        current = current->next;
    }

    // Allocate memory for the combined string
    char *result = (char *)malloc((total_length + 1) * sizeof(char));
    if (result == NULL) {
        // Memory allocation failed
        return NULL;
    }

    // Initialize the result string with a null character


    // Concatenate strings from the list
    current = head;
    while (current != NULL) {
        ft_strlcat(result, current->data, total_length + 1);
        current = current->next;
    }

    return result;
}


#include <stdio.h>
void print_list(t_buffer *list) {
    while (list != NULL) {
        printf("%s", list->data);
        list = list->next;
    }
}

int main(void) {
    int fd;
    t_buffer *list = NULL;

    // Open a file for testing
    fd = open("test_file.txt", O_RDONLY);
    if (fd == -1) {
        return 1;
    }

    // Call create_list to populate the linked list
    create_list(&list, fd);

    // Print the contents of the linked list
    printf("%s", get_line(list));
    printf("\n");
    print_list(list);

    // Close the file
    close(fd);

    return 0;
}
