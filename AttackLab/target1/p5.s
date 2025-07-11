movq %rsp, %rax
ret
movq %rax, %rdi
ret
popq %rax
ret
movl %eax, %edx
ret
movl %edx, %ecx
ret
movl %ecx, %esi
ret
lea (%rdi,%rsi,1), %rax
ret
movq %rax, %rdi
ret