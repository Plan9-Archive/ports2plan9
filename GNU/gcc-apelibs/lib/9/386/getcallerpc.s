.globl	getcallerpc
getcallerpc:
	movl	4(%esp), %eax
	movl	-4(%eax), %eax
	ret
	