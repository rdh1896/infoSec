; Russell Harvey
; 10/28/2019
;Directives - in every .asm program

.586
.model flat, stdcall
.stack 4096				; Make the stack/heap size to be 4k

;library includes
includelib libcmt.lib
includelib libvcruntime.lib
includelib libucrt.lib
includelib legacy_stdio_definitions.lib   ; Gives us access to C function calls from asm

extern printf:NEAR  ;Indicates that we'll be using printf from a library
extern scanf:NEAR   ;Indicates that we'll be using scanf from a library
ExitProcess PROTO,dwExitCode: DWORD   ;ExitProcess is a funcction defined by Windows that we'll be using

.data
	myname db "Russell Harvey", 0Ah, 0
	prompt1 db "Enter an integer: ", 0Ah, 0
	holder1 dd 0
	input1 dd 0
	checkInput db "Converting %d to a sum of bytes...", 0Ah, 0 
	formatin1 db "%d"
	prompt2 db "Enter another integer: ", 0Ah, 0
	holder2 dd 0
	input2 dd 0
	formatin2 db "%d"
	result db "The sum of squares is: %d", 0Ah, 0
	answer dd 0
	result2 db "The sum of bytes is: %d", 0Ah, 0
	answer2 dd 0

.code
	main PROC c
		;Print Name
		push offset myname
		call printf
		add esp,4

		;Push Prompt1
		push offset prompt1
		call printf
		add esp,4

		;Push Input1
		push offset input1
		push offset formatin1
		call scanf

		;Square Input1
		mov eax, input1
		imul eax
		add esp,8
		push offset holder1
		mov holder1, eax
		add esp,4

		;Push Prompt2
		push offset prompt2
		call printf
		add esp,4

		;Push Input2
		push offset input2
		push offset formatin2
		call scanf

		;Square Input2
		mov eax, input2
		imul eax
		add esp,8
		push offset holder2
		mov holder2, eax
		add esp,4

		; Add Squared Input1 and Input2
		push offset holder1
		push offset holder2
		push offset answer
		mov eax, holder1
		add eax, holder2
		mov answer, eax
		add esp,12

		;Push Result
		push answer
		push offset result
		call printf
		add esp,8

		;Check that Input1 is Original
		push input1
		push offset checkInput
		call printf
		add esp,8

		;Convert Input1 to Hex
		mov eax, offset input1
		mov ebx, 0
		mov ecx, 0
		mov bl, BYTE PTR[eax]
		add ecx, ebx
		mov ebx, 0
		mov bl, BYTE PTR[eax+1]
		add ecx, ebx
		mov ebx, 0
		mov bl, BYTE PTR[eax+2]
		add ecx, ebx
		mov ebx, 0
		mov bl, BYTE PTR[eax+3]
		add ecx, ebx
		mov answer2, ecx

		; Print the Bytes Result
		push answer2
		push offset result2
		call printf
		add esp,8
		
		;Exit Proc
		INVOKE ExitProcess, 0
	main endp
end


