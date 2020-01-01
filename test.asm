.data 0x00
.text
	addi $t1, $Zero, 1
	add $t1, $Zero, $s1
delay:
	addi $t2, $Zero, 10
	add $t2, $Zero, $s2
	addi $t3, $Zero, 30000
	add $t3, $Zero, $s2
label0:
	addi $t4, $Zero, 0
	sub $t4, $s2, $t0
	bltz $t0, label1
	j label2
label1:
	addi $t5, $Zero, 1
	sub $s2, $t5, $t6
	add $t6, $Zero, $s2
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
	lw $fp,0($sp)
	lw $sp, 4($sp)
	jr $ra
