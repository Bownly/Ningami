#ifndef RAM_H
#define RAM_H

#define RAM_ROOMID   0x00U
#define RAM_PLAYER   0x01U
#define RAM_DECK     0x10U
#define RAM_SIG_ADDR 0xF9U

extern UBYTE ram_data[];

void saveGameData();
void loadGameData();

#endif