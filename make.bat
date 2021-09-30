
C:\gbdk2020\bin\lcc -Wa-l -c -o bordertiles.o tiles/borderTiles.c
C:\gbdk2020\bin\lcc -Wa-l -c -o cardtiles.o tiles/cardTiles.c
C:\gbdk2020\bin\lcc -Wa-l -c -o cursortiles.o tiles/cursorTiles.c
C:\gbdk2020\bin\lcc -Wa-l -c -o fonttiles.o tiles/fontTiles.c
C:\gbdk2020\bin\lcc -Wa-l -c -o icontiles.o tiles/iconTiles.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo1 -c -o enemyDogTiles.o tiles/enemyDogTiles.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo1 -c -o enemyKameTiles.o tiles/enemyKameTiles.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo1 -c -o enemyKitsuneTiles.o tiles/enemyKitsuneTiles.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo1 -c -o enemyNinja1tiles.o tiles/enemyNinja1Tiles.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo1 -c -o enemyNinja2tiles.o tiles/enemyNinja2Tiles.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo1 -c -o enemyTanukitiles.o tiles/enemyTanukiTiles.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo1 -c -o enemyToriTiles.o tiles/enemyToriTiles.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo1 -c -o glintTiles.o tiles/glintTiles.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo1 -c -o healAnimTiles.o tiles/healAnimTiles.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo1 -c -o manaAnimTiles.o tiles/manaAnimTiles.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo1 -c -o shieldAnimTiles.o tiles/shieldAnimTiles.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo2 -c -o foresttiles.o tiles/forestTiles.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo2 -c -o forestmetatiles.o tiles/forestMetaTiles.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo3 -c -o titlecardtiles.o tiles/titlecardTiles.c

C:\gbdk2020\bin\png2mtspr sprites/player.png -sh 16 -sw 16 -pw 0 -ph 0 -spr8x8 -b 2

C:\gbdk2020\bin\lcc -Wa-l -c -o common.o common.c
C:\gbdk2020\bin\lcc -Wa-l -c -o fade.o fade.c

C:\gbdk2020\bin\lcc -Wa-l -Wf-bo1 -c -o battleState.o states/battleState.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo2 -c -o overworldState.o states/overworldState.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo3 -c -o pausemenuState.o states/pausemenuState.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo3 -c -o mainmenuState.o states/mainmenuState.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo4 -c -o dialogState.o states/dialogState.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo5 -c -o shopState.o states/shopState.c

C:\gbdk2020\bin\lcc -Wa-l -c -o cardDescStrings.o maps/cardDescStrings.c
C:\gbdk2020\bin\lcc -Wa-l -c -o cardMaps.o maps/cardMaps.c
C:\gbdk2020\bin\lcc -Wa-l -c -o textWindowMap.o maps/textWindowMap.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo1 -c -o battleAnimMaps.o maps/battleAnimMaps.c

C:\gbdk2020\bin\lcc -Wa-l -c -o CardData.o database/CardData.c
C:\gbdk2020\bin\lcc -Wa-l -c -o DeckObject.o objects/DeckObject.c
C:\gbdk2020\bin\lcc -Wa-l -c -o EnemyObject.o objects/EnemyObject.c

C:\gbdk2020\bin\lcc -Wa-l -Wf-bo2 -c -o RoomData.o database/RoomData.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo4 -c -o StringData.o database/StringData.c
C:\gbdk2020\bin\lcc -Wa-l -Wf-bo5 -c -o ShopData.o database/ShopData.c

c:\gbdk2020\bin\lcc -Wa-l -Wf-ba0 -c -o ram.o ram.c
C:\gbdk2020\bin\lcc -Wa-l -c -o main.o main.c  
C:\gbdk2020\bin\lcc -Wl-yt3 -Wl-yo8 -Wl-ya4 -o Ningami.gb *.o sprites/*.c

REM pause
del *.o
del *.lst
del *.asm
del *.sym

@REM Bank info
@REM 0: main, common, music logic etc
@REM 1: battleState
@REM 2: overworldState
@REM 3: title stuff; pause menu stuff
@REM 4: dialog stuff
@REM 5: shop stuff
