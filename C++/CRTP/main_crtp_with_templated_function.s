	.file	"main_crtp_with_templated_function.cpp"
	.text
	.p2align 4,,15
	.def	__tcf_0;	.scl	3;	.type	32;	.endef
	.seh_proc	__tcf_0
__tcf_0:
.LFB2089:
	.seh_endprologue
	leaq	_ZStL8__ioinit(%rip), %rcx
	jmp	_ZNSt8ios_base4InitD1Ev
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC0:
	.ascii "Hello from DerivedfromBase2_1 \0"
	.text
	.align 2
	.p2align 4,,15
	.def	_ZN19DerivedfromBased2_120say_hello_from_Base2Ev.isra.3;	.scl	3;	.type	32;	.endef
	.seh_proc	_ZN19DerivedfromBased2_120say_hello_from_Base2Ev.isra.3
_ZN19DerivedfromBased2_120say_hello_from_Base2Ev.isra.3:
.LFB2094:
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	movq	.refptr._ZSt4cout(%rip), %rcx
	movl	$30, %r8d
	leaq	.LC0(%rip), %rdx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_x
	movq	.refptr._ZSt4cout(%rip), %rcx
	addq	$40, %rsp
	jmp	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section	.text.startup,"x"
	.p2align 4,,15
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB1599:
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	call	__main
	call	_ZN19DerivedfromBased2_120say_hello_from_Base2Ev.isra.3
	call	_ZN19DerivedfromBased2_120say_hello_from_Base2Ev.isra.3
	call	_ZN19DerivedfromBased2_120say_hello_from_Base2Ev.isra.3
	xorl	%eax, %eax
	addq	$40, %rsp
	ret
	.seh_endproc
	.p2align 4,,15
	.def	_GLOBAL__sub_I_main;	.scl	3;	.type	32;	.endef
	.seh_proc	_GLOBAL__sub_I_main
_GLOBAL__sub_I_main:
.LFB2090:
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	leaq	_ZStL8__ioinit(%rip), %rcx
	call	_ZNSt8ios_base4InitC1Ev
	leaq	__tcf_0(%rip), %rcx
	addq	$40, %rsp
	jmp	atexit
	.seh_endproc
	.section	.ctors,"w"
	.align 8
	.quad	_GLOBAL__sub_I_main
.lcomm _ZStL8__ioinit,1,1
	.ident	"GCC: (x86_64-posix-seh, Built by strawberryperl.com project) 8.3.0"
	.def	_ZNSt8ios_base4InitD1Ev;	.scl	2;	.type	32;	.endef
	.def	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_x;	.scl	2;	.type	32;	.endef
	.def	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_;	.scl	2;	.type	32;	.endef
	.def	_ZNSt8ios_base4InitC1Ev;	.scl	2;	.type	32;	.endef
	.def	atexit;	.scl	2;	.type	32;	.endef
	.section	.rdata$.refptr._ZSt4cout, "dr"
	.globl	.refptr._ZSt4cout
	.linkonce	discard
.refptr._ZSt4cout:
	.quad	_ZSt4cout
