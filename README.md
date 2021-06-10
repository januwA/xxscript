# xxscript

> ./x64/Release/xxscript.exe -i ./test.xxs -jit

> ./x64/Release/xxscript.exe -i ./test.xxs -print

## Number

```
1       i64 
1.2     f64 
```

## Bool
```
true  i1
false i1
```

## Function

```
function name(p1, p2) {
  return 1 + 1;
}

name(1,2)
```


## if
```
if() {

} else if() {

} else {

}
```

## for
```
for(;;) { }

for(i=0; i<10; ++i) { }

for(i=0; i<10; ++i) {
  if(i==5) break;
}

for(i=0; i<10; ++i) {
  if(i==5) continue;
}
```

## while
```
while(true) { break; }
```

## 编译命令
```
$ ./x64/Release/xxscript.exe -i test.xxs [options]
```

options:
 - -jit    执行代码
 - -ir     打印LLVM IR
 - -pass   开启函数优化
 - -parser 测试语法解析器