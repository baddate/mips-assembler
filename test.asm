.data  00000000                    # 数据段定义开始 
buf: .word  0X000000FF 
.text
start:  addi   $t0, $Zero, 0
lw   $v0, buf ($t0)
addi  $t0, $t0, 4 
lw  $v1, buf($t0) 
add   $v0, $v0, $v1    
addi  $t0, $t0, 4  
sw     $v0, buf($t0)  
j   start
