
    
; ллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл
rotate PROTO

; ллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл

.code

; ллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл

AsmRotate64  proc FRAME
    db 48h
    push rbx
    .allocstack 8

    push rbx
    .allocstack 8

    push rcx
    .allocstack 8

    push rdx
    .allocstack 8

    pushfq
    .allocstack 8

    sub rsp,20h
    .allocstack 20h
.endprolog


    ;put stupid value in flags
    mov rax,02d7H
    push rax
    popfq

    mov rax, 10H
    mov rbx, 20H
    mov rcx, 30H
    mov rdx, 40H
    
    call rotate

    ;save flags for futur checking
    pushfq

    ;check registers values
    cmp rax,20H
    jne label_error

    cmp rbx,30H
    jne label_error

    cmp rcx,40H
    jne label_error

    cmp rdx,10H
    jne label_error

    ;check flags value
    pop rax
    cmp rax,02d7H
    je label_success

    label_error:
    pop rax ; rax has not been poped
    mov rax,0
    jmp label_end

    label_success:
    mov rax,1
    ;jmp label_end


    label_end:
    add rsp,20h
    popfq
    pop rdx
    pop rcx
    pop rbx


    pop rbx
    ret
AsmRotate64 endp


; ллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл

rotate proc
    db 48h

	; rotate registers 
	push rax
	mov rax,rbx
	mov rbx,rcx
	mov rcx,rdx
	pop rdx
	ret

rotate endp

end