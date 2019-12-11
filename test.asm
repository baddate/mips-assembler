
.text
start:
addi $t0, $t0, 8
addi $t0, $Zero, 0
add $v0, $v0, $v1
lw   $v0, buf($t0)
addi  $t0, $t0, 4 
sw   $v0, buf($t0)

.data
buf: .word 12