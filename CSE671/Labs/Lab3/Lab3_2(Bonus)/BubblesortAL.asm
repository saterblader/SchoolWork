TITLE BubblesortALs					(BubblesortAL.asm)

INCLUDE Irvine32.inc
.data

; Variable declaration

TimeTaken BYTE "Sort took: ",0
Units BYTE " Milliseconds.",0dh,0ah,0
i			DWORD	?
newn		DWORD	?
array		DWORD	100000 DUP(?)
startTime	DWORD	?

.code
main PROC

	call Clrscr ; clear display
	call Rand ; call rand procedure
	call GetMseconds ; get start time
	mov startTime, eax ; store start time
	call BubbleSort ; call bubble sort procedure
	call GetMseconds ; get end time
	sub eax, startTime ; figure out runtime
	mov startTime, eax ; store runtime
	call Crlf ; Newline
	mov edx, OFFSET TimeTaken ; move 'Sort took: ' into register for writing
	call WriteString ; write 'Sort took: "
	mov eax, startTime ; move runtime for writing
	call WriteInt ; write runtime
	mov edx, OFFSET Units ; move 'Milliseconds'
	Call WriteString ; write "Milliseconds'
	call Crlf ; newline

	exit
main ENDP

Rand PROC
	mov i, LENGTHOF array ; size array into i
	mov ecx, i ; move i into ecx
	mov ebx, 0 ; set ebx to zero
	
Randomgen:
	call Random32 ; get random number
	mov [array + ebx], eax ; store random number
	add ebx, TYPE array ; increment array index
	loop Randomgen ; loop random generation
	ret
Rand ENDP

BubbleSort PROC	

	mov edi, LENGTHOF array ; size of array into edi

  WhileLoop:

	mov newn, 0 ; init variable
	mov i, 0 ; init variable

	ForLoop:
		
		inc i ; increment 'i'
		mov edx, i ; move 'i' into edx
		dec edi ; decrement edi
		cmp edx, edi ; compare edx and edi
		ja EndFor ; jump to end of loop
		mov ebx, 4 ; move 4 into ebx
		
		While2:
		cmp edx, 1 ; compare i and edx
		je L2 ; jump to L2
		add ebx, 4 ; add 4 to ebx
		dec edx ; subtract 1 from edx
		Loop While2 ; loop to While2

		L2:
		mov esi, array[ebx-4] ; load previous value
		cmp esi, array[ebx] ; compare previous to current  value
		
		jg Swap ; jump to swap
		jmp L3 ; jump to L3
      
		Swap:
		xchg array[ebx], esi ; swap current with esi
		mov array[ebx-4], esi ; swap prev with esi

		L3:
		mov edx, i ; move edx into i
		mov newn, edx; move edx into newn
		Loop ForLoop ; loop forloop
	
  EndFor:
	mov edx, newn ; move edx into newn
    mov edi, edx ; move edi into edx
;Loop WhileLoop
	cmp edi, 0 ; compare zero and edi
	jne Whileloop ; exit if edi=0

L1:
  ret ; return to main procedure 
BubbleSort ENDP


END main