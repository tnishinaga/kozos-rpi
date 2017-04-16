	.h8300h
	.section .text
	.global	_start
#	.type	_start,@function
_start:
	mov.l	#_bootstack,sp
	jsr	@_main

1:
	bra	1b

	.global	_dispatch
#	.type	_dispatch,@function
_dispatch:
	mov.l	@er0,er7
	mov.l	@er7+,er0
	mov.l	@er7+,er1
	mov.l	@er7+,er2
	mov.l	@er7+,er3
	mov.l	@er7+,er4
	mov.l	@er7+,er5
	mov.l	@er7+,er6
	rte
