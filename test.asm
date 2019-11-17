.data  0x100000 					# 数据段定义开始
BUF: .word  0X000000FF, 0X55005500
.text
start:  addi   $t0, $Zero, 0                 
lw   $v0, buf ($t0)           
addi  $t0, $t0, 4 
lw  $v1, buf($t0) 
add   $v0, $v0, $v1    
addi  $t0, $t0, 4  
sw     $v0, buf($t0)  
j   start
