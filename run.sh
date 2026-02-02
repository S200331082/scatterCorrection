#!/bin/bash

macros=("run1.mac" "run2.mac" "run3.mac" "run4.mac" "run5.mac" "run6.mac")

for macro in "${macros[@]}"
do
    echo "正在运行 $macro ..."
    ./exampleB1 $macro
    
    # 添加5秒延时
    sleep 10
    
done