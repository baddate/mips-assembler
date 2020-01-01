.data 0x00
.text
delay:
	addi $t2, $Zero, 10
	add $t2, $Zero, $s2
	addi $t3, $Zero, 30000
	add $t3, $Zero, $s2
label0:
	addi $t4, $Zero, 0
	sub $t4, $s2, $t0
	bltz $t0, label1
	j label1
label1:
	addi $t5, $Zero, 1
	sub $s2, $t5, $t6
	add $t6, $Zero, $s2
	j label0


