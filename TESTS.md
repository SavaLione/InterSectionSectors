
#### Тесты проводятся на VM 2x3.80GHz (intel)

```
  1   original    gcc   188
  2   original    gcc   183
  3   original    gcc   182
  4   original    gcc   180
  5   original    g++   182
  6   original    g++   176   -O0
  7   original    g++   183   -O1
  8   original    g++   182   -O2
  9   original    g++   186   -O3
  
 10   optimized   g++   178   -O2
 11   optimized   g++   194   -O2     (remove cout)
 12   optimized   g++   190   -O0
```

```
[Original]
(b7f4126)
Для исходных данных
  50 минут
Для 50000 строк
  CoI === 17
  
  real  3m9,808s
  user  2m11,114s
  sys   3m8,330s
```

```
[original]
CoI === 16

real    5m18,770s
user    2m13,216s
sys     3m3,377s
```

```
[original]
CoI === 19

real    5m15,422s
user    2m11,292s
sys     3m2,111s
```

```
[original]
CoI === 15

real    5m14,642s
user    2m11,692s
sys     3m0,958s
```

```
[original]
[g++]
CoI === 17

real    5m42,390s
user    2m38,013s
sys     3m2,258s
```

```
[original]
[g++ -O0]
CoI === 17

real    5m33,246s
user    2m34,722s
sys     2m56,677s
```

```
[original]
[g++ -O1]
CoI === 18

real    4m0
user    0m55
sys     3m3
```

```
[original]
[g++ -O2]
CoI === 18

real    3m57
user    0m52
sys     3m2
```

```
[original]
[g++ -O3]
CoI === 18

real    4m1
user    0m53
sys     3m6
```

```
[optimized]
(3d38eb1)
[10]
[g++ -O2]
CoI === 18

real    3m52
user    0m52
sys     2m58
```

```
[optimized]
(f5e4a95)
[11]
[g++ -O2 (remove cout)]
CoI === 18

real    4m8
user    0m52
sys     3m14
```

```
[optimized]
[12]
[g++ -O0]
CoI === 16

real    5m51
user    2m38
sys     3m10
```
