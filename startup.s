	.section .text
	.global	_start
#	.type	_start,@function
_start:
	bx lr

1:
	b	1b

	.global	dispatch
#	.type	dispatch,@function
dispatch:
	bx lr