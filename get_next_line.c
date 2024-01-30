/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrolova <lfrolova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:00:07 by lfrolova          #+#    #+#             */
/*   Updated: 2024/01/09 14:00:08 by lfrolova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"


void append_node(t_buffer **head, const char *str_buf) 
{
    t_buffer *last_node;
    t_buffer *new_node;

    new_node = malloc(sizeof(t_buffer));
    if (new_node == NULL)
        return;
    new_node->content = ft_strdup(str_buf);  
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

void create_list(t_buffer **list, int fd) 
{
    ssize_t bytesRead;
    int foundNewline = 0;
    char *buffer;

    buffer = malloc(BUFFER_SIZE + 1);
        if (!buffer)
            return ;
    while (!foundNewline && (bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) 
    {
        buffer[bytesRead] = '\0';

        // Find the position of the newline character
        char *newlinePos = ft_strchr(buffer, '\n');
        if (newlinePos != NULL) {
            /*newlinePos = '\n';*/
            foundNewline = 1;
        }
        append_node(list, buffer);
    }
    free(buffer);
    return ;
}

char	*get_line(t_buffer *list)
{
	int		str_len;
	char	*next_str;

	if (NULL == list)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (NULL == next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

void deallocate_list(t_buffer **list, t_buffer *last_node) {
    char *buf = malloc(BUFFER_SIZE + 1);
    t_buffer *clean_node = malloc(sizeof(t_buffer));

    if (NULL == buf || NULL == clean_node)
        return;

    int i = 0;
    int k = 0;

    while (last_node->content[i] && last_node->content[i] != '\n')
        ++i;

    while (last_node->content[i] && last_node->content[++i])
        buf[k++] = last_node->content[i];

    buf[k] = '\0';

    clean_node->content = buf;
    clean_node->next = NULL;

    t_buffer *tmp;

    while (*list) {
        tmp = (*list)->next;
        free((*list)->content);
        free(*list);
        *list = tmp;
    }

    *list = NULL;

    if (clean_node->content[0])
        *list = clean_node;
    else {
        free(buf);
        free(clean_node);
    }
}



char *get_next_line(int fd)
{
    static t_buffer *list = NULL;
    char *next_line;
    t_buffer *last_node;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
        return NULL;

    create_list(&list, fd);
    if (list == NULL)
        return NULL;
    last_node = find_last_node(list);
    next_line = get_line(list);

    // Update the list by deallocating nodes
    deallocate_list(&list, last_node);

    return next_line;
}