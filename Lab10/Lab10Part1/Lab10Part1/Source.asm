; Russell Harvey
; 10/31/2019

.586
.model flat,stdcall
.stack 2048

includelib libcmt.lib
includelib libvcruntime.lib
includelib libucrt.lib
includelib legacy_stdio_definitions.lib

extern printf:NEAR
extern scanf:NEAR
ExitProcess PROTO, dwExitCode: DWORD

.data
	prompt db "Enter an integer: ", 0
	output db "%d! = %d", 0Ah, 0
	formatinput db "%d", 0
	limit dd 0

.code
	main Proc c
	
	; Show User the Prompt
	; Equivalent to printf(prompt)
	push offset prompt	; offset -> & | variable -> mem addr of variable
	call printf
	add esp,4	; Getting rid of the addr of prompt

	; Get input from the user
	; Equivalent to scanf("%d", &limit)
	push offset limit	; Put &limit on the stack
	push offset formatinput	; Put the addr of "%d" on the stack
	call scanf
	add esp,8	; getting rid of offset limit, offset formatinput

	; Factorial
	mov ebx, 1	; Start our loop counter at 1
	mov ecx, 1	; Start our accumulator at 1
topofloop:
	cmp ebx, limit	; Compare ebx to limit
	jg pastloop	; Jump past the loop if ebx is greater than limit

	imul ecx, ebx
	push ecx
	push ecx
	push ebx
	push offset output
	call printf
	add esp,12
	pop ecx	; Restores ecx after calling printf()
	add ebx, 1

	jmp topofloop
pastloop:
	; printf("%d! = %d, limit, ecx")
	push ecx
	push limit
	push offset output
	call printf



	INVOKE ExitProcess, 0
	main endp
end
	