#OSHW2 執行序
## build & run
	gcc oshw2.c -o oshw2 -lcurses -lncurses && ./oshw2
以下為相依性lib必須加在後面compile不然會死

	-lcurses
	-lncurses
	
##特色
	1. responsive design
	2. 好玩
	3. 不會玩到破台
##Terminal
長必須為

	奇數
	
responsive做好囉！

可以拉來拉去

上上下下拉好蚌蚌

左左右會會死
##說明
player 1

	上 => w
	下 => s
	
player 2

	上 => i
	下 => k
	
規則

	打掛別人就好

得分

	1. 碰到對方牆壁
	2. 塞進對方球拍裡面會瘋狂得分
	
##預覽
![preview](1.png)

	
	