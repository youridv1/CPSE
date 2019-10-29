.cpu cortex-m0
.align 2
.bss
buffer: .skip 40
.text
.global decompress

decompress:
	push {r4, lr} 					//push r4 and lr on the stack
	mov r4, r0    					//move the compressed string to r4

mainLoop:
	ldrb r0, [r4]  					//load the next char in the compressed string
	cmp r0, #0	   					//if it reached the end of the string
	beq done    						//we're done
	mov r0, r4	   					//move the string to r0
	bl findAndDecompress  	//go to the @ finding subroutine
	add r4, r4, r0 					//add the index to the string to go to the next char the next time
	b mainLoop	   					//and do it all again

findAndDecompress:
	push { r4, r5, r6, lr } //push all registers we may use to the stack
	mov r4, r0 	            //put the string in r4
	ldrb r0, [r4]						//load the char again
	cmp r0, #'@'						//if the char is a @
	beq decode							//go to the decode subroutine

regularChar:
	bl handleChar	  				//go to the subroutine that handles regular characters
	mov r0, #1			  			//index ++

regularCharDone:
	pop {r4, r5, r6, pc}		//and pop all pushed registers

handleChar:
	push { r4, lr }    			//push some used registers to the stack
	mov r4, r0		   				//move the regular char to r4
	bl bufferAddChar	   		//add it to the buffer
	mov r0, r4		   				//move it back to r0
	cmp r0, #'_'	   				//if the character is not a '_'
	bne printChar 					//print it
	mov r0, #10		   				//if it is a '_', change it to a newLine and print

printChar:
	bl print	   						//call the print function
	pop { r4, pc } 					//and pop used registers

decode:
	ldr r0, =buffer	   			//place the buffer in r0
	ldrb r1, [r4 , #1] 			//place the offset in r1
	ldrb r2, [r4 , #2] 			//place the offset in r2
	mov r3, #48        			//place 48 in r3
	sub r5, r1, r3     			//decode the offset
	sub r6, r2, r3     			//decode the length
	add r4, r0, r5	   			//add the buffer with the offset and place it in r4

decodeLoop:
	cmp r6, #0	        		//if length is 0
	beq decodeLoopDone      //we're done
	ldrb r0, [r4]						//get the char from the buffer
	bl handleChar 					//print it and add it at the end of the buffer
	sub r6, r6, #1					//length --
	b decodeLoop		    		//do it again

decodeLoopDone:
	mov r0, #3 							//next time you get a char from the string, get it 3 places further
													//because the last 3 places were needed for the @, the offset and the length
	b regularCharDone				//and we're done

bufferAddChar:
	push { r4, lr } 				//push registers we're goning to use to the stack
	mov r4, r0							//place the char in r4
	ldr r3, =buffer					//set the buffer in r3
	mov r1, #39         		//set the last index of the buffer in r1
	add r0, r3, r1    			//and go to the end of the buffer

bufferShift:
	cmp r0, r3			  			//if we're done with shifting
	beq bufferShiftFinished //we're done
	sub r1, r0, #1 		   		//place r0 - 1 in r1
	ldrb r2, [r1]		   			//load the char in r0 - 1
	strb r2, [r0]		   			//store the char in r0
	mov r0, r1			   			//lower the index with 1
	b bufferShift         	//do this one more time

bufferShiftFinished:
	strb r4, [r0]	 					//store the new char in the buffer
	pop { r4, pc } 				 	//and pop all used registers

done:
