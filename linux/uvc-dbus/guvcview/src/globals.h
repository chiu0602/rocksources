/*******************************************************************************#
#           guvcview              http://guvcview.berlios.de                    #
#                                                                               #
#           Paulo Assis <pj.assis@gmail.com>                                    #
#                                                                               #
# This program is free software; you can redistribute it and/or modify          #
# it under the terms of the GNU General Public License as published by          #
# the Free Software Foundation; either version 2 of the License, or             #
# (at your option) any later version.                                           #
#                                                                               #
# This program is distributed in the hope that it will be useful,               #
# but WITHOUT ANY WARRANTY; without even the implied warranty of                #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 #
# GNU General Public License for more details.                                  #
#                                                                               #
# You should have received a copy of the GNU General Public License             #
# along with this program; if not, write to the Free Software                   #
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA     #
#                                                                               #
********************************************************************************/

#ifndef GLOBALS_H
#define GLOBALS_H

#include <glib.h>
#include <gtk/gtk.h>
#include "defs.h"
#include "utils.h"

typedef struct _VidBuff
{
	gboolean used;
	QWORD time_stamp;
	BYTE *frame;
	int bytes_used;
} VidBuff;

// 0-"jpg", 1-"bmp", 2-"png" (see create_image.c)
typedef enum {
    IMG_FORMAT_JPG = 0,
    IMG_FORMAT_BMP,
    IMG_FORMAT_PNG,
    IMG_FORMAT_RAW
} IMG_FORMAT;

/*global variables used in guvcview*/
struct GLOBAL
{
	__MUTEX_TYPE    mutex;         //global structure mutex
	__COND_TYPE     IO_cond;      //IO thread semaphore

	VidBuff *videoBuff;    //video Buffer

	char *videodevice;     // video device (def. /dev/video0)
	char *confPath;        //configuration file path
	char *vidfile;         //video filename passed through argument options with -n
	char *WVcaption;       //video preview title bar caption
	char *imageinc_str;    //label for File inc
	char *vidinc_str;      //label for File inc
	char *mode;            //mjpg (default)
	pchar* vidFPath;       //video path [0] - filename  [1] - dir
	pchar* imgFPath;       //image path [0] - filename  [1] - dir

	BYTE *jpeg;            // jpeg buffer

//	ULONG AVI_MAX_LEN;     //avi max length
	DWORD snd_begintime;   //begin time for audio capture
	DWORD currtime;
	DWORD lasttime;
	UINT64 Vidstarttime;    //video start time
	UINT64 Vidstoptime;     //video stop time
	QWORD v_ts;            //video time stamp
	QWORD a_ts;            //audio time stamp
	DWORD vid_inc;         //video name increment
	DWORD framecount;      //video frame count
	DWORD frmCount;        //frame count for fps display calc
	DWORD image_inc;       //image name increment

	int stack_size;        //thread stack size
	int vid_sleep;         //video thread sleep time (0 by default)
	int cap_meth;          //capture method: 1-mmap 2-read
	int Capture_time;      //video capture time passed through argument options with -t
	IMG_FORMAT imgFormat;  //image format
	int VidCodec;          //0-"MJPG"  1-"YUY2" 2-"DIB "(rgb32) 3-....
	int VidFormat;         //0-AVI 1-MKV ....
	//int Sound_API;         //audio API: 0-PORTAUDIO 1-PULSEAUDIO
	int PanStep;           //step angle for Pan
	int TiltStep;          //step angle for Tilt
	int FpsCount;          //frames counter for fps calc
	int timer_id;          //fps count timer
	int image_timer_id;    //auto image capture timer
	int disk_timer_id;     //timer id for disk check (free space)
	int image_timer;       //auto image capture time
	int image_npics;       //number of captures
	int fps;               //fps denominator
	int fps_num;           //fps numerator (usually 1)
	int bpp;               //current bytes per pixel
	int hwaccel;           //use hardware acceleration
	int width;             //frame width
	int height;            //frame height
	int winwidth;          //control windoe width
	int winheight;         //control window height
	int boxvsize;          //size of vertical spliter
	int spinbehave;        //spin: 0-non editable 1-editable
	int format;            //v4l2 pixel format
	int Frame_Flags;       //frame filter flags
	int skip_n;            //initial frames to skip
	int w_ind;             //write frame index
	int r_ind;             //read  frame index

	float DispFps;         //fps value

	gboolean no_display;   //display on window or not.
//	gboolean Sound_enable; //Enable/disable Sound (Def. enable)
	gboolean AFcontrol;    //Autofocus control flag (exists or not)
	gboolean autofocus;    //autofocus flag (enable/disable)
	gboolean flg_config;   //flag confPath if set in args
	gboolean flg_npics;    //flag npics if set in args
	gboolean flg_hwaccel;  //flag hwaccel if set in args
	gboolean flg_res;      //flag resol if set in args
	gboolean flg_mode;     //flag mode if set in args
	gboolean flg_imgFPath; //flag imgFPath if set in args
	gboolean flg_FpsCount; //flag FpsCount if set in args
	gboolean flg_cap_meth; //flag if cap_meth is set in args
	gboolean debug;        //debug mode flag (--verbose)
	gboolean control_only; //if set don't stream video (enables image control in other apps e.g. ekiga, skype, mplayer)
	gboolean change_res;   //flag for reseting resolution
	gboolean add_ctrls;    //flag for exiting after adding extension controls

    struct {
        gint x;
        gint y;
        gint width;
        gint height;
        gint depth;
    } geometry;
    GdkWindow *inner_window;
    GdkWindow *foreign_window;
};

/*----------------------------- prototypes ------------------------------------*/
int initGlobals(struct GLOBAL *global);

int closeGlobals(struct GLOBAL *global);

#endif

