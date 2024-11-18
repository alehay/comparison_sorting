# comparison_sorting
Sorting comparison is my homework assignment for the university


```
make build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release .
cmake --build .

./test_sort --width=1000  --height=1000 -i --rndMin=0 --rndMax=700000

```


example result 
```
./test_sort --width=1000  --height=1000 -i --rndMin=0 --rndMax=700000
name is introsort libstdc++; elapsed mks is 35
name is heap_sort_int; elapsed mks is 58
name is insertion_sort_int; elapsed mks is 132
name is quickSort_int; elapsed mks is 42
name is selection_sort_int; elapsed mks is 290
name is shell_sort_int; elapsed mks is 53
name is radix_sort_intt; elapsed mks is 14
name is PDQD SORT INT; elapsed mks is 24
```