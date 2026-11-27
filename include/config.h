#ifndef CONFIG_H
#define CONFIG_H

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720

#define TILESIZE 40

// With screen set to 1280x720, and Tilesize set to 40. This should result in 32 col 18 row. 32 * 18 = 576 worldGrid tiles
#define MAX_COLS (SCREENWIDTH / TILESIZE)
#define MAX_ROWS (SCREENHEIGHT / TILESIZE)

#endif