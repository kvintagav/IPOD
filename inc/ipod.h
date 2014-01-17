

#ifndef __IPOD_H
#define __IPOD_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define DY_SLEEP 0x45
#define DY_HOME 0x46
#define DY_MODE 0xE7
#define DY_CLOCK  0x44
#define DY_SEL  0x40
#define DY_EQ 0x43
#define DY_BACK 0x07
#define DY_NEXT 0x15
#define DY_START 0x09
#define DY_DOWN 0x16
#define DY_UP 0x19
#define DY_0 0x0D
#define DY_1 0x0C
#define DY_2 0x18
#define DY_3 0x5E
#define DY_4 0x08
#define DY_5 0x1C
#define DY_6 0x5A
#define DY_7 0x42
#define DY_8 0x52
#define DY_9 0x4A

#define HEADER1 0xFF
#define HEADER2 0x55
#define LENGTH_INDEX 2
#define MODE_INDEX 3
#define COMMAND_INDEX 4

#define WIDHT  120
#define WIDHT_PICT  128

#define HEIGHT 64

#define COLOR 0x01


void  GET_MODE(void) ;
void SWITCH_4(void);
void SWITCH_2(void);

void CHANGE_MODE(void);

void BUTTON_RELEASE(void);
void PLAY_PAUSE (void);
void VOL_UP (void);
void VOL_DOWN (void);
void SKIP_FORWARD (void);
void SKIP_BACK (void);
void NEXT_ALBUM (void);
void PREV_ALBUM (void);
void STOP_PLAY (void);
void PLAY (void);
void PAUSE (void);
void TOGGLE_MUTE (void);
void NEXT_PLAYLIST(void);
void PREV_PLAYLIST (void);
void TOGGLE_SHUFFLE(void);
void TOGGLE_REPEAT(void);
void IPOD_OFF (void);
void IPOD_ON(void);
void MENU_BUTTON (void);
void CENTER_BUTTON (void);
void SCROLL_CCW (void);
void SCROLL_CW(void);


void  GET_IPOD_TYPE(void);
void GET_POD_TYPE(void);
void GET_POD_NAME(void);
void GO_2_LIB(void);
void SWITCH_ITEM(void);
void GET_COUNT_TYPE(void);
void GET_NAMES_RANGE(void);
void GET_TIME_STATUS(void);
void GET_POS_PL(void);
void GET_TITLE_SONG(void);
void GET_ARTIST_SONG(void);
void GET_ALBUM_SONG(void);
void POLLING_MODE(void);
void START_PL_SONG(void);
void PLAY_BACK(void);
void GET_SHUF_MODE(void);
void SET_SHUF_MODE(void);
void GET_REP_MODE(void);
void SET_REP_MODE(void);
void UPLOAD_PIC (void);
void GET_MAX_SCREEN(void);
void GET_NUM_SONG_PL(void);
void JUMP_SONG_PL(void);


char getCheckSum(void);
void sendmsg( char cmd[]);
void ipod_init(void);
void command_ipod(uint8_t BYTE);
void filling_line(char *byte, int number,int line);
void send_image(int number);
void resp_ipod(void);
#endif /* __MAIN_H */
