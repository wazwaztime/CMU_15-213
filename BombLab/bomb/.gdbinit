set args psol.txt

#b phase_1
#b phase_2
#b phase_3
#b phase_4
#b phase_5
#b phase_6

#通过阅读asm文件我们可以发现phase_defused是个很阴险的跳到secret_phase的函数
#在解决完前面的问题前我们不用考虑它

#b phase_defused
#command
#    return
#end

b secret_phase

#为了防止炸弹爆炸，直接跳过
b explode_bomb
command
    return
end

r