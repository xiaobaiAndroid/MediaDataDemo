//
//  simple_mediadata_raw.h
//  mediaDataDemo
//
//  Created by BZF on 2021/10/29.
//

#ifndef simple_mediadata_raw_h
#define simple_mediadata_raw_h

int simples_yuv420_gray(char *url, int w, int h, int num);

int yuv444_split(char *url, int w, int h, int  num);


int yuv420_gray(char *url, int w, int h, int num);

int yuv420_halfy(char *url, int w, int h, int num);

int yuv420_border(char *url, int w, int h, int border, int num);

int yuv420_graybar(int width, int height, int ymin, int ymax, int barnum, char *url_out);

int yuv420_psnr(char *url1, char *url2, int w, int h, int num);

int rgb24_split(char *url, int w, int h, int num);

int rgb24_to_bmp(const char *rgb24path, int width, int height, const char *bmppath);


int simplest_rgb24_to_yuv420(char *url_in, int w, int h,int num,char *url_out);

int simplest_rgb24_colorbar(int width, int height,char *url_out);

#endif /* simple_mediadata_raw_h */
