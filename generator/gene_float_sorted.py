from cyaron import IO
from cyaron import Compare
from cyaron import Sequence
from random import randint
from random import uniform
import random
random.seed()
io = IO(file_prefix="test")
n = randint(1,10000000)
seq = Sequence(lambda i,f:uniform(0,1000)).get(0,n-1)
seq.sort()
io.input_writeln(n)
io.input_writeln(seq)
io.output_write(seq)
