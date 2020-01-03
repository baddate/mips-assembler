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
	andi $s1, $s1, 124
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
delay:
	addi $t1, $Zero, 30000
	add $s1, $Zero, $t1
label0:
	addi $t2, $Zero, 0
	sub $t0, $t2, $s1
	bltz $t0, label1
	j label2
label1:
	addi $t3, $Zero, 1
	sub $t4, $s1, $t3
	add $s1, $Zero, $t4
	j label0
label2:
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
	jr $ra
test:
	addi $t0, $sp, -4
	lw $a0, 0($t0)
	addi $t5, $Zero, 2
	mult $a0, $t5
	mfhi $t6
	mflo $t6
	addi $t7, $Zero, 2
	div $t6, $t7
	mfhi $t8
	mflo $t8
	addi $t9, $Zero, 1
	add $t9, $t8, $t9
	add $a0, $Zero, $t9
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
	add $v0, $Zero, $a0
	jr $ra
main:
	sw $fp,0($sp)
	sw $sp, 8($sp)
	addi $fp, $sp, 8
	addi $sp, $sp, 12
	addi $t0, $Zero, 22
	sw $t0, -1024($Zero)
	addi $t0, $Zero, -1
	sw $t0, -1020($Zero)
	addi $a0, $Zero, 0
	syscall
	sw $v0, -926($Zero)
	addi $t1, $Zero, 0
	add $s1, $Zero, $t1
label3:
	addi $t2, $Zero, 1
	addi $t3, $Zero, 0
	bne $t2, $t3, label4
	j label5
label4:
	addi $sp, $sp, 4
	sw $s1, 0($sp)
	addi $sp, $sp, 4
	sw $fp,0($sp)
	sw $sp, 4($sp)
	sw $s0, 8($sp)
	sw $s1, 12($sp)
	sw $s2, 16($sp)
	sw $s3, 20($sp)
	sw $s4, 24($sp)
	sw $s5, 28($sp)
	sw $s6, 32($sp)
	sw $s7, 36($sp)
	jal test
	add $t4 , $Zero, $v0
	add $s1, $Zero, $t4
	addi $t5, $Zero, -928
	sw $s1, -928($Zero)
	addi $t6, $Zero, -926
	addi $t7, $Zero, 16
	srlv $t8, $s1, $t7
	sw $t8, -926($Zero)
	addi $t9, $Zero, 10
	sub $t0, $t9, $s1
	bltz $t0, label6
	j label7
label6:
	addi $t1, $Zero, 0
	add $s1, $Zero, $t1
label7:
	addi $sp, $sp, 4
	sw $fp,0($sp)
	sw $sp, 4($sp)
	sw $s0, 8($sp)
	sw $s1, 12($sp)
	sw $s2, 16($sp)
	sw $s3, 20($sp)
	sw $s4, 24($sp)
	sw $s5, 28($sp)
	sw $s6, 32($sp)
	sw $s7, 36($sp)
	jal delay
	j label3
label5:
	addi $t2, $Zero, 0
	addi $t0, $Zero, 8192
	jr $t0
