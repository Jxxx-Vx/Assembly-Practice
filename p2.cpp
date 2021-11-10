//* CMPE102 - Project #2 template */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Example - sorter function */

void sorter (long* list, long count, long opcode)
{
/* Move the array pointer to rax, opcode to rbx, count to rcx */
/* The following sample code swap the array elements in reverse order */
/* You would need to replace it with the logic from the bubble sort algorithm 
1 = asc, 2 = des
*/

asm
(
	"movq %0, %%rax;" //Move array pointer to rax          
	"movq %1, %%rbx;" //Move asc/des to rbx, asc = 1, des = 2	
	"movq $0, %%rcx;" //Counter starting from 0 
	"movq %2, %%rsi;" //rsi = count
	"decq %%rsi;" //rsi = count - 1
	"movq $0, %%rdi;" //Moves 0 to rdi

"x:" //Outer loop of nested Loop
	"cmpq %%rsi, %%rcx;" // compare current count to count-1
	"jz done;" // Jumps to the end and will end loop

	"movq %%rcx, %%rdx;" // y = x 
	"y:" //Inner loop of nested Loop

		"movq (%%rax, %%rcx, 8), %%r10;" // moves outer loop value, x, into r10
		"movq (%%rax, %%rdx, 8), %%r11;" // moves inner loop value, y, into r11
		"cmpq $1, %%rbx;" //Compares whether is asc or des
		"jne des;"//will jump to des if zero flag is not set.
		"cmpq %%r10, %%r11;" // Compares y-x and sets condition flags
		"jge no_swap;" // if y >= x, we will not swap,
		"jmp swap;"
		"des:"
			"cmpq %%r11, %%r10;" // Compares x-y and sets condition flags
			"jge no_swap;" // if x >= y, we will not swap,
		
		"swap:"
			"xchgq %%r10, (%%rax, %%rdx, 8);" // Swapping y = x		
			"xchgq %%r11, (%%rax, %%rcx, 8);" // Swapping x = y

		"no_swap:"
			"incq %%rdx;" // increment rdx by 1
			"cmpq %2, %%rdx;" // compare rdx with count
			"jne y;" // if rdx < count, countinues loop, otherwise moves down
			
	"incq %%rcx;" //increment the counter by 1
	"jmp x;" //jumps back to x

"done:"
 	 : 
	 : "m" (list), "m" (opcode), "m" (count)
	 : 
	 ); 
	 
}

int main(int argc, char** argv)
{
	long numlist[1000], asc;
	FILE *fptr;

	long i = 0;
	
	if (argc != 3)
	{
		printf("Usage: %s filename asc_des\n", argv[0]);
		return 1;
	}

	asc = atol (argv[2]);
	asc = (asc == 1) ? 1 : 2;

	printf("\n");

	fptr = fopen((argv[1]), "rtc");
	if (fptr == NULL)
      printf( "File %s was not opened\n",argv[1] );
	else
   {
      /* Set pointer to beginning of file: */
      fseek( fptr, 0L, SEEK_SET );

      /* Read data from file: */
	  while ( fscanf(fptr, "%ld", &numlist[i]) != EOF )
	  {
          printf( "%ld ", numlist[i] );
		  i++;
	  }

      printf( "\n\nNumber of integer = %ld\n", i );
      printf( "Ascend_or_Descend = %ld\n\n", asc );
      fclose( fptr );
   }

   sorter( numlist, i, asc);

   for (int j = 0; j < i; j++)
          printf( "%ld ", numlist[j] );

   printf("\n");

   return 0;
}



	


