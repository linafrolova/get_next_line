#include "get_next_line.h"

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

