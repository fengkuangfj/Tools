
    
; ллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл
rotate PROTO

; ллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл

.code

; ллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл

mRotateRegisters proc
    db 48h

	; rotate registers in another order
	push rdx
	mov rdx,rcx
	mov rcx,rbx
	mov rbx,rax
	pop rax
	ret

mRotateRegisters endp

end