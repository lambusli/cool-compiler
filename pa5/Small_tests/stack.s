	.data
	.align	2
	.globl	class_nameTab
	.globl	Main_protObj
	.globl	Int_protObj
	.globl	String_protObj
	.globl	bool_const0
	.globl	bool_const1
	.globl	_int_tag
	.globl	_bool_tag
	.globl	_string_tag
_int_tag:
	.word	7
_bool_tag:
	.word	8
_string_tag:
	.word	9
	.globl	_MemMgr_INITIALIZER
_MemMgr_INITIALIZER:
	.word	_NoGC_Init
	.globl	_MemMgr_COLLECTOR
_MemMgr_COLLECTOR:
	.word	_NoGC_Collect
	.globl	_MemMgr_TEST
_MemMgr_TEST:
	.word	0
	.word	-1
str_const33:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const4
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const32:
	.word	9
	.word	7
	.word	String_dispTab
	.word	int_const9
	.ascii	"Cons_swap"
	.byte	0	
	.align	2
	.word	-1
str_const31:
	.word	9
	.word	7
	.word	String_dispTab
	.word	int_const9
	.ascii	"Cons_plus"
	.byte	0	
	.align	2
	.word	-1
str_const30:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const4
	.ascii	"Cons"
	.byte	0	
	.align	2
	.word	-1
str_const29:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const5
	.ascii	"Stack"
	.byte	0	
	.align	2
	.word	-1
str_const28:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const7
	.ascii	"A2I_adv"
	.byte	0	
	.align	2
	.word	-1
str_const27:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const3
	.ascii	"A2I"
	.byte	0	
	.align	2
	.word	-1
str_const26:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const6
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const25:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const4
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const24:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const3
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const23:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const2
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const22:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const6
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const21:
	.word	9
	.word	8
	.word	String_dispTab
	.word	int_const11
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const20:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"d"
	.byte	0	
	.align	2
	.word	-1
str_const19:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"e"
	.byte	0	
	.align	2
	.word	-1
str_const18:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"x"
	.byte	0	
	.align	2
	.word	-1
str_const17:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	">"
	.byte	0	
	.align	2
	.word	-1
str_const16:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"\n"
	.byte	0	
	.align	2
	.word	-1
str_const15:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"s"
	.byte	0	
	.align	2
	.word	-1
str_const14:
	.word	9
	.word	12
	.word	String_dispTab
	.word	int_const12
	.ascii	"You are on the stack bottom. "
	.byte	0	
	.align	2
	.word	-1
str_const13:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"+"
	.byte	0	
	.align	2
	.word	-1
str_const12:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"-"
	.byte	0	
	.align	2
	.word	-1
str_const11:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const0
	.byte	0	
	.align	2
	.word	-1
str_const10:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"9"
	.byte	0	
	.align	2
	.word	-1
str_const9:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"8"
	.byte	0	
	.align	2
	.word	-1
str_const8:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"7"
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"6"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"5"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"4"
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"3"
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"2"
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"1"
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"0"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	9
	.word	7
	.word	String_dispTab
	.word	int_const8
	.ascii	"stack.cl"
	.byte	0	
	.align	2
	.word	-1
int_const12:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	29
	.word	-1
int_const11:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	13
	.word	-1
int_const10:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	10
	.word	-1
int_const9:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	9
	.word	-1
int_const8:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	8
	.word	-1
int_const7:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	7
	.word	-1
int_const6:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	6
	.word	-1
int_const5:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	5
	.word	-1
int_const4:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	4
	.word	-1
int_const3:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	3
	.word	-1
int_const2:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	2
	.word	-1
int_const1:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	1
	.word	-1
int_const0:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
bool_const0:
	.word	8
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
bool_const1:
	.word	8
	.word	4
	.word	Bool_dispTab
	.word	1
	.word	-1
Object_protObj:
	.word	0
	.word	3
	.word	Object_dispTab
	.word	-1
IO_protObj:
	.word	1
	.word	3
	.word	IO_dispTab
	.word	-1
Int_protObj:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
Bool_protObj:
	.word	8
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
String_protObj:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const0
	.word	0
	.word	-1
A2I_protObj:
	.word	10
	.word	3
	.word	A2I_dispTab
	.word	-1
A2I_adv_protObj:
	.word	11
	.word	4
	.word	A2I_adv_dispTab
	.word	int_const0
	.word	-1
Stack_protObj:
	.word	2
	.word	3
	.word	Stack_dispTab
	.word	-1
Cons_protObj:
	.word	3
	.word	6
	.word	Cons_dispTab
	.word	str_const11
	.word	int_const0
	.word	0
	.word	-1
Cons_plus_protObj:
	.word	4
	.word	8
	.word	Cons_plus_dispTab
	.word	str_const11
	.word	int_const0
	.word	0
	.word	int_const0
	.word	int_const0
	.word	-1
Cons_swap_protObj:
	.word	5
	.word	8
	.word	Cons_swap_dispTab
	.word	str_const11
	.word	int_const0
	.word	0
	.word	str_const11
	.word	str_const11
	.word	-1
Main_protObj:
	.word	6
	.word	7
	.word	Main_dispTab
	.word	str_const11
	.word	0
	.word	bool_const0
	.word	0
class_nameTab:
	.word	str_const22
	.word	str_const23
	.word	str_const29
	.word	str_const30
	.word	str_const31
	.word	str_const32
	.word	str_const33
	.word	str_const24
	.word	str_const25
	.word	str_const26
	.word	str_const27
	.word	str_const28
class_objTab:
	.word	Object_protObj
	.word	Object_init
	.word	IO_protObj
	.word	IO_init
	.word	Stack_protObj
	.word	Stack_init
	.word	Cons_protObj
	.word	Cons_init
	.word	Cons_plus_protObj
	.word	Cons_plus_init
	.word	Cons_swap_protObj
	.word	Cons_swap_init
	.word	Main_protObj
	.word	Main_init
	.word	Int_protObj
	.word	Int_init
	.word	Bool_protObj
	.word	Bool_init
	.word	String_protObj
	.word	String_init
	.word	A2I_protObj
	.word	A2I_init
	.word	A2I_adv_protObj
	.word	A2I_adv_init
Object_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
IO_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
Int_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
Bool_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
String_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	String.length
	.word	String.concat
	.word	String.substr
A2I_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	A2I.c2i
	.word	A2I.i2c
	.word	A2I.a2i
	.word	A2I.a2i_aux
	.word	A2I.i2a
	.word	A2I.i2a_aux
A2I_adv_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	A2I.c2i
	.word	A2I.i2c
	.word	A2I.a2i
	.word	A2I.a2i_aux
	.word	A2I.i2a
	.word	A2I.i2a_aux
	.word	A2I_adv.chr_is_num
	.word	A2I_adv.str_is_num
Stack_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Stack.size
	.word	Stack.top
	.word	Stack.pop
	.word	Stack.push
	.word	Stack.eval
	.word	Stack.display
Cons_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Cons.size
	.word	Cons.top
	.word	Cons.pop
	.word	Stack.push
	.word	Stack.eval
	.word	Cons.display
	.word	Cons.init
Cons_plus_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Cons.size
	.word	Cons.top
	.word	Cons.pop
	.word	Stack.push
	.word	Stack.eval
	.word	Cons.display
	.word	Cons.init
	.word	Cons_plus.pop_then_plus
Cons_swap_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Cons.size
	.word	Cons.top
	.word	Cons.pop
	.word	Stack.push
	.word	Stack.eval
	.word	Cons.display
	.word	Cons.init
	.word	Cons_swap.pop_then_swap
Main_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Main.main
	.globl	heap_start
heap_start:
	.word	0
	.text
	.globl	Main_init
	.globl	Int_init
	.globl	String_init
	.globl	Bool_init
	.globl	Main.main
Object_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
IO_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Int_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Bool_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
String_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
A2I_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
A2I_adv_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	A2I_init
	la	$a0 int_const0
	sw	$a0 12($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Stack_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	IO_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Cons_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Stack_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Cons_plus_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Cons_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Cons_swap_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Cons_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Main_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	IO_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
A2I.c2i:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const1
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label0
	la	$a1 bool_const0
	jal equality_test
label0:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label1
	la	$a0 int_const0
	b	 label2
label1:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const2
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label3
	la	$a1 bool_const0
	jal equality_test
label3:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label4
	la	$a0 int_const1
	b	 label5
label4:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const3
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label6
	la	$a1 bool_const0
	jal equality_test
label6:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label7
	la	$a0 int_const2
	b	 label8
label7:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const4
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label9
	la	$a1 bool_const0
	jal equality_test
label9:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label10
	la	$a0 int_const3
	b	 label11
label10:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const5
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label12
	la	$a1 bool_const0
	jal equality_test
label12:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label13
	la	$a0 int_const4
	b	 label14
label13:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const6
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label15
	la	$a1 bool_const0
	jal equality_test
label15:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label16
	la	$a0 int_const5
	b	 label17
label16:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const7
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label18
	la	$a1 bool_const0
	jal equality_test
label18:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label19
	la	$a0 int_const6
	b	 label20
label19:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const8
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label21
	la	$a1 bool_const0
	jal equality_test
label21:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label22
	la	$a0 int_const7
	b	 label23
label22:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const9
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label24
	la	$a1 bool_const0
	jal equality_test
label24:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label25
	la	$a0 int_const8
	b	 label26
label25:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const10
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label27
	la	$a1 bool_const0
	jal equality_test
label27:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label28
	la	$a0 int_const9
	b	 label29
label28:
	move	$a0 $s0
	bne	$a0 $zero label30
	la	$a0 str_const0
	li	$t1 37
	jal _dispatch_abort
label30:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr	$t1
	la	$a0 int_const0
label29:
label26:
label23:
label20:
label17:
label14:
label11:
label8:
label5:
label2:
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 16
	jr	$ra	
A2I.i2c:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const0
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label31
	la	$a1 bool_const0
	jal equality_test
label31:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label32
	la	$a0 str_const1
	b	 label33
label32:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label34
	la	$a1 bool_const0
	jal equality_test
label34:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label35
	la	$a0 str_const2
	b	 label36
label35:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const2
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label37
	la	$a1 bool_const0
	jal equality_test
label37:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label38
	la	$a0 str_const3
	b	 label39
label38:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const3
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label40
	la	$a1 bool_const0
	jal equality_test
label40:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label41
	la	$a0 str_const4
	b	 label42
label41:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const4
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label43
	la	$a1 bool_const0
	jal equality_test
label43:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label44
	la	$a0 str_const5
	b	 label45
label44:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const5
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label46
	la	$a1 bool_const0
	jal equality_test
label46:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label47
	la	$a0 str_const6
	b	 label48
label47:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const6
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label49
	la	$a1 bool_const0
	jal equality_test
label49:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label50
	la	$a0 str_const7
	b	 label51
label50:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const7
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label52
	la	$a1 bool_const0
	jal equality_test
label52:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label53
	la	$a0 str_const8
	b	 label54
label53:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const8
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label55
	la	$a1 bool_const0
	jal equality_test
label55:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label56
	la	$a0 str_const9
	b	 label57
label56:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const9
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label58
	la	$a1 bool_const0
	jal equality_test
label58:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label59
	la	$a0 str_const10
	b	 label60
label59:
	move	$a0 $s0
	bne	$a0 $zero label61
	la	$a0 str_const0
	li	$t1 55
	jal _dispatch_abort
label61:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr	$t1
	la	$a0 str_const11
label60:
label57:
label54:
label51:
label48:
label45:
label42:
label39:
label36:
label33:
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 16
	jr	$ra	
A2I.a2i:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($fp)
	bne	$a0 $zero label62
	la	$a0 str_const0
	li	$t1 67
	jal _dispatch_abort
label62:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const0
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label63
	la	$a1 bool_const0
	jal equality_test
label63:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label64
	la	$a0 int_const0
	b	 label65
label64:
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label66
	la	$a0 str_const0
	li	$t1 68
	jal _dispatch_abort
label66:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const12
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label67
	la	$a1 bool_const0
	jal equality_test
label67:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label68
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label69
	la	$a0 str_const0
	li	$t1 68
	jal _dispatch_abort
label69:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	jal	Object.copy
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	sub	$t1 $t1 $t2
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label70
	la	$a0 str_const0
	li	$t1 68
	jal _dispatch_abort
label70:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label71
	la	$a0 str_const0
	li	$t1 68
	jal _dispatch_abort
label71:
	lw	$t1 8($a0)
	lw	$t1 24($t1)
	jalr	$t1
	jal	Object.copy
	lw	$t1 12($a0)
	neg	$t1 $t1
	sw	$t1 12($a0)
	b	 label72
label68:
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label73
	la	$a0 str_const0
	li	$t1 69
	jal _dispatch_abort
label73:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const13
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label74
	la	$a1 bool_const0
	jal equality_test
label74:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label75
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label76
	la	$a0 str_const0
	li	$t1 69
	jal _dispatch_abort
label76:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	jal	Object.copy
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	sub	$t1 $t1 $t2
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label77
	la	$a0 str_const0
	li	$t1 69
	jal _dispatch_abort
label77:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label78
	la	$a0 str_const0
	li	$t1 69
	jal _dispatch_abort
label78:
	lw	$t1 8($a0)
	lw	$t1 24($t1)
	jalr	$t1
	b	 label79
label75:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label80
	la	$a0 str_const0
	li	$t1 70
	jal _dispatch_abort
label80:
	lw	$t1 8($a0)
	lw	$t1 24($t1)
	jalr	$t1
label79:
label72:
label65:
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 16
	jr	$ra	
A2I.a2i_aux:
	addiu	$sp $sp -24
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 int_const0
	sw	$a0 12($fp)
	lw	$a0 24($fp)
	bne	$a0 $zero label81
	la	$a0 str_const0
	li	$t1 80
	jal _dispatch_abort
label81:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr	$t1
	sw	$a0 16($fp)
	la	$a0 int_const0
	sw	$a0 20($fp)
label82:
	lw	$a0 20($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($fp)
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label83
	la	$a0 bool_const0
label83:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label84
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const10
	jal	Object.copy
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 20($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 24($fp)
	bne	$a0 $zero label85
	la	$a0 str_const0
	li	$t1 84
	jal _dispatch_abort
label85:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label86
	la	$a0 str_const0
	li	$t1 84
	jal _dispatch_abort
label86:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr	$t1
	jal	Object.copy
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 12($fp)
	lw	$a0 20($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	jal	Object.copy
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 20($fp)
	b	 label82
label84:
	lw	$a0 12($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 28
	jr	$ra	
A2I.i2a:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label87
	la	$a0 bool_const0
label87:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label88
	la	$a0 str_const1
	b	 label89
label88:
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label90
	la	$a0 bool_const0
label90:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label91
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label92
	la	$a0 str_const0
	li	$t1 100
	jal _dispatch_abort
label92:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr	$t1
	b	 label93
label91:
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	jal	Object.copy
	lw	$t1 12($a0)
	neg	$t1 $t1
	sw	$t1 12($a0)
	jal	Object.copy
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label94
	la	$a0 str_const0
	li	$t1 101
	jal _dispatch_abort
label94:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const12
	bne	$a0 $zero label95
	la	$a0 str_const0
	li	$t1 101
	jal _dispatch_abort
label95:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr	$t1
label93:
label89:
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 16
	jr	$ra	
A2I.i2a_aux:
	addiu	$sp $sp -16
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 16($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label96
	la	$a0 bool_const0
label96:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label97
	la	$a0 str_const11
	b	 label98
label97:
	lw	$a0 16($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const10
	jal	Object.copy
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	div	$t1 $t1 $t2
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 12($fp)
	lw	$a0 16($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const10
	jal	Object.copy
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	jal	Object.copy
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	sub	$t1 $t1 $t2
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label99
	la	$a0 str_const0
	li	$t1 111
	jal _dispatch_abort
label99:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label100
	la	$a0 str_const0
	li	$t1 111
	jal _dispatch_abort
label100:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr	$t1
	bne	$a0 $zero label101
	la	$a0 str_const0
	li	$t1 111
	jal _dispatch_abort
label101:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr	$t1
label98:
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 20
	jr	$ra	
A2I_adv.chr_is_num:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label102
	la	$a0 str_const0
	li	$t1 130
	jal _dispatch_abort
label102:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const1
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label103
	la	$a1 bool_const0
	jal equality_test
label103:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label104
	la	$a0 bool_const1
	b	 label105
label104:
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label106
	la	$a0 str_const0
	li	$t1 131
	jal _dispatch_abort
label106:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const2
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label107
	la	$a1 bool_const0
	jal equality_test
label107:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label108
	la	$a0 bool_const1
	b	 label109
label108:
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label110
	la	$a0 str_const0
	li	$t1 132
	jal _dispatch_abort
label110:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const3
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label111
	la	$a1 bool_const0
	jal equality_test
label111:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label112
	la	$a0 bool_const1
	b	 label113
label112:
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label114
	la	$a0 str_const0
	li	$t1 133
	jal _dispatch_abort
label114:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const4
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label115
	la	$a1 bool_const0
	jal equality_test
label115:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label116
	la	$a0 bool_const1
	b	 label117
label116:
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label118
	la	$a0 str_const0
	li	$t1 134
	jal _dispatch_abort
label118:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const5
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label119
	la	$a1 bool_const0
	jal equality_test
label119:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label120
	la	$a0 bool_const1
	b	 label121
label120:
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label122
	la	$a0 str_const0
	li	$t1 135
	jal _dispatch_abort
label122:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const6
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label123
	la	$a1 bool_const0
	jal equality_test
label123:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label124
	la	$a0 bool_const1
	b	 label125
label124:
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label126
	la	$a0 str_const0
	li	$t1 136
	jal _dispatch_abort
label126:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const7
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label127
	la	$a1 bool_const0
	jal equality_test
label127:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label128
	la	$a0 bool_const1
	b	 label129
label128:
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label130
	la	$a0 str_const0
	li	$t1 137
	jal _dispatch_abort
label130:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const8
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label131
	la	$a1 bool_const0
	jal equality_test
label131:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label132
	la	$a0 bool_const1
	b	 label133
label132:
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label134
	la	$a0 str_const0
	li	$t1 138
	jal _dispatch_abort
label134:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const9
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label135
	la	$a1 bool_const0
	jal equality_test
label135:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label136
	la	$a0 bool_const1
	b	 label137
label136:
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label138
	la	$a0 str_const0
	li	$t1 139
	jal _dispatch_abort
label138:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const10
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label139
	la	$a1 bool_const0
	jal equality_test
label139:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label140
	la	$a0 bool_const1
	b	 label141
label140:
	la	$a0 bool_const0
label141:
label137:
label133:
label129:
label125:
label121:
label117:
label113:
label109:
label105:
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 16
	jr	$ra	
A2I_adv.str_is_num:
	addiu	$sp $sp -20
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 int_const0
	sw	$a0 12($s0)
	lw	$a0 20($fp)
	bne	$a0 $zero label142
	la	$a0 str_const0
	li	$t1 147
	jal _dispatch_abort
label142:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr	$t1
	sw	$a0 12($fp)
	la	$a0 int_const0
	sw	$a0 16($fp)
label143:
	lw	$a0 16($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label144
	la	$a0 bool_const0
label144:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label145
	lw	$a0 16($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 20($fp)
	bne	$a0 $zero label146
	la	$a0 str_const0
	li	$t1 150
	jal _dispatch_abort
label146:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label147
	la	$a0 str_const0
	li	$t1 150
	jal _dispatch_abort
label147:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 bool_const0
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label148
	la	$a1 bool_const0
	jal equality_test
label148:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label149
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	jal	Object.copy
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 12($s0)
	b	 label150
label149:
	lw	$a0 12($s0)
	sw	$a0 12($s0)
label150:
	lw	$a0 16($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	jal	Object.copy
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 16($fp)
	b	 label143
label145:
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const0
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label151
	la	$a1 bool_const0
	jal equality_test
label151:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label152
	la	$a0 bool_const1
	b	 label153
label152:
	la	$a0 bool_const0
label153:
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 24
	jr	$ra	
Stack.size:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 int_const0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Stack.top:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 str_const14
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Stack.pop:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Stack.push:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label154
	la	$a0 str_const0
	li	$t1 189
	jal _dispatch_abort
label154:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	jal	Object.copy
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 Cons_protObj
	jal	Object.copy
	jal	Cons_init
	bne	$a0 $zero label155
	la	$a0 str_const0
	li	$t1 189
	jal _dispatch_abort
label155:
	lw	$t1 8($a0)
	lw	$t1 52($t1)
	jalr	$t1
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 16
	jr	$ra	
Stack.eval:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	move	$a0 $s0
	bne	$a0 $zero label156
	la	$a0 str_const0
	li	$t1 193
	jal _dispatch_abort
label156:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const13
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label157
	la	$a1 bool_const0
	jal equality_test
label157:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label158
	move	$a0 $s0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 Cons_plus_protObj
	jal	Object.copy
	jal	Cons_plus_init
	bne	$a0 $zero label159
	la	$a0 str_const0
	li	$t1 193
	jal _dispatch_abort
label159:
	lw	$t1 8($a0)
	lw	$t1 56($t1)
	jalr	$t1
	b	 label160
label158:
	move	$a0 $s0
	bne	$a0 $zero label161
	la	$a0 str_const0
	li	$t1 194
	jal _dispatch_abort
label161:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const15
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label162
	la	$a1 bool_const0
	jal equality_test
label162:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label163
	move	$a0 $s0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 Cons_swap_protObj
	jal	Object.copy
	jal	Cons_swap_init
	bne	$a0 $zero label164
	la	$a0 str_const0
	li	$t1 194
	jal _dispatch_abort
label164:
	lw	$t1 8($a0)
	lw	$t1 56($t1)
	jalr	$t1
	b	 label165
label163:
	move	$a0 $s0
	bne	$a0 $zero label166
	la	$a0 str_const0
	li	$t1 195
	jal _dispatch_abort
label166:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 A2I_adv_protObj
	jal	Object.copy
	jal	A2I_adv_init
	bne	$a0 $zero label167
	la	$a0 str_const0
	li	$t1 195
	jal _dispatch_abort
label167:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 bool_const1
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label168
	la	$a1 bool_const0
	jal equality_test
label168:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label169
	move	$a0 $s0
	b	 label170
label169:
	move	$a0 $s0
	bne	$a0 $zero label171
	la	$a0 str_const0
	li	$t1 196
	jal _dispatch_abort
label171:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const0
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label172
	la	$a1 bool_const0
	jal equality_test
label172:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label173
	move	$a0 $s0
	b	 label174
label173:
	move	$a0 $s0
	bne	$a0 $zero label175
	la	$a0 str_const0
	li	$t1 197
	jal _dispatch_abort
label175:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr	$t1
	move	$a0 $s0
label174:
label170:
label165:
label160:
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Stack.display:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 str_const11
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label176
	la	$a0 str_const0
	li	$t1 202
	jal _dispatch_abort
label176:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr	$t1
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Cons.size:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 16($s0)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Cons.top:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($s0)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Cons.pop:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 16($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	jal	Object.copy
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	sub	$t1 $t1 $t2
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 16($s0)
	lw	$a0 20($s0)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Cons.init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 20($fp)
	sw	$a0 12($s0)
	lw	$a0 16($fp)
	sw	$a0 16($s0)
	lw	$a0 12($fp)
	sw	$a0 20($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 24
	jr	$ra	
Cons.display:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 str_const16
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label177
	la	$a0 str_const0
	li	$t1 233
	jal _dispatch_abort
label177:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label178
	la	$a0 str_const0
	li	$t1 233
	jal _dispatch_abort
label178:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr	$t1
	bne	$a0 $zero label179
	la	$a0 str_const0
	li	$t1 233
	jal _dispatch_abort
label179:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr	$t1
	lw	$a0 20($s0)
	bne	$a0 $zero label180
	la	$a0 str_const0
	li	$t1 234
	jal _dispatch_abort
label180:
	lw	$t1 8($a0)
	lw	$t1 48($t1)
	jalr	$t1
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Cons_plus.pop_then_plus:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($fp)
	bne	$a0 $zero label181
	la	$a0 str_const0
	li	$t1 249
	jal _dispatch_abort
label181:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr	$t1
	sw	$a0 12($fp)
	lw	$a0 12($fp)
	bne	$a0 $zero label182
	la	$a0 str_const0
	li	$t1 253
	jal _dispatch_abort
label182:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const2
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label183
	la	$a0 bool_const0
label183:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label184
	la	$a0 bool_const0
label184:
	lw	$t1 12($a0)
	beqz	$t1 label185
	lw	$a0 12($fp)
	bne	$a0 $zero label186
	la	$a0 str_const0
	li	$t1 254
	jal _dispatch_abort
label186:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 A2I_adv_protObj
	jal	Object.copy
	jal	A2I_adv_init
	bne	$a0 $zero label187
	la	$a0 str_const0
	li	$t1 254
	jal _dispatch_abort
label187:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 24($s0)
	lw	$a0 12($fp)
	bne	$a0 $zero label188
	la	$a0 str_const0
	li	$t1 254
	jal _dispatch_abort
label188:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr	$t1
	sw	$a0 12($fp)
	lw	$a0 12($fp)
	bne	$a0 $zero label189
	la	$a0 str_const0
	li	$t1 255
	jal _dispatch_abort
label189:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 A2I_adv_protObj
	jal	Object.copy
	jal	A2I_adv_init
	bne	$a0 $zero label190
	la	$a0 str_const0
	li	$t1 255
	jal _dispatch_abort
label190:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 28($s0)
	lw	$a0 12($fp)
	bne	$a0 $zero label191
	la	$a0 str_const0
	li	$t1 255
	jal _dispatch_abort
label191:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr	$t1
	sw	$a0 12($fp)
	lw	$a0 24($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 28($s0)
	jal	Object.copy
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	addiu	$sp $sp 4
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 A2I_adv_protObj
	jal	Object.copy
	jal	A2I_adv_init
	bne	$a0 $zero label192
	la	$a0 str_const0
	li	$t1 258
	jal _dispatch_abort
label192:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label193
	la	$a0 str_const0
	li	$t1 258
	jal _dispatch_abort
label193:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr	$t1
	sw	$a0 12($fp)
	b	 label194
label185:
	move	$a0 $s0
	bne	$a0 $zero label195
	la	$a0 str_const0
	li	$t1 260
	jal _dispatch_abort
label195:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr	$t1
label194:
	lw	$a0 12($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 16
	jr	$ra	
Cons_swap.pop_then_swap:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 12($fp)
	bne	$a0 $zero label196
	la	$a0 str_const0
	li	$t1 276
	jal _dispatch_abort
label196:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr	$t1
	sw	$a0 12($fp)
	lw	$a0 12($fp)
	bne	$a0 $zero label197
	la	$a0 str_const0
	li	$t1 280
	jal _dispatch_abort
label197:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr	$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const2
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label198
	la	$a0 bool_const0
label198:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label199
	la	$a0 bool_const0
label199:
	lw	$t1 12($a0)
	beqz	$t1 label200
	lw	$a0 12($fp)
	bne	$a0 $zero label201
	la	$a0 str_const0
	li	$t1 281
	jal _dispatch_abort
label201:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr	$t1
	sw	$a0 24($s0)
	lw	$a0 12($fp)
	bne	$a0 $zero label202
	la	$a0 str_const0
	li	$t1 281
	jal _dispatch_abort
label202:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr	$t1
	sw	$a0 12($fp)
	lw	$a0 12($fp)
	bne	$a0 $zero label203
	la	$a0 str_const0
	li	$t1 282
	jal _dispatch_abort
label203:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr	$t1
	sw	$a0 28($s0)
	lw	$a0 12($fp)
	bne	$a0 $zero label204
	la	$a0 str_const0
	li	$t1 282
	jal _dispatch_abort
label204:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr	$t1
	sw	$a0 12($fp)
	lw	$a0 28($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 24($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label205
	la	$a0 str_const0
	li	$t1 283
	jal _dispatch_abort
label205:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr	$t1
	bne	$a0 $zero label206
	la	$a0 str_const0
	li	$t1 283
	jal _dispatch_abort
label206:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr	$t1
	sw	$a0 12($fp)
	b	 label207
label200:
	move	$a0 $s0
	bne	$a0 $zero label208
	la	$a0 str_const0
	li	$t1 284
	jal _dispatch_abort
label208:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr	$t1
label207:
	lw	$a0 12($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 16
	jr	$ra	
Main.main:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 Stack_protObj
	jal	Object.copy
	jal	Stack_init
	sw	$a0 16($s0)
	la	$a0 bool_const1
	sw	$a0 20($s0)
label209:
	lw	$a0 20($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 bool_const1
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label210
	la	$a1 bool_const0
	jal equality_test
label210:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label211
	la	$a0 str_const17
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label212
	la	$a0 str_const0
	li	$t1 303
	jal _dispatch_abort
label212:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr	$t1
	move	$a0 $s0
	bne	$a0 $zero label213
	la	$a0 str_const0
	li	$t1 304
	jal _dispatch_abort
label213:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr	$t1
	sw	$a0 12($s0)
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const18
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label214
	la	$a1 bool_const0
	jal equality_test
label214:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label215
	la	$a0 bool_const0
	sw	$a0 20($s0)
	b	 label216
label215:
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const19
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label217
	la	$a1 bool_const0
	jal equality_test
label217:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label218
	lw	$a0 16($s0)
	bne	$a0 $zero label219
	la	$a0 str_const0
	li	$t1 306
	jal _dispatch_abort
label219:
	lw	$t1 8($a0)
	lw	$t1 44($t1)
	jalr	$t1
	sw	$a0 16($s0)
	b	 label220
label218:
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const20
	lw	$t1 4($sp)
	move	$t2 $a0
	la	$a0 bool_const1
	beq	$t1 $t2 label221
	la	$a1 bool_const0
	jal equality_test
label221:
	addiu	$sp $sp 4
	lw	$t1 12($a0)
	beqz	$t1 label222
	lw	$a0 16($s0)
	bne	$a0 $zero label223
	la	$a0 str_const0
	li	$t1 307
	jal _dispatch_abort
label223:
	lw	$t1 8($a0)
	lw	$t1 48($t1)
	jalr	$t1
	b	 label224
label222:
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	bne	$a0 $zero label225
	la	$a0 str_const0
	li	$t1 308
	jal _dispatch_abort
label225:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr	$t1
	sw	$a0 16($s0)
label224:
label220:
label216:
	b	 label209
label211:
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
