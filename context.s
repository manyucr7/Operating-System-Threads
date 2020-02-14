.text
.globl context_switch

context_switch:
	push %ebx
	push %esi
	push %edi
	push %ebp
	mov 20(%esp), %eax       # prev
	mov 24(%esp), %ecx       # next
	mov %esp, (%eax)        # prev->esp = esp
	mov (%ecx), %esp        # esp = next->esp
	pop %ebp
	pop %edi
	pop %esi
	pop %ebx
	ret
