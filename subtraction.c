#include "apc.h"

/*--------------------------------------------------------------------
 * Function : subtraction
 * Description : Performs subtraction of two large numbers stored in
 *               doubly linked lists.
 *
 * Parameters :
 *      head1, tail1 -> First operand list (larger number)
 *      head2, tail2 -> Second operand list (smaller number)
 *      headR, tailR -> Result list
 *
 * Return :
 *      SUCCESS
 *
 * Logic :
 *      - Subtraction starts from Least Significant Digit (LSB)
 *      - Traverse both lists from tail to head
 *      - Handle borrow when required
 *      - Store result digit at beginning of result list
 *
 * Note :
 *      head1 should contain number greater than or equal to head2
 *------------------------------------------------------------------*/
int subtraction(Dlist **head1, Dlist **tail1,
                Dlist **head2, Dlist **tail2,
                Dlist **headR, Dlist **tailR)
{
    /* Pointers for traversal from last digit */
    Dlist *t1 = *tail1;
    Dlist *t2 = *tail2;

    /* Stores borrow value */
    int borrow = 0;

    /* Stores difference */
    int diff;

    /* Stores digits from operands */
    int d1, d2;

    /*--------------------------------------------------------------
     * Continue until first operand digits are completed
     *-------------------------------------------------------------*/
    while (t1 != NULL)
    {
        /* Get digit from first operand */
        d1 = t1->data;

        /* Get digit from second operand */
        if (t2 != NULL)
            d2 = t2->data;
        else
            d2 = 0;

        /*----------------------------------------------------------
         * Apply previous borrow
         *---------------------------------------------------------*/
        d1 = d1 - borrow;

        /*----------------------------------------------------------
         * Borrow condition
         *
         * Example :
         *      2 - 5
         *
         * Borrow from previous digit:
         *      12 - 5 = 7
         *---------------------------------------------------------*/
        if (d1 < d2)
        {
            d1 = d1 + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        /* Calculate difference */
        diff = d1 - d2;

        /* Insert result digit at beginning */
        insert_at_first(headR, tailR, diff);

        /* Move to previous digit in operand1 */
        t1 = t1->prev;

        /* Move to previous digit in operand2 */
        if (t2 != NULL)
            t2 = t2->prev;
    }

    return SUCCESS;
}