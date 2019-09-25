.text
.align 2

str: .asciz "Hello world"

.global application
application:
  ldr r0, =str
  bl print_asciz
