/*
Given an SLL which has a modified version of node called oddevennode .
Each oddevennode will have a next pointer and a random pointer ,The next will point to the next oddevennode
in the SLL and random will point to NULL initially.

You need to modify the SLL random pointers in such a way that ,All odd numbers in the list
are connected by random pointers in the same order in which they are in SLL and the same for even numbers.

Ex : SLL is : 1-2-3-4-5-6
Here 1->next will point to 2 ,2->next to 3 and so on till 6->next is NULL .All 1-6 nodes have random set to
NULL initially .Now you need to modify random pointers in such a way that First Odd number in List random will
point to second odd number in the list and so on .

so 1->random should point to 3 .3->random should point to 5 .5->random to NULL (As 5 is the last Oddnumber)
and 2->random should point to 4 ,4->random should point to 6 .6->random to NULL .(As 6 is last even number)

Return an Array consisting of two numbers [Oddcount,Evencount] or NULL for invalid Inputs

Ex 2 : 50->4->3->7->10->99->17
O.P : SLL randoms should be modified as .
50->4->10 . [Even numbers if transversed through Randoms from 50]
3->7->99->17. [Odd numbers if transversed through Randoms from 3]
The function SHOULD RETURN [4,3]  . Oddnumbers and Even numbers count array .

Note : The Order of Randoms Pointers should be in the same order they are in the original SLL .so if 33 has
arrived before 5 in the SLL .33->random should be 5 but not in reverse .And it should also be continous ,Like
if  there is only 1 odd node 71 any where between 33 and 5 ,33->random should point to 71 and 71->random should
point to 5.
The type if node is oddevennode ,and not Node .
*/
#include <stdlib.h>
#include <stdio.h>

struct oddevennode{
	int data;
	struct oddevennode * next;
	struct oddevennode * random;

};

struct oddevennode* send_head_to_even(struct oddevennode*, int*);
struct oddevennode* send_head_to_odd(struct oddevennode*, int*);

int * oddeven_sll(struct oddevennode *head){
	if (head==NULL)
	return NULL;
	else
	{
		oddevennode* odd_starting, *even_starting;
		int* count_arr;
		count_arr = (int*)malloc(sizeof(int) * 2);
		count_arr[0] = 0;
		count_arr[1] = 0;
		if ((head->data) % 2 == 0)
		{
			odd_starting = send_head_to_even(head, count_arr);
			if (odd_starting != NULL)
			even_starting = send_head_to_odd(odd_starting, count_arr);
		}
		else
		{
			even_starting = send_head_to_odd(head, count_arr);
			if (even_starting!=NULL)
			odd_starting = send_head_to_even(even_starting, count_arr);
		}
		return count_arr;
	}
}
struct oddevennode* send_head_to_even(struct oddevennode* head, int* count_arr)
{
	int flag = 0, even_count = 0;
	struct oddevennode* present, *prev,*odd_starting=NULL;
	if ((head->data) % 2 == 0)
		even_count++;
	present = head->next;
	prev = head;
	while (present)
	{
		if ((present->data) % 2 == 0)
		{
			prev->random = present;
			prev = present;
			even_count++;
		}
		else if (flag == 0 && ((present->data) % 2 != 0))
		{
			odd_starting = present;
			flag = 1;
		}
		present = present->next;
	}
	prev->random = NULL;
	count_arr[1] = even_count;
	return odd_starting;
}

struct oddevennode* send_head_to_odd(struct oddevennode* odd_starting, int* count_arr)
{
	struct oddevennode* present, *prev,*even_starting=NULL;
	int flag = 0, odd_count = 0;
	if ((odd_starting->data) % 2 != 0)
		odd_count++;
	present = odd_starting->next;
	prev = odd_starting;
	while (present)
	{
		if ((present->data) % 2 != 0)
		{
			prev->random = present;
			prev = present;
			odd_count++;
		}
		else if (flag == 0 && ((present->data) % 2 == 0))
		{
			even_starting = present;
			flag = 1;
		}
		present = present->next;
	}
	prev->random = NULL;
	count_arr[0] = odd_count;
	return even_starting;
}