marge insertion sort とは?
マージ挿入ソート

マージソート
ソート済みファイルとソート済みファイルを、互いの最小値同士を比較し新たなファイルを作成するソート

A:		12 45 90
B:		10 62 70
の場合

A:		12 45 90
B:		10 62 70
(10 < 12)

A:		12 45 90
B:		62 70
sorted:	10

A:		12 45 90
B:		62 70
(12 < 62)
sorted:	10 12

A:		45 90
B:		62 70
(45 < 62)
sorted:	10 12 45

A:		90
B:		62 70
(62 < 90)
sorted:	10 12 45 62

A:		90
B:		70
(70 < 90)
sorted:	10 12 45 62 70

A:		90
B:		
(90)
sorted:	10 12 45 62 70 90


マージ挿入ソート とは

n要素の場合に
  (i) [n/2] 個の別々の対に分けて、対ごとに比較を行う(n が奇数なら 1つ要素を残しておく)
 (ii) (i) で見つけた [n/2] 対の大きいほうの数をマージ挿入法でソートする (再帰的!)
(iii)