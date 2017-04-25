/* 
 * File:   display.h
 * Author: C16266
 *
 * Created on November 16, 2016, 2:19 PM
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum{
    DISPLAY_ENABLE_WAV = 0,
    DISPLAY_ENABLE_MP3,
    DISPLAY_ENABLE_AAC,
    DISPLAY_ENABLE_WMA,
    DISPLAY_ENABLE_OPUS,
    DISPLAY_ENABLE_ADPCM,
    DISPLAY_ENABLE_SPEEX,
    DISPLAY_TRACK_NAME,
    DISPLAY_ARTIST_NAME,
    DISPLAY_ALBUM_NAME,
    DISPLAY_TRACK_LENGTH,
    DISPLAY_PLAY_TIME,
    DISPLAY_SWITCH_SCREEN,
            
    
}DISPLAY_EVENT;

typedef struct{
    char album[64];
    char track[64];
    char artist[64];
    uint8_t screenID;
    uint32_t    track_length;
    uint32_t    playtime;
    
}APP_DISPLAY_DATA;

void APP_DisplayInit();
void APP_DisplayTasks();
void APP_UpdateDisplay(DISPLAY_EVENT de);
void APP_UpdateTrackName(const char *track);
void APP_UpdateArtistName(const char *data);
void APP_UpdateAlbumName(const char *data);
void APP_UpdateTrackLength(uint32_t data);
void APP_UpdatePlaytime(uint32_t data);
void APP_UpdateScreen(uint32_t data);
#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */

