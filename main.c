/*
*************************************************************************************************************
*                                        DES-Algorithm-Implementation
*                                          Data Encryption Standard
*
*                                               DES  Test code
*
* File : main.C
* By   : Mostafa Abd El-Fatah, 2015
*************************************************************************************************************
*/
//#pragma SRC
#include <REG52.H>                /* special function register declarations   */
/* for the intended 8051 derivative         */
#include <stdio.h>                /* prototype declarations for I/O functions */
#include "datatypes.h"
#include "DES.h"
#include "UART.h"
#include "TERMINAL.h"

/*
**************************************************************************************************************
*                                               VARIABLES
**************************************************************************************************************
*/
code char welcome[] = "welcome\r";
code char input[] = "Input:";
code char result[] = "Result:";
code char error[] = "please enter SETKEY or ENCRYPT or DECRYPT\r";
code char error_check_vlues[] = "check values to be hex\r";

/*$PAGE*/
/*
*********************************************************************************************************
*                                       FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void desTest(void) reentrant;

/*
**************************************************************************************************************
*                                                MAIN
**************************************************************************************************************
*/
void main (void)
{
    uart_init();
    uart_string(welcome);
//	#pragma asm
//	nop;
//	#pragma endasm

    /*------------------------------------------------
     loop executed forever.
    ------------------------------------------------*/
    while (1)
    {
        desTest();
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                         Test encrypt and decrypt DES algorithm implementation
*
* Description: This function is used to Display Encrypted and Decrypted input data to the console.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/
void desTest(void) reentrant
{
    uint8_t *check_in, *ptr_hex;
    unsigned char out[8]; 
    unsigned char in[8];
    static unsigned char key[8];

    uart_string(input);
    check_in = uart_getstring();

    switch(operation(check_in))
    {
    case 1:
        //uart_string("SETKEY");
        ptr_hex = check_in+7;
        if(check_hex(ptr_hex)) 			/* if entered value in hex containue */
        {
            get_hex(key,ptr_hex);		/* get string input and convert it to hex */
            uart_string("Result: Key Changed Successfully\r");
        }
        else
        {
            uart_string(error_check_vlues);
        }
        break;

    case 2:
        //uart_string("ENCRYPT");
        ptr_hex = check_in+8;
        if(check_hex(ptr_hex)==1)
        {
            get_hex(in,ptr_hex);
            encrypt(out, in, key);      // encrypt "in" data by "key" and return encrypted data in "out"
            uart_string(result);
            uart_string(bin_to_string(out, 8));
        }
        else
        {
            uart_string(error_check_vlues);
        }
        break;

    case 3:
        //uart_string("DECRYPT");
        ptr_hex = check_in+8;
        if(check_hex(ptr_hex)==1)
        {
            get_hex(in,ptr_hex);
            decrypt(out, in, key);      // decrypt "in" data by "key" and return original data in "out"
            uart_string(result);
            uart_string(bin_to_string(out, 8));
        }
        else
        {
            uart_string(error_check_vlues);
        }
        break;

    default:
        uart_string(error);
    }
}

