/*
*************************************************************************************************************
*                                        UART Communication

* File : UART.C
* By   : github.com
*************************************************************************************************************
*/
#include "TERMINAL.H"

/*
**************************************************************************************************************
*                                               VARIABLES
**************************************************************************************************************
*/

code uint8_t operation_chose[3][8] = {"SETKEY","ENCRYPT","DECRYPT"};

code uint8_t decimal2hex[] = {'0', '1', '2', '3', '4',
                             '5', '6', '7', '8', '9',
                             'A','B','C','D','E','F'
                            };

/*$PAGE*/
/*
*********************************************************************************************************
*                                              operation check
*
* Description: This function is used to check the input from terminal to chose the operation
*
* Arguments  : in	    is a pointer to the input data come from terminal.
*
* Returns    : =1		SETKEY chosen
*
*			   =2		ENCRYPT	chosen
*
*			   =3		DECRYPT	chosen
*
*			   =0      	wrong entered
*********************************************************************************************************
*/
uint8_t operation(uint8_t *in) reentrant
{
    if(str_comp(in, &operation_chose[0], 6))
        return 1;

    if(str_comp(in, &operation_chose[1], 6))
        return 2;

    if(str_comp(in, &operation_chose[1], 6))
        return 3;

    return 0;
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                              check hex data input
*
* Description: This function is used to check the hex input from terminal is already hex
*
* Arguments  : in	    is a pointer to the input data come from terminal.
*
* Returns    : =1		data is hex
*
*			   =0      	wrong data entered
*********************************************************************************************************
*/
uint8_t check_hex(uint8_t *in) reentrant
{
    uint8_t i, j,check=0;
    for(i = 0; i<16; i++)
    {
        for(j = 0; j<16; j++)
            if(in[i]==decimal2hex[j])
                check=1;
        if(check==0)
            return 0;
    }
    return 1;
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                              get hex from string input
*
* Description: This function is used to get hex from string input from terminal.
*
* Arguments  : out	  pointer to the block (64 bit = 8 byte) where the converted data is written to
*
*              in     pointer to the block (64 bit = 8 byte) where the terminal data come
*
* Returns    : None
*********************************************************************************************************
*/
void get_hex(uint8_t* out,uint8_t* in) reentrant
{
    uint8_t i, j,hex_value=0,next=0;
    for(i = 0; i<16; i++)
    {
        for(j = 0; j<16; j++)
        {
            if(in[i]==decimal2hex[j])
            {
                hex_value|=j;
                break;
            }
        }
        if(i%2)
        {
            out[next++] = hex_value;
            hex_value =0;
        }
        hex_value=hex_value<<4;
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                      binary to string
*
* Description: This function use to convert data from binary to string
*
* Arguments  : input    is a point to the array want to be converted.
*
*			   nbytes	is a char that represent the number of array.
*
* Returns    : output	is a point to the 1st element of string.
*********************************************************************************************************
*/
char* bin_to_string(const unsigned char input[], int nbytes)
{
    int i;
    static char output[64 + 3];
    char* output_ptr = output;
    *output_ptr++ = '0';
    *output_ptr++ = 'x';
    for (i=0; i<nbytes; i++)
    {
        *output_ptr++ = decimal2hex[(input[i]&0xF0)>>4];
        *output_ptr++ = decimal2hex[(input[i]&0x0F)];
    }
    *output_ptr++ = '\r';
    *output_ptr = '\0';
    return output;
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                              string compare
*
* Description: This function is used to compare between tow string in certin n bytes.
*
* Arguments  : str1	  	pointer to the 1st element of 1st string
*
*              str2   	pointer to the 2nd element of 2nd string
*
*              nbytes	number of bytes
*
* Returns  =1  of str1 match with str2
*
*		   =0  of str1 dosnt match with str2
*********************************************************************************************************
*/
uint8_t str_comp(uint8_t* str1,uint8_t* str2, uint8_t nbytes) reentrant
{
    uint8_t i=0;
    while(i < nbytes)
    {
        if(str1[i]!=str2[i])
			return 0;
		i++;
	}
	return 1;
}