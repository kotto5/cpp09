#!/bin/bash

while true; do
    # コマンドを実行し、終了ステータスを取得
    ./PmergeMe `jot -r 100000 1 100000 | tr '\n' ' '`

    # 終了ステータスが0でない場合、ループを終了
    if [ $? -ne 0 ]; then
        break
    fi
done
