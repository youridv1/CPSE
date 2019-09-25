.global convert
convert:
    ldrb    r0, [r0]        @ Load r0 from memory
    cmp     r0, #'a'        @ Check if r0 is equal to 96 (ascii char "'")
    blo     uppercase       @ if the cmp shows that r0 is  lower then "'" or equal to. go to lowercase check
    cmp     r0, #'z'        @ check if r0 is equal to 123 (ascii char "{")
    bhi     end             @ if r0 is higher then "{" go to end because it is no letter
    sub     r0, r0, #32     @ if r0 is an lowercase letter, subtract 32 to make it a uppercase
    b       end             @ r0 is converted; go to end

uppercase:
    cmp     r0, #'A'        @ Check is r0 is equal to 64 (ascii char "@")
    blo     end             @ if r0 is lower or equal to "@" it is no letter; Go to end
    cmp     r0, #'Z'        @ Check if r0 is  equal to 91 (ascii char "[")
    bhi     end             @ if r0 is higher or equal to "[" it is not a letter; go to end
    ADD     r0, r0, #32     @ r0 is an uppercase letter, add 32 to make it an lowercase letter
    b       end             @ r0 is converted; go to end

end:
    mov     pc, lr          @ load link register to program counter
