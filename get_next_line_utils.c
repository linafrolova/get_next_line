#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dest;

	i = 0;
	while (s[i] != '\0')
		i++;
	dest = (char *)malloc((i + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int found_newline(t_buffer *list) 
{
	char *ptr;
    if (list == NULL)
        return (0);
    while (list) 
	{
        ptr = list->content;
        while (*ptr != '\0') 
		{
            if (*ptr == '\n')
                return (1);
            ptr++;
        }
        list = list->next;
    }
    return (0);
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
		while (list -> content[i])
		{
			if (list -> content[i] == '\n')
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
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->content[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
}

void append_node(t_buffer **head, const char *str_buf) 
{
    t_buffer *last_node;
    t_buffer *new_node;

    if (head == NULL)
        return ;
    new_node = malloc(sizeof(t_buffer));
    if (new_node == NULL)
        return ;
    new_node->content = ft_strdup(str_buf);  
    new_node->next = NULL;
    if (*head == NULL)
        *head = new_node;
    else 
	{
        last_node = *head;
        while (last_node->next != NULL)
            last_node = last_node->next;
        last_node->next = new_node;
    }
}