/*
 * FrameBuffer Image Display Function
 * (c) smoku/2000
 *
 */

/* Public Use Functions:
 *
 * extern void fb_display(unsigned char *rgbbuff,
 *     int x_size, int y_size,
 *     int x_pan, int y_pan,
 *     int x_offs, int y_offs);
 *
 * extern void getCurrentRes(int *x,int *y);
 *
 	通过/dev/fbns，应用程序可进行的针对帧缓冲设备的操作主要有如下几种。 
l  读/写dev/fbn：相当于读/写屏幕缓冲区。例如用 cp  /dev/fb0  tmp命令可将当
前屏幕的内容复制到一个文件中，而命令 cp  tmp  >  /dev/fb0 则将图形文件
tmp显示在屏幕上。 
l  映射操作：对于帧缓冲设备，可通过 mmap()映射操作将屏幕缓冲区的物理
地址映射到用户空间的一段虚拟地址中， 之后用户就可以通
过读/写这段虚拟地址访问屏幕缓冲区，在屏幕上绘图了。
而且若干个进程可以映射到同一个显示缓冲区。实际上，使
用帧缓冲设备的应用程序都是通过映射操作来显示图形的。  
l  I/O 控制：对于帧缓冲设备，对设备文件的 ioctl()操作可读
取/设置显示设备及屏幕的参数，如分辨率、显示颜色数、
屏幕大小等。 
	如图18.6所示，在应用程序中，操作/dev/fbn的一般步骤如下。 
（1）打开/dev/fbn设备文件。 
（2）用 ioctl()操作取得当前显示屏幕的参数，如屏幕分辨率、每
	个像素点的比特数和偏移。根据屏幕参数可计算屏幕缓冲区的大小。  
（3）将屏幕缓冲区映射到用户空间。 
（4） 映射后就可以直接读/写屏幕缓冲区， 进行绘图和图片显示了。

	此代码所示为一段用户空间访问帧缓冲设备显示缓冲区的范例， 包含打开
和关闭帧缓冲设备、得到和设置可变参数、得到固定参数、生成与BPP对应的
帧缓冲数据及填充显示缓冲区。 
*/

//#include "fb_display.h"

unsigned short red[256], green[256], blue[256];
struct fb_cmap map332 = {0, 256, red, green, blue, NULL};
unsigned short red_b[256], green_b[256], blue_b[256];
struct fb_cmap map_back = {0, 256, red_b, green_b, blue_b, NULL};


int openFB(const char *name);
void closeFB(int fh);
void getVarScreenInfo(int fh, struct fb_var_screeninfo *var);
void setVarScreenInfo(int fh, struct fb_var_screeninfo *var);
void getFixScreenInfo(int fh, struct fb_fix_screeninfo *fix);
void set332map(int fh);
void* convertRGB2FB(int fh, unsigned char *rgbbuff, unsigned long count, int bpp, int *cpp);
void blit2FB(int fh, void *fbbuff,
	unsigned int pic_xs, unsigned int pic_ys,
	unsigned int scr_xs, unsigned int scr_ys,
	unsigned int xp, unsigned int yp,
	unsigned int xoffs, unsigned int yoffs,
	int cpp);
 /*帧缓冲设备显示*/ 
void fb_display(unsigned char *rgbbuff, int x_size, int y_size, int x_pan, int y_pan, int x_offs, int y_offs)
{
    struct fb_var_screeninfo var;
    unsigned short *fbbuff = NULL;
    int fh = -1, bp = 0;
    
    /* 打开帧缓冲设备 */  /* get the framebuffer device handle */
    fh = openFB(NULL);
    
     /* 获得可变参数 *//* read current video mode */
    getVarScreenInfo(fh, &var);
    
      /*校正panning */ /* correct panning */
    if(x_pan > x_size - var.xres) x_pan = 0;
    if(y_pan > y_size - var.yres) y_pan = 0;
     /* 校正offset *//* correct offset */
    if(x_offs + x_size > var.xres) x_offs = 0;
    if(y_offs + y_size > var.yres) y_offs = 0;
    
     /* 将RGB数据转换为与var位域对应的数据并填充到显示缓冲区 *//* blit buffer 2 fb */
    fbbuff = convertRGB2FB(fh, rgbbuff, x_size * y_size, var.bits_per_pixel, &bp);
    blit2FB(fh, fbbuff, x_size, y_size, var.xres, var.yres, x_pan, y_pan, x_offs, y_offs, bp);
    free(fbbuff);
    
     /* 关闭帧缓冲设备 *//* close device */
    closeFB(fh);
}

void getCurrentRes(int *x, int *y)
{
    struct fb_var_screeninfo var;
    int fh = -1;
    fh = openFB(NULL);
    getVarScreenInfo(fh, &var);
    *x = var.xres;
    *y = var.yres;
    closeFB(fh);
}
 /*打开帧缓冲设备*/ 
int openFB(const char *name)
{
    int fh;
    char *dev;

    if(name == NULL){
	dev = getenv("FRAMEBUFFER");
	if(dev) name = dev;
	else name = DEFAULT_FRAMEBUFFER;
    }
    
    if ((fh = open(name, O_WRONLY)) == -1){
        fprintf(stderr, "open %s: %s\n", name, strerror(errno));
	exit(1);
    }
    return fh;
}
 /*关闭帧缓冲设备*/ 
void closeFB(int fh)
{
    close(fh);
}
 /*得到屏幕可变参数*/ 
void getVarScreenInfo(int fh, struct fb_var_screeninfo *var)
{
    if (ioctl(fh, FBIOGET_VSCREENINFO, var)){
        fprintf(stderr, "ioctl FBIOGET_VSCREENINFO: %s\n", strerror(errno));
	exit(1);
    }
}
 /*设置屏幕可变参数*/
void setVarScreenInfo(int fh, struct fb_var_screeninfo *var)
{
    if (ioctl(fh, FBIOPUT_VSCREENINFO, var)){
        fprintf(stderr, "ioctl FBIOPUT_VSCREENINFO: %s\n", strerror(errno));
	exit(1);
    }
}
 /*得到屏幕固定参数*/ 
void getFixScreenInfo(int fh, struct fb_fix_screeninfo *fix)
{
    if (ioctl(fh, FBIOGET_FSCREENINFO, fix)){
        fprintf(stderr, "ioctl FBIOGET_FSCREENINFO: %s\n", strerror(errno));
	exit(1);
    }
}
 /*构造颜色表*/ 
void make332map(struct fb_cmap *map)
{
	int rs, gs, bs, i;
	int r = 8, g = 8, b = 4;

	map->red = red;
	map->green = green;
	map->blue = blue;

	rs = 256 / (r - 1);
	gs = 256 / (g - 1);
	bs = 256 / (b - 1);
	
	for (i = 0; i < 256; i++) {
		map->red[i]   = (rs * ((i / (g * b)) % r)) * 255;
		map->green[i] = (gs * ((i / b) % g)) * 255;
		map->blue[i]  = (bs * ((i) % b)) * 255;
	}
}
 /*设置颜色表*/  
void set8map(int fh, struct fb_cmap *map)
{
    if (ioctl(fh, FBIOPUTCMAP, map) < 0) {
        fprintf(stderr, "Error putting colormap");
        exit(1);
    }
}
 /*获得颜色表*/ 
void get8map(int fh, struct fb_cmap *map)
{
    if (ioctl(fh, FBIOGETCMAP, map) < 0) {
        fprintf(stderr, "Error getting colormap");
        exit(1);
    }
}
/*构造并设置颜色表*/ 
void set332map(int fh)
{
    make332map(&map332);
    set8map(fh, &map332);
}
/*写显示缓冲区*/
void blit2FB(int fh, void *fbbuff,
	unsigned int pic_xs, unsigned int pic_ys,
	unsigned int scr_xs, unsigned int scr_ys,
	unsigned int xp, unsigned int yp,
	unsigned int xoffs, unsigned int yoffs,
	int cpp)
{
    int i, xc, yc;
    unsigned char *cp; unsigned short *sp; unsigned int *ip;
    cp = (unsigned char *) sp = (unsigned short *) ip = (unsigned int *) fbbuff;

    xc = (pic_xs > scr_xs) ? scr_xs : pic_xs;
    yc = (pic_ys > scr_ys) ? scr_ys : pic_ys;
    
    switch(cpp){
	case 1:
	    get8map(fh, &map_back);
	    set332map(fh);
	    for(i = 0; i < yc; i++){
		lseek(fh, ((i+yoffs)*scr_xs+xoffs)*cpp, SEEK_SET);
		write(fh, cp + (i+yp)*pic_xs+xp, xc*cpp);
	    }
	    set8map(fh, &map_back);
	    break;
	case 2:
	    for(i = 0; i < yc; i++){
		lseek(fh, ((i+yoffs)*scr_xs+xoffs)*cpp, SEEK_SET);
		write(fh, sp + (i+yp)*pic_xs+xp, xc*cpp);
	    }
	    break;
	case 4:
	    for(i = 0; i < yc; i++){
		lseek(fh, ((i+yoffs)*scr_xs+xoffs)*cpp, SEEK_SET);
		write(fh, ip + (i+yp)*pic_xs+xp, xc*cpp);
	    }
	    break;
    }
}

inline unsigned char make8color(unsigned char r, unsigned char g, unsigned char b)
{
    return (
	(((r >> 5) & 7) << 5) |
	(((g >> 5) & 7) << 2) |
	 ((b >> 6) & 3)       );
}

inline unsigned short make15color(unsigned char r, unsigned char g, unsigned char b)
{
    return (
	(((r >> 3) & 31) << 10) |
	(((g >> 3) & 31) << 5)  |
	 ((b >> 3) & 31)        );
}
/*组成BPP=16时的缓冲数据*/ 
inline unsigned short make16color(unsigned char r, unsigned char g, unsigned char b)
{
    return (
	(((r >> 3) & 31) << 11) |
	(((g >> 2) & 63) << 5)  |
	 ((b >> 3) & 31)        );
}
/*把RGB数据按照屏幕的BPP调整*/ 
void* convertRGB2FB(int fh, unsigned char *rgbbuff, unsigned long count, int bpp, int *cpp)
{
    unsigned long i;
    void *fbbuff = NULL;
    unsigned char *c_fbbuff;
    unsigned short *s_fbbuff;
    unsigned int *i_fbbuff;

    switch(bpp)
    {
	case 8:
	    *cpp = 1;
	    c_fbbuff = (unsigned char *) malloc(count * sizeof(unsigned char));
	    for(i = 0; i < count; i++)
		c_fbbuff[i] = make8color(rgbbuff[i*3], rgbbuff[i*3+1], rgbbuff[i*3+2]);
	    fbbuff = (void *) c_fbbuff;
	    break;
	case 15:
	    *cpp = 2;
	    s_fbbuff = (unsigned short *) malloc(count * sizeof(unsigned short));
	    for(i = 0; i < count ; i++)
		s_fbbuff[i] = make15color(rgbbuff[i*3], rgbbuff[i*3+1], rgbbuff[i*3+2]);
	    fbbuff = (void *) s_fbbuff;
	    break;
	case 16:
	    *cpp = 2;
	    s_fbbuff = (unsigned short *) malloc(count * sizeof(unsigned short));
	    for(i = 0; i < count ; i++)
		s_fbbuff[i] = make16color(rgbbuff[i*3], rgbbuff[i*3+1], rgbbuff[i*3+2]);
	    fbbuff = (void *) s_fbbuff;
	    break;
	case 24:
	case 32:
	    *cpp = 4;
	    i_fbbuff = (unsigned int *) malloc(count * sizeof(unsigned int));
	    for(i = 0; i < count ; i++)
		i_fbbuff[i] = ((rgbbuff[i*3] << 16) & 0xFF0000) |
			    ((rgbbuff[i*3+1] << 8) & 0xFF00) |
			    (rgbbuff[i*3+2] & 0xFF);
	    fbbuff = (void *) i_fbbuff;
	    break;
	default:
	    fprintf(stderr, "Unsupported video mode! You've got: %dbpp\n", bpp);
	    exit(1);
    }
    return fbbuff;
}

