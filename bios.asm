.data 0x00
.text
	addi $sp, $sp, 4
	sw $fp, 0($sp)
	sw $sp, 4($sp)
	sw $s0, 8($sp)
	sw $s1, 12($sp)
	sw $s2, 16($sp)
	sw $s3, 20($sp)
	sw $s4, 24($sp)
	sw $s5, 28($sp)
	sw $s6, 32($sp)
	sw $s7, 36($sp)
	mfc0 $s1, $t5, 0
	ori $s1, $s1, 124
	addi $s2, $Zero, 32
	bne $s1, $s2, 8
	bne $a0, $Zero, 2
	lw $v0, -1024($Zero)
	addi $s3, $Zero, 1
	bne $a0, $s3, 2
	lw $v0, -1022($Zero)
	lw $s0, 8($sp)
	lw $s1, 12($sp)
	lw $s2, 16($sp)
	lw $s3, 20($sp)
	lw $s4, 24($sp)
	lw $s5, 28($sp)
	lw $s6, 32($sp)
	lw $s7, 36($sp)
	lw $fp, 0($sp)
	lw $sp, 4($sp)
	eret

	addi $t0, $Zero, 22
	sw $t0, -1024($Zero)
	addi $t0, $Zero, -1
	sw $t0, -1020($Zero)
	addi $a0, $Zero, 0
	syscall
	sw $v0, -926($Zero)