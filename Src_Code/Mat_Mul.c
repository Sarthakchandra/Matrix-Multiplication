/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <time.h>
#include "xtime_l.h"
#define N 2

void multiply(int mat1[N][N], int mat2[N][N], int res[N][N]) // Function to perform the multiplication
{
	int i,j,k;
	for(i = 0; i < N ; i++){
		for(j = 0; j < N ; j++){
			res[i][j] = 0;// Need to initialize this by 0 as by default it can take any value
			for(k = 0; k < N ; k++){
				res[i][j] += mat1[i][k]*mat2[k][j];
			}
		}
	}
}
	int main()
	{
    init_platform();
    int M1[N][N],M2[N][N];
    int res[N][N]; // To store the result
    int i,j;
    XTime tprocessorStart, tprocessorEnd; //both variables have the data type Structure
    printf("BUILDING WITH THE O1 OPTIMIZATION\n");
    printf("Enter the elements of Matrix 1\n");
    printf("==========================================\n");
    for(i = 0; i < N ; i++)
    	for(j = 0; j < N ; j++){
    		printf("Enter the element M1[%d][%d]\n",i,j);
    		scanf("%d",&M1[i][j]);
    	}
    printf("Enter the elements of Matrix 2\n");
        printf("==========================================\n");
        for(i = 0; i < N ; i++)
        	for(j = 0; j < N ; j++){
        		printf("Enter the element M2[%d][%d]\n",i,j);
        		scanf("%d",&M2[i][j]);
        	}
    printf("The entered Matrix M1 is \n\r");
    for(i = 0; i < N ; i++){
        	for(j = 0; j < N ; j++)
        		printf(" %d",M1[i][j]);
        	printf("\n");
    }
    printf("The entered Matrix M2 is \n\r");
        for(i = 0; i < N ; i++){
            	for(j = 0; j < N ; j++)
            		printf(" %d",M2[i][j]);
            	printf("\n");
        }
    XTime_GetTime(&tprocessorStart);//Time Calculation starts here
    multiply(M1, M2, res);
    XTime_GetTime(&tprocessorEnd);//Time Calculation ends here
    printf("The multiplication of M1 and M2 is \n");
    for(i=0;i<N;i++){
    	for(j=0;j<N;j++)
    		printf(" %d", res[i][j]);
    	printf("\n");
    }
    printf("PS took %.2f us. to calculate the product \n", 1.0*(tprocessorEnd-tprocessorStart));
    cleanup_platform();
    return 0;
}
