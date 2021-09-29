from cyaron import IO
from cyaron import Compare
from cyaron import Sequence
from random import randint
import random

random.seed()
io = IO(file_prefix="test")
n = randint(1,10000000)
seq = Sequence(lambda i,f:randint(0,10000000)).get(0,n-1)

begin = randint(1,n // 2)
end = randint(n // 2,n)
seq[begin:end]=sorted(seq[begin:end])

io.input_writeln(n)
io.input_writeln(seq)
seq.sort()
io.output_write(seq)
