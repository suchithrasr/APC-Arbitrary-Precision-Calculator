#include "apc.h"
#include <stdio.h>

/*--------------------------------------------------------------------
 * Function : division
 * Description : Performs division of two large numbers stored in
 *               doubly linked lists.
 *
 * Parameters :
 *      head1, tail1 -> Dividend list
 *      head2, tail2 -> Divisor list
 *      headR, tailR -> Result list (Quotient)
 *
 * Return :
 *      SUCCESS -> Division successful
 *      FAILURE -> Division by zero
 *
 * Logic :
 *      - Repeatedly subtract divisor from dividend
 *      - Count number of successful subtractions
 *      - Store count as quotient
 *------------------------------------------------------------------*/
int division(Dlist **head1, Dlist **tail1,
             Dlist **head2, Dlist **tail2,
             Dlist **headR, Dlist **tailR)
{
    /* Temporary list to store subtraction result */
    Dlist *tempH = NULL, *tempT = NULL;

    /* Stores quotient count */
    int count;

    /*--------------------------------------------------------------
     * Division by zero check
     * Example : 100 / 0 -> invalid
     *-------------------------------------------------------------*/
    if (*head2 == NULL ||
       ((*head2)->data == 0 && (*head2)->next == NULL))
    {
        return FAILURE;
    }

    /*--------------------------------------------------------------
     * If dividend < divisor
     * Quotient becomes 0
     * Example : 5 / 10 = 0
     *-------------------------------------------------------------*/
    if (compare_list(head1, head2) < 0)
    {
        insert_at_last(headR, tailR, 0);
        return SUCCESS;
    }

    /*--------------------------------------------------------------
     * Main division loop
     * Continue until dividend becomes smaller than divisor
     *-------------------------------------------------------------*/
    while (compare_list(head1, head2) >= 0)
    {
        /* Reset count for each iteration */
        count = 0;

        /* Initialize temporary list */
        tempH = tempT = NULL;

        /*----------------------------------------------------------
         * Repeated subtraction
         * dividend = dividend - divisor
         *---------------------------------------------------------*/
        while (compare_list(head1, head2) >= 0)
        {
            /* Perform subtraction */
            subtraction(head1, tail1,
                        head2, tail2,
                        &tempH, &tempT);

            /* Delete old dividend list */
            delete_list(head1, tail1);

            /* Update dividend with subtraction result */
            *head1 = tempH;
            *tail1 = tempT;

            /* Remove unnecessary leading zeros */
            remove_leading_zeros(head1, tail1);

            /* Increment quotient count */
            count++;

            /* Reset temporary pointers */
            tempH = tempT = NULL;
        }

        /*----------------------------------------------------------
         * Convert count into digits
         * Example :
         *      count = 12
         *      store as 1 -> 2
         *---------------------------------------------------------*/
        char buffer[50];

        /* Convert integer to string */
        sprintf(buffer, "%d", count);

        /* Insert each digit into quotient list */
        for (int i = 0; buffer[i] != '\0'; i++)
        {
            insert_at_last(headR, tailR,
                           buffer[i] - '0');
        }
    }

    /*--------------------------------------------------------------
     * Safety check:
     * If quotient list still empty, insert 0
     *-------------------------------------------------------------*/
    if (*headR == NULL)
        insert_at_last(headR, tailR, 0);

    return SUCCESS;
}