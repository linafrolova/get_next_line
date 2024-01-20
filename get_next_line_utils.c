#include "get_next_line.h"

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

void append_node(t_buffer **head, const char *str_buf) {
    t_buffer *last_node;
    t_buffer *new_node;

    new_node = malloc(sizeof(t_buffer));
    if (new_node == NULL)
        return;
    
    // Duplicate the string before storing it in the node
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


char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;

	i = 0;
	cc = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			return ((char *) s + i);
		i++;
	}
	if (cc == '\0')
		return ((char *) s + i);
	return (NULL);
}
char	*find_last_node(t_buffer *list)
{
	if (NULL == list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list -> data);
}
// int	found_newline(t_buffer *list)
// {
// 	int	i;

// 	if (NULL == list)
// 		return (0);
// 	while (list)
// 	{
// 		i = 0;
// 		while (list->data[i] && i < BUFFER_SIZE)
// 		{
// 			if (list->data[i] == '\n')
// 				return (1);
// 			++i;
// 		}
// 		list = list->next;
// 	}
// 	return (0);
// }

// void	create_list(t_buffer **list, int fd)
// {
// 	int		char_read;	
// 	char	*buf;

// 	while (!found_newline(*list))
// 	{
// 		buf = malloc(BUFFER_SIZE + 1);
// 		if (NULL == buf)
// 			return ;
// 		char_read = read(fd, buf, BUFFER_SIZE);
// 		if (!char_read)
// 		{
// 			free(buf);
// 			return ;
// 		}
// 		buf[char_read] = '\0';
// 		append_node(list, buf);
// 	}
// }
void create_list(t_buffer **list, int fd) 
{
    ssize_t bytesRead;
    int foundNewline = 0;
    char *buffer;

    buffer = malloc(BUFFER_SIZE + 1);
        if (!buffer) {
            return ;
        }

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


size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

int	len_to_newline(t_buffer *list)
{
	int	i;
	int	len;

	if (NULL == list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->data[i])
		{
			if (list->data[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}	
	return (len);
}


void	copy_str(t_buffer *list, char *str)
{
	int	i;
	int	k;

	if (NULL == list)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->data[i])
		{
			if (list->data[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->data[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
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


t_buffer *deallocate_list(t_buffer **list, char *last_node)
{
    t_buffer *new_list;
    char *rest;

    rest = ft_strchr(last_node, '\n');
    if (rest == NULL)
    {
        // Handle case where newline is not found
        return NULL;
    }

    new_list = malloc(sizeof(t_buffer));
    if (new_list == NULL)
    {
        // Handle memory allocation failure
        return NULL;
    }

    new_list->data = ft_strdup(rest + 1); // Move past the newline
    new_list->next = NULL;

    // Clean the previous list and free the memory
    while (*list != NULL)
    {
        t_buffer *temp = *list;
        *list = (*list)->next;
        free(temp->data);
        free(temp);
    }

    return new_list;
}


char *get_next_line(int fd)
{
    static t_buffer *list = NULL;
    char *next_line;
    char *last_node;


    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
        return NULL;

    create_list(&list, fd);
    if (list == NULL)
        return NULL;
    last_node = find_last_node(list);
    next_line = get_line(list);

    // Update the list by deallocating nodes
    list = deallocate_list(&list, last_node);

    return next_line;
}

#include <stdio.h>

int main(void) {
    int fd;
    char *line;

    // Open a file for testing
    fd = open("test_file.txt", O_RDONLY);
    if (fd == -1) {
        return 1;
    }

    // Read and print lines using get_next_line
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s\n", line);
        free(line);  // Free the allocated memory for each line
    }

    // Close the file
    close(fd);

    return 0;
}


// void print_list(t_buffer* list) {
//     while (list) {
//         printf("%s", list->data);
//         list = list->next;
//     }
// }

// int main() {
//     t_buffer* list = NULL;
//     int fd;  // Replace 'fd' with the file descriptor you want to read from

//     fd = open("test_file.txt", O_RDONLY);
//     if (fd == -1) {
//         return 1;
//     }

//     create_list(&list, fd);

//     print_list(list);

//     while (list) {
//         t_buffer* temp = list;
//         list = list->next;
//         free(temp);
//     }

//     return 0;
// }
