#OSHW2 執行序
## build & run
	gcc oshw2.c -o oshw2 -lcurses -lncurses && ./oshw2
以下為相依性lib必須加在後面compile不然會死

	-lcurses
	-lncurses
	
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
	
	