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
str_const12:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const0
	.byte	0
	.align	2
	.word	-1
str_const11:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const1
	.ascii	"String"
	.byte	0
	.align	2
	.word	-1
str_const10:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const2
	.ascii	"Bool"
	.byte	0
	.align	2
	.word	-1
str_const9:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const3
	.ascii	"Int"
	.byte	0
	.align	2
	.word	-1
str_const8:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const2
	.ascii	"Main"
	.byte	0
	.align	2
	.word	-1
str_const7:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const4
	.ascii	"D"
	.byte	0
	.align	2
	.word	-1
str_const6:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const4
	.ascii	"B"
	.byte	0
	.align	2
	.word	-1
str_const5:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const4
	.ascii	"C"
	.byte	0
	.align	2
	.word	-1
str_const4:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const4
	.ascii	"A"
	.byte	0
	.align	2
	.word	-1
str_const3:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const5
	.ascii	"IO"
	.byte	0
	.align	2
	.word	-1
str_const2:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const1
	.ascii	"Object"
	.byte	0
	.align	2
	.word	-1
str_const1:
	.word	9
	.word	8
	.word	String_dispTab
	.word	int_const6
	.ascii	"<basic class>"
	.byte	0
	.align	2
	.word	-1
str_const0:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const7
	.ascii	"case.cl"
	.byte	0
	.align	2
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
	.word	13
	.word	-1
int_const5:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	2
	.word	-1
int_const4:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	1
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
	.word	4
	.word	-1
int_const1:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	6
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
class_nameTab:
	.word	str_const2
	.word	str_const3
	.word	str_const4
	.word	str_const5
	.word	str_const6
	.word	str_const7
	.word	str_const8
	.word	str_const9
	.word	str_const10
	.word	str_const11
class_objTab:
	.word	Object_protObj
	.word	Object_init
	.word	IO_protObj
	.word	IO_init
	.word	A_protObj
	.word	A_init
	.word	C_protObj
	.word	C_init
	.word	B_protObj
	.word	B_init
	.word	D_protObj
	.word	D_init
	.word	Main_protObj
	.word	Main_init
	.word	Int_protObj
	.word	Int_init
	.word	Bool_protObj
	.word	Bool_init
	.word	String_protObj
	.word	String_init
Object_dispTab:
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
Bool_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
Int_dispTab:
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
Main_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Main.main
A_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
D_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
C_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
B_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	-1
Object_protObj:
	.word	0
	.word	3
	.word	Object_dispTab
	.word	-1
String_protObj:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const0
	.word	0
	.word	-1
Bool_protObj:
	.word	8
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
Int_protObj:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
IO_protObj:
	.word	1
	.word	3
	.word	IO_dispTab
	.word	-1
Main_protObj:
	.word	6
	.word	4
	.word	Main_dispTab
	.word	0
	.word	-1
A_protObj:
	.word	2
	.word	3
	.word	A_dispTab
	.word	-1
D_protObj:
	.word	5
	.word	3
	.word	D_dispTab
	.word	-1
C_protObj:
	.word	3
	.word	3
	.word	C_dispTab
	.word	-1
B_protObj:
	.word	4
	.word	3
	.word	B_dispTab
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
	addiu $sp $sp -12
	sw $fp 12($sp)
	sw $s0 8($sp)
	sw $ra 4($sp)
	addiu $fp $sp 4
	move $s0 $a0
	move $a0 $s0
	lw $fp 12($sp)
	lw $s0 8($sp)
	lw $ra 4($sp)
	addiu $sp $sp 12
	jr $ra
String_init:
	addiu $sp $sp -12
	sw $fp 12($sp)
	sw $s0 8($sp)
	sw $ra 4($sp)
	addiu $fp $sp 4
	move $s0 $a0
	jal	Object_init
	move $a0 $s0
	lw $fp 12($sp)
	lw $s0 8($sp)
	lw $ra 4($sp)
	addiu $sp $sp 12
	jr $ra
Bool_init:
	addiu $sp $sp -12
	sw $fp 12($sp)
	sw $s0 8($sp)
	sw $ra 4($sp)
	addiu $fp $sp 4
	move $s0 $a0
	jal	Object_init
	move $a0 $s0
	lw $fp 12($sp)
	lw $s0 8($sp)
	lw $ra 4($sp)
	addiu $sp $sp 12
	jr $ra
Int_init:
	addiu $sp $sp -12
	sw $fp 12($sp)
	sw $s0 8($sp)
	sw $ra 4($sp)
	addiu $fp $sp 4
	move $s0 $a0
	jal	Object_init
	move $a0 $s0
	lw $fp 12($sp)
	lw $s0 8($sp)
	lw $ra 4($sp)
	addiu $sp $sp 12
	jr $ra
IO_init:
	addiu $sp $sp -12
	sw $fp 12($sp)
	sw $s0 8($sp)
	sw $ra 4($sp)
	addiu $fp $sp 4
	move $s0 $a0
	jal	Object_init
	move $a0 $s0
	lw $fp 12($sp)
	lw $s0 8($sp)
	lw $ra 4($sp)
	addiu $sp $sp 12
	jr $ra
Main_init:
	addiu $sp $sp -12
	sw $fp 12($sp)
	sw $s0 8($sp)
	sw $ra 4($sp)
	addiu $fp $sp 4
	move $s0 $a0
	jal	IO_init
	move $a0 $s0
	lw $fp 12($sp)
	lw $s0 8($sp)
	lw $ra 4($sp)
	addiu $sp $sp 12
	jr $ra
A_init:
	addiu $sp $sp -12
	sw $fp 12($sp)
	sw $s0 8($sp)
	sw $ra 4($sp)
	addiu $fp $sp 4
	move $s0 $a0
	jal	IO_init
	move $a0 $s0
	lw $fp 12($sp)
	lw $s0 8($sp)
	lw $ra 4($sp)
	addiu $sp $sp 12
	jr $ra
D_init:
	addiu $sp $sp -12
	sw $fp 12($sp)
	sw $s0 8($sp)
	sw $ra 4($sp)
	addiu $fp $sp 4
	move $s0 $a0
	jal	A_init
	move $a0 $s0
	lw $fp 12($sp)
	lw $s0 8($sp)
	lw $ra 4($sp)
	addiu $sp $sp 12
	jr $ra
C_init:
	addiu $sp $sp -12
	sw $fp 12($sp)
	sw $s0 8($sp)
	sw $ra 4($sp)
	addiu $fp $sp 4
	move $s0 $a0
	jal	A_init
	move $a0 $s0
	lw $fp 12($sp)
	lw $s0 8($sp)
	lw $ra 4($sp)
	addiu $sp $sp 12
	jr $ra
B_init:
	addiu $sp $sp -12
	sw $fp 12($sp)
	sw $s0 8($sp)
	sw $ra 4($sp)
	addiu $fp $sp 4
	move $s0 $a0
	jal	C_init
	move $a0 $s0
	lw $fp 12($sp)
	lw $s0 8($sp)
	lw $ra 4($sp)
	addiu $sp $sp 12
	jr $ra
Main.main:
	addiu $sp $sp -16
	sw $fp 16($sp)
	sw $s0 12($sp)
	sw $ra 8($sp)
	addiu $fp $sp 4
	move $s0 $a0
	sw $s1 0($fp)
	lw $a0 12($s0)
	bne $a0 $zero label1
	la	$a0 str_const0
	li $t1 12
	jal _case_abort2
label1:
    # Load the tag number of input object
	lw $t2 0($a0)

    # If tag does not match this branch, jump to next branch
	blt $t2 5 label2
	bgt $t2 5 label2

    # Put aside the input object
    # I will push it onto stack instead
	move $s1 $a0

    # CodeGen for branch body
	la	$a0 D_protObj
	jal Object.copy
	jal	D_init

    # Move the input object back
    # I also need to pop that item off the stack
	move $s1 $a0

    # jump out of the case
	b label0
label2:
	blt $t2 4 label3
	bgt $t2 4 label3
	move $s1 $a0
	la	$a0 B_protObj
	jal Object.copy
	jal	B_init
	move $s1 $a0
	b label0
label3:
	blt $t2 3 label4
	bgt $t2 4 label4
	move $s1 $a0
	la	$a0 C_protObj
	jal Object.copy
	jal	C_init
	move $s1 $a0
	b label0
label4:
	blt $t2 2 label5
	bgt $t2 5 label5
	move $s1 $a0
	la	$a0 A_protObj
	jal Object.copy
	jal	A_init
	move $s1 $a0
	b label0
label5:
	jal _case_abort
label0:
	lw $s1 0($fp)
	lw $fp 16($sp)
	lw $s0 12($sp)
	lw $ra 8($sp)
	addiu $sp $sp 16
	jr $ra
