#include "apc.h"

/*--------------------------------------------------------------------
 * Function : multiplication
 * Description : Performs multiplication of two large numbers stored
 *               in doubly linked lists.
 *
 * Parameters :
 *      head1, tail1 -> First operand list
 *      head2, tail2 -> Second operand list
 *      headR, tailR -> Result list
 *
 * Return :
 *      SUCCESS
 *
 * Logic :
 *      - Multiply each digit of operand2 with entire operand1
 *      - Store intermediate result in temporary list
 *      - Add zeros according to place value
 *      - Add all intermediate results
 *------------------------------------------------------------------*/
int multiplication(Dlist **head1, Dlist **tail1,
                   Dlist **head2, Dlist **tail2,
                   Dlist **headR, Dlist **tailR)
{
    /* Traversal pointers */
    Dlist *t1, *t2;

    /* Temporary result lists */
    Dlist *headR1 = NULL, *tailR1 = NULL;
    Dlist *headR2 = NULL, *tailR2 = NULL;

    int mul, carry, digit;

    /* Stores place value count */
    int count = 0;

    /*--------------------------------------------------------------
     * Start multiplication from Least Significant Digit (LSB)
     * of second operand
     *-------------------------------------------------------------*/
    t2 = *tail2;

    while (t2 != NULL)
    {
        /* Reset pointer for first operand */
        t1 = *tail1;

        /* Reset carry */
        carry = 0;

        /* Initialize temporary result list */
        headR2 = tailR2 = NULL;

        /*----------------------------------------------------------
         * Add zeros according to place value
         *
         * Example :
         *      123 × 45
         *            ^
         *           4 -> one zero added
         *---------------------------------------------------------*/
        for (int i = 0; i < count; i++)
        {
            insert_at_last(&headR2, &tailR2, 0);
        }

        /*----------------------------------------------------------
         * Multiply current digit of operand2
         * with all digits of operand1
         *---------------------------------------------------------*/
        while (t1 != NULL)
        {
            /* Multiply digits and add carry */
            mul = (t1->data * t2->data) + carry;

            /* Extract digit */
            digit = mul % 10;

            /* Update carry */
            carry = mul / 10;

            /* Insert digit at beginning */
            insert_at_first(&headR2, &tailR2, digit);

            /* Move to previous digit */
            t1 = t1->prev;
        }

        /*----------------------------------------------------------
         * Insert remaining carry if exists
         *---------------------------------------------------------*/
        if (carry > 0)
        {
            insert_at_first(&headR2, &tailR2, carry);
        }

        /*----------------------------------------------------------
         * First intermediate result
         *---------------------------------------------------------*/
        if (headR1 == NULL)
        {
            headR1 = headR2;
            tailR1 = tailR2;
        }

        /*----------------------------------------------------------
         * Add intermediate result with previous result
         *---------------------------------------------------------*/
        else
        {
            addition(&headR1, &tailR1,
                     &headR2, &tailR2,
                     headR, tailR);

            /* Free old intermediate lists */
            delete_list(&headR1, &tailR1);
            delete_list(&headR2, &tailR2);

            /* Update accumulated result */
            headR1 = *headR;
            tailR1 = *tailR;

            /* Reset result pointers */
            *headR = NULL;
            *tailR = NULL;
        }

        /*----------------------------------------------------------
         * Move to next digit in operand2
         *---------------------------------------------------------*/
        t2 = t2->prev;

        /* Increment place value count */
        count++;
    }

    /*--------------------------------------------------------------
     * Store final multiplication result
     *-------------------------------------------------------------*/
    *headR = headR1;
    *tailR = tailR1;

    return SUCCESS;
}