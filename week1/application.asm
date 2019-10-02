.text
.align 2

str: .asciz "Hello world" @ create string

.global application
application:
  ldr r0, =str @ load memory address of the beginning of the string into r0
  bl print_asciz @ go to the print_asciz label.
