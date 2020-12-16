!#/bin/bash

for i in {1..9}
do
./subc -ast tiny_test_progs/tiny_0$i >> output/$i.txt
diff -s output/$i.txt tiny_test_progs/tiny_0$i.tree

done
for i in {10..25}
do
./subc -ast tiny_test_progs/tiny_$i >> output/$i.txt
diff -s output/$i.txt tiny_test_progs/tiny_$i.tree

done

