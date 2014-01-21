
#include "ipod.h"

#include "platform_config.h"
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char uart_rx_buf_ipod[lenght_usart]; 

char M0_GET_MODE[4]=  {0x04,0x00,0x01,0x03};
char M0_SWITCH_4[4]=  {0x04,0x00,0x01,0x04};
char changeMode[4]=  {0x04,0x00,0x01,0x00};
char M0_SWITCH_2[4]=  {0x04,0x00,0x01,0x02};

char M4_RX_FEEDBACK[4]=       {0x04,0x04,0x00,0x01};
char M4_TX_GET_POD_TYPE[4]=   {0x04,0x04,0x00,0x12};
char M4_RX_GET_POD_TYPE[4]=   {0x04,0x04,0x00,0x13};
char M4_TX_GET_POD_NAME[4]=   {0x04,0x04,0x00,0x14};
char M4_RX_GET_POD_NAME[4]=   {0x04,0x04,0x00,0x15};
char M4_TX_GO_2_LIB[4]=       {0x04,0x04,0x00,0x16};
char M4_TX_SWITCH_ITEM[4]=    {0x04,0x04,0x00,0x17};
char M4_TX_GET_COUNT_TYPE[4]= {0x04,0x04,0x00,0x18};
char M4_RX_GET_COUNT_TYPE[4]= {0x04,0x04,0x00,0x19};
char M4_TX_GET_NAMES_RANGE[4]={0x04,0x04,0x00,0x1a};
char M4_RX_GET_NAMES_RANGE[4]={0x04,0x04,0x00,0x1b};
char M4_TX_GET_TIME_STATUS[4]={0x04,0x04,0x00,0x1c};
char M4_RX_GET_TIME_STATUS[4]={0x04,0x04,0x00,0x1d};
char M4_TX_GET_POS_PL[4]=     {0x04,0x04,0x00,0x1e};
char M4_RX_GET_POS_PL[4]=     {0x04,0x04,0x00,0x1f};
char M4_TX_GET_TITLE_SONG[4]= {0x04,0x04,0x00,0x20};
char M4_RX_GET_TITLE_SONG[4]= {0x04,0x04,0x00,0x21};
char M4_TX_GET_ARTIST_SONG[4]={0x04,0x04,0x00,0x22};
char M4_RX_GET_ARTIST_SONG[4]={0x04,0x04,0x00,0x23};
char M4_TX_GET_ALBUM_SONG[4]= {0x04,0x04,0x00,0x24};
char M4_RX_GET_ALBUM_SONG[4]= {0x04,0x04,0x00,0x25};
char M4_TX_POLLING_MODE[4]=   {0x04,0x04,0x00,0x26};
char M4_RX_POLLING_MODE[4]=   {0x04,0x04,0x00,0x27};
char M4_TX_START_PL_SONG[4]=  {0x04,0x04,0x00,0x28};
char M4_TX_PLAY_BACK[4]=      {0x04,0x04,0x00,0x29};
char M4_TX_GET_SHUF_MODE[4]=  {0x04,0x04,0x00,0x2c};
char M4_RX_GET_SHUF_MODE[4]=  {0x04,0x04,0x00,0x2d};
char M4_TX_SET_SHUF_MODE[4]=  {0x04,0x04,0x00,0x2e};
char M4_TX_GET_REP_MODE[4]=   {0x04,0x04,0x00,0x2f};
char M4_RX_GET_REP_MODE[4]=   {0x04,0x04,0x00,0x30};
char M4_TX_SET_REP_MODE[4]=   {0x04,0x04,0x00,0x31};
char M4_TX_UPLOAD_PIC[4]=     {0x04,0x04,0x00,0x32};
char M4_TX_GET_MAX_SCREEN[4]= {0x04,0x04,0x00,0x33};
char M4_RX_GET_MAX_SCREEN[4]= {0x04,0x04,0x00,0x34};
char M4_TX_GET_NUM_SONG_PL[4]={0x04,0x04,0x00,0x35};
char M4_RX_GET_NUM_SONG_PL[4]={0x04,0x04,0x00,0x36};
char M4_TX_JUMP_SONG_PL[4]=   {0x04,0x04,0x00,0x37};


char M2_BUTTON_RELEASE[4]=  {0x04,0x02,0x00,0x00};                    //
char M2_PLAY_PAUSE[4]=      {0x04,0x02,0x00,0x01};                    //a
char M2_VOL_UP[4]=          {0x04,0x02,0x00,0x02};                    //b
char M2_VOL_DOWN[4]=        {0x04,0x02,0x00,0x04};                    //c
char M2_SKIP_FORWARD[4]=    {0x04,0x02,0x00,0x08};                    //d
char M2_SKIP_BACK[4]=       {0x04,0x02,0x00,0x10};                    //e
char M2_NEXT_ALBUM[4]=      {0x04,0x02,0x00,0x20};                    //f
char M2_PREV_ALBUM[4]=      {0x04,0x02,0x00,0x40};                    //g
char M2_STOP_PLAY[4]=       {0x04,0x02,0x00,0x80};                    //h
char M2_PLAY[5]=            {0x05,0x02,0x00,0x00,0x01};               //i
char M2_PAUSE[5]=           {0x05,0x02,0x00,0x00,0x02};               //j
char M2_TOGGLE_MUTE[5]=     {0x05,0x02,0x00,0x00,0x04};               //k
char M2_NEXT_PLAYLIST[5]=   {0x05,0x02,0x00,0x00,0x20};               //l
char M2_PREV_PLAYLIST[5]=   {0x05,0x02,0x00,0x00,0x40};               //m
char M2_TOGGLE_SHUFFLE[5]=  {0x05,0x02,0x00,0x00,0x80};               //n
char M2_TOGGLE_REPEAT[6]=   {0x06,0x02,0x00,0x00,0x00,0x01};          //o
char M2_IPOD_OFF[6]=        {0x06,0x02,0x00,0x00,0x00,0x04};          //p
char M2_IPOD_ON[6]=         {0x06,0x02,0x00,0x00,0x00,0x08};          //q
char M2_MENU_BUTTON[6]=     {0x06,0x02,0x00,0x00,0x00,0x40};          //r
char M2_CENTER_BUTTON[6]=   {0x06,0x02,0x00,0x00,0x00,0x80};          //s
char M2_SCROLL_CCW[7]=      {0x07,0x02,0x00,0x00,0x00,0x00,0x01};     //t
char M2_SCROLL_CW[7]=       {0x07,0x02,0x00,0x00,0x00,0x00,0x02};     //u

void  GET_MODE(void) {sendmsg(M0_GET_MODE);};
void SWITCH_4(void) {sendmsg(M0_SWITCH_4);};
void SWITCH_2(void) {sendmsg(M0_SWITCH_2);};
void CHANGE_MODE(void) {sendmsg(changeMode);};

void BUTTON_RELEASE(void){sendmsg(M2_BUTTON_RELEASE);};
void PLAY_PAUSE (void){sendmsg(M2_PLAY_PAUSE);};
void VOL_UP (void){sendmsg(M2_VOL_UP);};
void VOL_DOWN (void){sendmsg(M2_VOL_DOWN);};
void SKIP_FORWARD (void){sendmsg(M2_SKIP_FORWARD);};
void SKIP_BACK (void){sendmsg(M2_SKIP_BACK);};
void NEXT_ALBUM (void){sendmsg(M2_NEXT_ALBUM);};
void PREV_ALBUM (void){sendmsg(M2_PREV_ALBUM);};
void STOP_PLAY (void){sendmsg(M2_STOP_PLAY);};
void PLAY (void){sendmsg(M2_PLAY);};
void PAUSE (void){sendmsg(M2_PAUSE);};
void TOGGLE_MUTE (void){sendmsg(M2_TOGGLE_MUTE);};
void NEXT_PLAYLIST(void){ sendmsg(M2_NEXT_PLAYLIST);};
void PREV_PLAYLIST (void){sendmsg(M2_PREV_PLAYLIST);};
void TOGGLE_SHUFFLE(void){ sendmsg(M2_TOGGLE_SHUFFLE);};
void TOGGLE_REPEAT(void){ sendmsg(M2_TOGGLE_REPEAT);};
void IPOD_OFF (void){sendmsg(M2_IPOD_OFF);};
void IPOD_ON(void){ sendmsg(M2_IPOD_ON);};
void MENU_BUTTON (void){sendmsg(M2_MENU_BUTTON);};
void CENTER_BUTTON (void){sendmsg(M2_CENTER_BUTTON);};
void SCROLL_CCW (void){sendmsg(M2_SCROLL_CCW);};
void SCROLL_CW(void){ sendmsg(M2_SCROLL_CW);};



void  GET_IPOD_TYPE(void){sendmsg(M4_TX_GET_POD_TYPE);};
void GET_POD_TYPE(void){sendmsg( M4_TX_GET_POD_TYPE);};
void GET_POD_NAME(void){sendmsg( M4_TX_GET_POD_NAME);};
void GO_2_LIB(void){sendmsg( M4_TX_GO_2_LIB);};
void SWITCH_ITEM(void){sendmsg( M4_TX_SWITCH_ITEM);};
void GET_COUNT_TYPE(void){sendmsg( M4_TX_GET_COUNT_TYPE);};
void GET_NAMES_RANGE(void){sendmsg( M4_TX_GET_NAMES_RANGE);};
void GET_TIME_STATUS(void){sendmsg( M4_TX_GET_TIME_STATUS);};
void GET_POS_PL(void){sendmsg( M4_TX_GET_POS_PL);};
void GET_TITLE_SONG(void){sendmsg( M4_TX_GET_TITLE_SONG);};
void GET_ARTIST_SONG(void){sendmsg( M4_TX_GET_ARTIST_SONG);};
void GET_ALBUM_SONG(void){sendmsg( M4_TX_GET_ALBUM_SONG);};
void POLLING_MODE(void){sendmsg( M4_TX_POLLING_MODE);};
void START_PL_SONG(void){sendmsg( M4_TX_START_PL_SONG);};
void PLAY_BACK(void){sendmsg( M4_TX_PLAY_BACK);};
void GET_SHUF_MODE(void){sendmsg( M4_TX_GET_SHUF_MODE);};
void SET_SHUF_MODE(void){sendmsg( M4_TX_SET_SHUF_MODE);};
void GET_REP_MODE(void){sendmsg( M4_TX_GET_REP_MODE);};
void SET_REP_MODE(void){sendmsg( M4_TX_SET_REP_MODE);};
void UPLOAD_PIC (void){sendmsg( M4_TX_UPLOAD_PIC);};
void GET_MAX_SCREEN(void){sendmsg( M4_TX_GET_MAX_SCREEN);};
void GET_NUM_SONG_PL(void){sendmsg( M4_TX_GET_NUM_SONG_PL);};
void JUMP_SONG_PL(void){sendmsg( M4_TX_JUMP_SONG_PL);};


char txBuffer[265]=    {0xff,0x55};


//ipod command setup
//   0    |    1   |   2    |    3   |    4   |    5   |   6    |   7    
// header | header | length |  mode  |command |command | param  |checksum
//  0xff  |  0x55  | 0-255  |   0-5  | 2bytes for most |        | 0x100-((L+M+C+P) &0xff)

void filling_line(char *byte, int number,int line)
{
	int i; 
	for(i=0;i<=((WIDHT_PICT/4)*3-1);i++)
	{
		if (line==0) byte[15+i]=0x55;
		else  byte[6+i]=0x55;
	}
}

void send_image(int number)
{
		int i,lenght;
		char buf_apload_pic[255];
		
		memset(buf_apload_pic, 0,buf_apload_pic[0] ); //clear bufer
		
		
  	buf_apload_pic[0]=(WIDHT_PICT/4)*3+15;  //lenght all bufer
		buf_apload_pic[1]=M4_TX_UPLOAD_PIC[1];  
		buf_apload_pic[2]=M4_TX_UPLOAD_PIC[2];
		buf_apload_pic[3]=M4_TX_UPLOAD_PIC[3];
		buf_apload_pic[5]=0x00;               //number line
		buf_apload_pic[6]=COLOR;							//color 0x01
		buf_apload_pic[8]=WIDHT;							
		buf_apload_pic[10]=HEIGHT;
		buf_apload_pic[14]=(WIDHT_PICT/4);		//widht  multiple 8
		
		filling_line(buf_apload_pic,number,0);	//full bufer pixel information 
		
//		UPLOAD_PIC();
	sendmsg(buf_apload_pic);		//sen command on ipod
		
		for(i=1;i<=(HEIGHT/3-1);i++)
		{
			delay(3000000); 	
			memset(buf_apload_pic, 0,buf_apload_pic[0] ); 
			buf_apload_pic[0]=(WIDHT_PICT/4)*3+6;
			buf_apload_pic[1]=M4_TX_UPLOAD_PIC[1];
			buf_apload_pic[2]=M4_TX_UPLOAD_PIC[2];
			buf_apload_pic[3]=M4_TX_UPLOAD_PIC[3];
			
			
			filling_line(buf_apload_pic,number,i);
			buf_apload_pic[5]=i;
	//		UPLOAD_PIC();
			sendmsg(buf_apload_pic);
		}
		
		
}



void command_ipod(uint8_t BYTE)
{
	switch(BYTE)
		{	
			case '1' : BUTTON_RELEASE();
				send_str(UART_EXT,"BUTTON_RELEASE \r");
			break;
			case '2' : PLAY_PAUSE ();
			send_str(UART_EXT,"PLAY_PAUSE \r");
			break;
			case '3' :  VOL_UP ();
			send_str(UART_EXT,"VOL_UP \r");
			break;
			case '4' :VOL_DOWN ();
			send_str(UART_EXT,"VOL_DOWN \r");
			break;
			case '5' : SKIP_FORWARD ();
			send_str(UART_EXT,"SKIP_FORWARD \r");
			break;
			case '6' :  SKIP_BACK ();
			send_str(UART_EXT,"SKIP_BACK \r");
			break;
			case '7' :  NEXT_ALBUM ();
			send_str(UART_EXT,"NEXT_ALBUM \r");
			break;
			case '8' : PREV_ALBUM ();
			send_str(UART_EXT,"PREV_ALBUM \r");
			break;
			case '9' : STOP_PLAY ();
			send_str(UART_EXT,"STOP_PLAY \r");
			break;
			case '0' : PLAY ();
			send_str(UART_EXT,"PLAY \r");
			break;
			case 'w' : PAUSE ();
			send_str(UART_EXT,"PAUSE \r");
			break;
			case 'e' : TOGGLE_MUTE ();
			send_str(UART_EXT,"TOGGLE_MUTE \r");
			break;
			case 'r' : NEXT_PLAYLIST();
			send_str(UART_EXT,"NEXT_PLAYLIST \r");
			break;
			case 't' : PREV_PLAYLIST ();
			send_str(UART_EXT,"PREV_PLAYLIST \r");
			break;
			case 'y' : TOGGLE_SHUFFLE();
			send_str(UART_EXT,"TOGGLE_SHUFFLE \r");
			break;
			case 'u' : TOGGLE_REPEAT();
			send_str(UART_EXT,"TOGGLE_REPEAT \r");
			break;
			case 'i' : IPOD_OFF ();
			send_str(UART_EXT,"IPOD_OFF \r");
			break;
			case 'o': IPOD_ON();
			send_str(UART_EXT,"IPOD_ON \r");
			break;
			case 'p' : MENU_BUTTON ();
			send_str(UART_EXT,"MENU_BUTTON \r");
			break;
			case 'a' :  CENTER_BUTTON (); 
			send_str(UART_EXT,"CENTER_BUTTON \r");
			break;
			case 's' :  SCROLL_CCW (); 
			send_str(UART_EXT,"SCROLL_CCW \r");
			break;
			case 'd' :  SCROLL_CW(); 
			send_str(UART_EXT,"SCROLL_CW \r");
			break;
			
			default:
			break;
			

		 }
		send_str(UART_EXT,"\nipod> ");
	
}

void resp_ipod(void)
{
	
}

void sendmsg(char cmd[]){
	int i;
  // because MODE is included as the first byte of our commands,
  // we only need to add one more for the checksum
  // DONT FORGET WE NEED TO ADD THE PARAM IF YOU WANNA ADD MODE 4 SUPPORT
  txBuffer[LENGTH_INDEX]=(cmd[0]-1);
  txBuffer[MODE_INDEX]=cmd[1];
  
  // copy the command (starting at the 3rd byte) in to the tx buffer (starting at the 5th byte)
  for(i=0;i< (cmd[0]-2); i++)
    txBuffer[COMMAND_INDEX+i]=cmd[2+i];
    
  txBuffer[LENGTH_INDEX + txBuffer[LENGTH_INDEX] + 1] = getCheckSum();

  for( i=0; i< (LENGTH_INDEX + txBuffer[LENGTH_INDEX] + 2) ; i++){
    
   
		send_to_uart(UART_IPOD,txBuffer[i]);
    }
  
 
}

char getCheckSum(){
	int i;
  char checkSum=0;
  //
  for( i=LENGTH_INDEX; i< LENGTH_INDEX + txBuffer[LENGTH_INDEX] +1; i++ ){
    checkSum=checkSum+txBuffer[i];   
  }
  return 0x100 - (checkSum & 0xff);
}

