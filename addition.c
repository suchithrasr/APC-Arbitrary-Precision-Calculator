#include "apc.h"

/*--------------------------------------------------------------------
 * Function : addition
 * Description : Performs addition of two large numbers stored in
 *               doubly linked lists.
 *               Result is stored in another linked list.
 *
 * Input :
 *      head1, tail1 -> First operand list
 *      head2, tail2 -> Second operand list
 *      headR, tailR -> Result list
 *
 * Return :
 *      SUCCESS
 *
 * Logic :
 *      - Addition starts from Least Significant Digit (LSB)
 *      - Traverse both lists from tail to head
 *      - Add digits along with carry
 *      - Store result digit at beginning of result list
 *------------------------------------------------------------------*/
int addition(Dlist **head1, Dlist **tail1,
             Dlist **head2, Dlist **tail2,
             Dlist **headR, Dlist **tailR)
{
    /* Point to last digits of both numbers */
    Dlist *t1 = *tail1;
    Dlist *t2 = *tail2;

    int carry = 0;
    int sum, digit;
    int d1, d2;

    /* Continue until:
       - both lists end
       - and carry becomes 0 */
    while (t1 != NULL || t2 != NULL || carry != 0)
    {
        /* Get digit from first number */
        if (t1 != NULL)
            d1 = t1->data;
        else
            d1 = 0;   // Handles unequal length numbers

        /* Get digit from second number */
        if (t2 != NULL)
            d2 = t2->data;
        else
            d2 = 0;   // Handles unequal length numbers

        /* Add digits and carry */
        sum = d1 + d2 + carry;

        /* Extract result digit */
        digit = sum % 10;

        /* Update carry */
        carry = sum / 10;

        /* Insert result digit at beginning */
        insert_at_first(headR, tailR, digit);

        /* Move to previous digit in first number */
        if (t1 != NULL)
            t1 = t1->prev;

        /* Move to previous digit in second number */
        if (t2 != NULL)
            t2 = t2->prev;
    }

    return SUCCESS;
}