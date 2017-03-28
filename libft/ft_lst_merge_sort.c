#include "libft.h"

t_list	*SortedMerge(t_list *a, t_list *b)
{
	t_list	*result;

	result = NULL;

	if (a == NULL)
		return(b);
	else if (b==NULL)
		return(a);

	/* Pick either a or b, and recur */
	if (a->data <= b->data)
	{
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = SortedMerge(a, b->next);
	}
	return(result);
}

void	split(t_list *source, t_list **front_ptr, t_list **back_ptr)
{
	t_list *fast;
	t_list *slow;

	if (source==NULL || source->next==NULL)
	{
		*front_ptr = source;
		*back_ptr = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}

		*front_ptr = source;
		*back_ptr = slow->next;
		slow->next = NULL;
	}
}
void	ft_lst_merge_sort(t_list **head_ptr, int (*cmp)())
{
	t_list	*head;
	t_list	*a;
	t_list	*b;

	head = *head_ptr;
	if ((head == NULL) || (head->next == NULL))
		return;

	split(head, &a, &b);

	/* Recursively sort the sublists */
	ft_lst_merge_sort(&a, cmp);
	ft_lst_merge_sort(&b, cmp);

	/* answer = merge the two sorted lists together */
	*head_ptr = SortedMerge(a, b);
}
