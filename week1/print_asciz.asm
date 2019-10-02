.text
.align 2
.global print_asciz
print_asciz:
  push { r5, lr }     @ push r5 and the lr to the stack as they are to remain untouched
  mov r5, r0          @ move the contents of r0 into r5
loop:
  ldrb r0, [ r5 ]     @ load the byte which is at the memory address in r5 into r0
  add r0, r0, #0      @ check if zero
  beq done            @ if zero then this is the terminator byte so we're done printing
  bl toggle_case      @ go to the toggle_case label to invert the case of the char
  bl uart_put_char    @ go to the uart_put_char to print the char
  add r5, r5, #1      @increase r5 by one to select the next char from memory
  b loop              @ go back to the beginning of the loop
done:
  pop { r5, pc }      @ pop the contents of the holy registers back from the stack into their respective places
