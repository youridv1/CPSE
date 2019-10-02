.text
.global toggle_case
toggle_case:
    cmp     r0, #'a'        @ Check if r0 is bigger than 'a'
    blo     uppercase       @ if the cmp shows that r0 is  lower then "a". go to uppercase.
    cmp     r0, #'z'        @ check if r0 is equal to 'z'
    bhi     end             @ if r0 is higher than "z" go to end because it is not a letter
    sub     r0, r0, #32     @ if r0 is an lowercase letter, subtract 32 to make it a uppercase
    b       end             @ r0 is converted; go to end

uppercase:
    cmp     r0, #'A'        @ Compare r0 to 'A'
    blo     end             @ if r0 is lower than 'A' it is not a letter; Go to end
    cmp     r0, #'Z'        @ Compare r0 to 'Z'
    bhi     end             @ if r0 is higher than 'Z' it is not a letter; go to end
    ADD     r0, r0, #32     @ r0 is an uppercase letter, add 32 to make it an lowercase letter
    b       end             @ r0 is converted; go to end

end:
    mov     pc, lr          @ load link register to program counter
