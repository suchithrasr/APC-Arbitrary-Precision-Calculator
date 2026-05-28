#ifndef APC_H
#define APC_H

#include <stddef.h>
#include <stdlib.h>

/*--------------------------------------------------------------------
 * Macro Definitions
 *------------------------------------------------------------------*/

/* Operation successful */
#define SUCCESS 0

/* Operation failed */
#define FAILURE -1

/*--------------------------------------------------------------------
 * Structure Definition
 * Description : Node structure for Doubly Linked List
 *------------------------------------------------------------------*/
typedef struct node
{
    /* Pointer to previous node */
    struct node *prev;

    /* Stores single digit */
    int data;

    /* Pointer to next node */
    struct node *next;

} Dlist;

/*--------------------------------------------------------------------
 * Function Prototypes
 *------------------------------------------------------------------*/

/*--------------------------------------------------------------------
 * Function : digit_to_list
 * Description : Converts operand strings into doubly linked lists.
 *------------------------------------------------------------------*/
void digit_to_list(Dlist **head1, Dlist **tail1,
                   Dlist **head2, Dlist **tail2,
                   char *argv[]);

/*--------------------------------------------------------------------
 * Function : addition
 * Description : Adds two large numbers stored in linked lists.
 *------------------------------------------------------------------*/
int addition(Dlist **head1, Dlist **tail1,
             Dlist **head2, Dlist **tail2,
             Dlist **headR, Dlist **tailR);

/*--------------------------------------------------------------------
 * Function : subtraction
 * Description : Subtracts two large numbers stored in linked lists.
 *------------------------------------------------------------------*/
int subtraction(Dlist **head1, Dlist **tail1,
                Dlist **head2, Dlist **tail2,
                Dlist **headR, Dlist **tailR);

/*--------------------------------------------------------------------
 * Function : multiplication
 * Description : Multiplies two large numbers stored in linked lists.
 *------------------------------------------------------------------*/
int multiplication(Dlist **head1, Dlist **tail1,
                   Dlist **head2, Dlist **tail2,
                   Dlist **headR, Dlist **tailR);

/*--------------------------------------------------------------------
 * Function : division
 * Description : Divides two large numbers stored in linked lists.
 *------------------------------------------------------------------*/
int division(Dlist **head1, Dlist **tail1,
             Dlist **head2, Dlist **tail2,
             Dlist **headR, Dlist **tailR);

/*--------------------------------------------------------------------
 * Function : print_result
 * Description : Prints the result stored in linked list.
 *------------------------------------------------------------------*/
void print_result(Dlist *head);

/*--------------------------------------------------------------------
 * Function : insert_at_first
 * Description : Inserts node at beginning of linked list.
 *------------------------------------------------------------------*/
int insert_at_first(Dlist **head, Dlist **tail, int data);

/*--------------------------------------------------------------------
 * Function : insert_at_last
 * Description : Inserts node at end of linked list.
 *------------------------------------------------------------------*/
int insert_at_last(Dlist **head, Dlist **tail, int data);

/*--------------------------------------------------------------------
 * Function : compare_list
 * Description : Compares two linked list numbers.
 * Return :
 *      1  -> first number greater
 *     -1  -> second number greater
 *      0  -> both equal
 *------------------------------------------------------------------*/
int compare_list(Dlist **head1, Dlist **head2);

/*--------------------------------------------------------------------
 * Function : delete_list
 * Description : Deletes entire linked list and frees memory.
 *------------------------------------------------------------------*/
void delete_list(Dlist **head, Dlist **tail);

/*--------------------------------------------------------------------
 * Function : remove_leading_zeros
 * Description : Removes unnecessary leading zeros from result.
 *------------------------------------------------------------------*/
void remove_leading_zeros(Dlist **head, Dlist **tail);

#endif