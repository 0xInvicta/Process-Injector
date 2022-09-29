;msgbox.asm 
[SECTION .text]

global _start


_start:
	;eax holds return value
	;ebx will hold function addresses
	;ecx will hold string pointers
	;edx will hold NULL

	
	xor eax,eax
	xor ebx,ebx			
	xor ecx,ecx
	xor edx,edx
	
	jmp short GetLibrary
LibraryReturn:
	pop ecx				
	mov [ecx + 10], dl		
	mov ebx, 0x77e7d961		
	push ecx			
	call ebx			

	jmp short FunctionName
FunctionReturn:

	pop ecx				
	xor edx,edx
	mov [ecx + 11],dl		
	push ecx
	push eax
	mov ebx, 0x77e7b332		;GetProcAddress(hmodule,functionname);
	call ebx			
	
	jmp short Message
MessageReturn:
	pop ecx				
	xor edx,edx			
	mov [ecx+3],dl			

	xor edx,edx
	
	push edx			
	push ecx			
	push ecx			
	push edx			
	
	call eax			;MessageBoxA(windowhandle,msg,title,type)

ender:
	xor edx,edx
	push eax			
	mov eax, 0x77e798fd 		;exitprocess(exitcode);
	call eax			
	
GetLibrary:
	call LibraryReturn
	db 'user32.dllN'
FunctionName
	call FunctionReturn
	db 'MessageBoxAN'
Message
	call MessageReturn
	db 'TEST'