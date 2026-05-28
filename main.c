#include "apc.h"
#include <stdio.h>

/*--------------------------------------------------------------------
 * Function Prototype
 * Description : Validates command line arguments.
 *------------------------------------------------------------------*/
int validate_cli_arguments(int argc, char *argv[], char *operator);

/*--------------------------------------------------------------------
 * Function : main
 * Description : Driver function for Arbitrary Precision Calculator.
 *               Handles:
 *                  - Addition
 *                  - Subtraction
 *                  - Multiplication
 *                  - Division
 *
 * Input :
 *      Command line arguments
 *
 * Example :
 *      ./a.out 12345 + 6789
 *------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    /* Operand 1 list */
    Dlist *head1 = NULL, *tail1 = NULL;

    /* Operand 2 list */
    Dlist *head2 = NULL, *tail2 = NULL;

    /* Result list */
    Dlist *headR = NULL, *tailR = NULL;

    /* Stores operator */
    char operator;

    /* Stores signs of operands */
    char sign1 = '+', sign2 = '+';

    /* Stores result sign */
    char result_sign = '+';

    /*--------------------------------------------------------------
     * Validate command line arguments
     *-------------------------------------------------------------*/
    if (validate_cli_arguments(argc, argv, &operator) == FAILURE)
        return FAILURE;

    /*--------------------------------------------------------------
     * Detect sign of operand1
     *-------------------------------------------------------------*/
    if (argv[1][0] == '-')
        sign1 = '-';

    /*--------------------------------------------------------------
     * Detect sign of operand2
     *-------------------------------------------------------------*/
    if (argv[3][0] == '-')
        sign2 = '-';

    /*--------------------------------------------------------------
     * Convert operands into doubly linked lists
     *-------------------------------------------------------------*/
    digit_to_list(&head1, &tail1,
                  &head2, &tail2,
                  argv);

    /*--------------------------------------------------------------
     * Perform operation based on operator
     *-------------------------------------------------------------*/
    switch (operator)
    {

        /*==========================================================
         * ADDITION
         *=========================================================*/
        case '+':
        {
            /*------------------------------------------------------
             * Case 1 :
             * Same sign
             * Example :
             *      +5 + +3
             *      -5 + -3
             *-----------------------------------------------------*/
            if (sign1 == sign2)
            {
                addition(&head1, &tail1,
                         &head2, &tail2,
                         &headR, &tailR);

                result_sign = sign1;
            }

            /*------------------------------------------------------
             * Case 2 :
             * Different signs
             * Example :
             *      10 + (-5)
             *      (-10) + 5
             *-----------------------------------------------------*/
            else
            {
                int cmp = compare_list(&head1, &head2);

                /* operand1 > operand2 */
                if (cmp > 0)
                {
                    subtraction(&head1, &tail1,
                                &head2, &tail2,
                                &headR, &tailR);

                    result_sign = sign1;
                }

                /* operand2 > operand1 */
                else if (cmp < 0)
                {
                    subtraction(&head2, &tail2,
                                &head1, &tail1,
                                &headR, &tailR);

                    result_sign = sign2;
                }

                /* Both operands equal */
                else
                {
                    insert_at_last(&headR, &tailR, 0);
                }
            }

            /*------------------------------------------------------
             * Print negative sign only if result is not zero
             *-----------------------------------------------------*/
            if (result_sign == '-' &&
               !(headR->data == 0 && headR->next == NULL))
            {
                printf("-");
            }

            /* Print final result */
            print_result(headR);

            break;
        }

        /*==========================================================
         * SUBTRACTION
         *=========================================================*/
        case '-':
        {
            /*------------------------------------------------------
             * Convert :
             *      A - B  ->  A + (-B)
             *-----------------------------------------------------*/

            if (sign2 == '+')
                sign2 = '-';
            else
                sign2 = '+';

            /* Same sign after conversion */
            if (sign1 == sign2)
            {
                addition(&head1, &tail1,
                         &head2, &tail2,
                         &headR, &tailR);

                result_sign = sign1;
            }

            /* Different signs after conversion */
            else
            {
                int cmp = compare_list(&head1, &head2);

                /* operand1 > operand2 */
                if (cmp > 0)
                {
                    subtraction(&head1, &tail1,
                                &head2, &tail2,
                                &headR, &tailR);

                    result_sign = sign1;
                }

                /* operand2 > operand1 */
                else if (cmp < 0)
                {
                    subtraction(&head2, &tail2,
                                &head1, &tail1,
                                &headR, &tailR);

                    result_sign = sign2;
                }

                /* Both operands equal */
                else
                {
                    insert_at_last(&headR, &tailR, 0);
                }
            }

            /*------------------------------------------------------
             * Print negative sign only if result is not zero
             *-----------------------------------------------------*/
            if (result_sign == '-' &&
               !(headR->data == 0 && headR->next == NULL))
            {
                printf("-");
            }

            /* Print final result */
            print_result(headR);

            break;
        }

        /*==========================================================
         * MULTIPLICATION
         *=========================================================*/
        case '*':
        case 'x':
        {
            /* Perform multiplication */
            multiplication(&head1, &tail1,
                           &head2, &tail2,
                           &headR, &tailR);

            /* Result negative if signs differ */
            if (sign1 != sign2)
                result_sign = '-';

            /* Print negative sign if result not zero */
            if (result_sign == '-' &&
               !(headR->data == 0 && headR->next == NULL))
            {
                printf("-");
            }

            /* Print final result */
            print_result(headR);

            break;
        }

        /*==========================================================
         * DIVISION
         *=========================================================*/
        case '/':
        {
            /* Perform division */
            if (division(&head1, &tail1,
                         &head2, &tail2,
                         &headR, &tailR) == FAILURE)
            {
                printf("Division failed (division by zero)\n");

                /* Free allocated memory */
                delete_list(&head1, &tail1);
                delete_list(&head2, &tail2);
                delete_list(&headR, &tailR);

                return FAILURE;
            }

            /* Result negative if signs differ */
            if (sign1 != sign2)
                result_sign = '-';

            /* Print negative sign if result not zero */
            if (result_sign == '-' &&
               !(headR->data == 0 && headR->next == NULL))
            {
                printf("-");
            }

            /* Print final result */
            print_result(headR);

            break;
        }

        /*==========================================================
         * INVALID OPERATOR
         *=========================================================*/
        default:
            printf("Invalid operator!\n");
    }

    /*--------------------------------------------------------------
     * Free all allocated memory
     *-------------------------------------------------------------*/
    delete_list(&head1, &tail1);
    delete_list(&head2, &tail2);
    delete_list(&headR, &tailR);

    return SUCCESS;
}

/*--------------------------------------------------------------------
 * Function : validate_cli_arguments
 * Description : Validates command line arguments.
 *
 * Conditions :
 *      - Total arguments must be 4
 *      - Operator must be valid
 *
 * Return :
 *      SUCCESS / FAILURE
 *------------------------------------------------------------------*/
int validate_cli_arguments(int argc,
                           char *argv[],
                           char *operator)
{
    /* Check argument count */
    if (argc != 4)
    {
        printf("Usage: %s <operand1> <operator> <operand2>\n",
               argv[0]);

        return FAILURE;
    }

    /* Extract operator */
    *operator = argv[2][0];

    /* Validate operator */
    if (*operator != '+' &&
        *operator != '-' &&
        *operator != '*' &&
        *operator != 'x' &&
        *operator != '/')
    {
        printf("Invalid operator!\n");
        return FAILURE;
    }

    return SUCCESS;
}