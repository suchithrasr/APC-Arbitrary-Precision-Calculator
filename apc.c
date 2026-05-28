#include "apc.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/*--------------------------------------------------------------------
 * Function : insert_at_last
 * Description : Inserts a new digit/node at the end of the doubly
 *               linked list.
 * Input : head  -> address of head pointer
 *         tail  -> address of tail pointer
 *         data  -> digit to be inserted
 * Output : SUCCESS / FAILURE
 *------------------------------------------------------------------*/
int insert_at_last(Dlist **head, Dlist **tail, int data)
{
    /* Allocate memory for new node */
    Dlist *newnode = (Dlist *)malloc(sizeof(Dlist));

    /* Check memory allocation */
    if (newnode == NULL)
        return FAILURE;

    /* Initialize node */
    newnode->data = data;
    newnode->prev = NULL;
    newnode->next = NULL;

    /* If list is empty */
    if (*head == NULL)
    {
        *head = *tail = newnode;
    }
    else
    {
        /* Link old tail to new node */
        (*tail)->next = newnode;

        /* Link new node back to old tail */
        newnode->prev = *tail;

        /* Update tail */
        *tail = newnode;
    }

    return SUCCESS;
}

/*--------------------------------------------------------------------
 * Function : insert_at_first
 * Description : Inserts a new digit/node at the beginning of the list.
 * Input : head  -> address of head pointer
 *         tail  -> address of tail pointer
 *         data  -> digit to be inserted
 * Output : SUCCESS / FAILURE
 *------------------------------------------------------------------*/
int insert_at_first(Dlist **head, Dlist **tail, int data)
{
    /* Create new node */
    Dlist *new = (Dlist *)malloc(sizeof(Dlist));

    /* Check memory allocation */
    if (new == NULL)
        return FAILURE;

    /* Initialize node */
    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    /* If list is empty */
    if (*head == NULL)
    {
        *head = *tail = new;
        return SUCCESS;
    }

    /* Link new node to old head */
    new->next = *head;

    /* Link old head back to new node */
    (*head)->prev = new;

    /* Update head */
    *head = new;

    return SUCCESS;
}

/*--------------------------------------------------------------------
 * Function : digit_to_list
 * Description : Converts operand strings into doubly linked lists.
 *               Each digit is stored in one node.
 * Input : argv[] -> command line arguments
 * Output : Creates linked lists for both operands
 *------------------------------------------------------------------*/
void digit_to_list(Dlist **head1, Dlist **tail1,
                   Dlist **head2, Dlist **tail2,
                   char *argv[])
{
    char *op1 = argv[1];
    char *op2 = argv[3];

    int i;

    /* ---------------- Operand 1 ---------------- */

    /* Skip negative sign if present */
    i = (op1[0] == '-') ? 1 : 0;

    /* Skip leading zeros */
    while (op1[i] == '0')
        i++;

    /* If operand contains only zeros */
    if (op1[i] == '\0')
    {
        insert_at_last(head1, tail1, 0);
    }
    else
    {
        /* Convert each digit into node */
        for (; op1[i] != '\0'; i++)
        {
            /* Validate digit */
            if (!isdigit(op1[i]))
            {
                printf("Invalid character in operand1\n");
                return;
            }

            /* Insert digit into list */
            insert_at_last(head1, tail1, op1[i] - '0');
        }
    }

    /* ---------------- Operand 2 ---------------- */

    /* Skip negative sign if present */
    i = (op2[0] == '-') ? 1 : 0;

    /* Skip leading zeros */
    while (op2[i] == '0')
        i++;

    /* If operand contains only zeros */
    if (op2[i] == '\0')
    {
        insert_at_last(head2, tail2, 0);
    }
    else
    {
        /* Convert each digit into node */
        for (; op2[i] != '\0'; i++)
        {
            /* Validate digit */
            if (!isdigit(op2[i]))
            {
                printf("Invalid character in operand2\n");
                return;
            }

            /* Insert digit into list */
            insert_at_last(head2, tail2, op2[i] - '0');
        }
    }
}

/*--------------------------------------------------------------------
 * Function : print_result
 * Description : Prints the digits stored in the linked list.
 *               Leading zeros are skipped.
 * Input : head -> head pointer of result list
 *------------------------------------------------------------------*/
void print_result(Dlist *head)
{
    /* Check if list is empty */
    if (head == NULL)
    {
        printf("List is empty (0)\n");
        return;
    }

    /* Skip leading zeros */
    while (head->data == 0 && head->next != NULL)
        head = head->next;

    /* Print digits */
    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");
}

/*--------------------------------------------------------------------
 * Function : compare_list
 * Description : Compares two linked list numbers.
 * Return :
 *      1  -> list1 > list2
 *     -1  -> list1 < list2
 *      0  -> both equal
 *------------------------------------------------------------------*/
int compare_list(Dlist **head1, Dlist **head2)
{
    int count1 = 0, count2 = 0;

    Dlist *t1 = *head1;
    Dlist *t2 = *head2;

    /* Count digits in first list */
    while (t1)
    {
        count1++;
        t1 = t1->next;
    }

    /* Count digits in second list */
    while (t2)
    {
        count2++;
        t2 = t2->next;
    }

    /* Compare based on length */
    if (count1 > count2)
        return 1;

    if (count1 < count2)
        return -1;

    /* Length same -> compare digit by digit */
    t1 = *head1;
    t2 = *head2;

    while (t1 && t2)
    {
        if (t1->data > t2->data)
            return 1;

        else if (t1->data < t2->data)
            return -1;

        t1 = t1->next;
        t2 = t2->next;
    }

    /* Both numbers are equal */
    return 0;
}

/*--------------------------------------------------------------------
 * Function : delete_list
 * Description : Deletes all nodes from the linked list and frees memory.
 * Input : head -> address of head pointer
 *         tail -> address of tail pointer
 *------------------------------------------------------------------*/
void delete_list(Dlist **head, Dlist **tail)
{
    Dlist *temp;

    /* Delete node one by one */
    while (*head != NULL)
    {
        temp = *head;

        /* Move head to next node */
        *head = (*head)->next;

        /* Free current node */
        free(temp);
    }

    /* Update tail */
    *tail = NULL;
}

/*--------------------------------------------------------------------
 * Function : remove_leading_zeros
 * Description : Removes unnecessary leading zero nodes from result list.
 * Input : head -> address of head pointer
 *         tail -> address of tail pointer
 *------------------------------------------------------------------*/
void remove_leading_zeros(Dlist **head, Dlist **tail)
{
    /* Remove leading zeros except last node */
    while (*head && (*head)->data == 0 && (*head)->next)
    {
        Dlist *temp = *head;

        /* Move head forward */
        *head = (*head)->next;

        /* Remove backward link */
        (*head)->prev = NULL;

        /* Free old node */
        free(temp);
    }

    /* If list becomes empty */
    if (*head == NULL)
        *tail = NULL;
}