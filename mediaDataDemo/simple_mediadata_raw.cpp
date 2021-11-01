//
//  simple_mediadata_raw.cpp
//  mediaDataDemo
//
//  Created by BZF on 2021/10/29.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>


//分离YUV420P像素数据中的Y、U、V分量
//@param num 要处理的帧数
int simples_yuv420_gray(char *url, int w, int h, int num){
    FILE *fp;
    if((fp = fopen(url, "rb+")) == NULL){
        printf("Fail to open file!\n");
        exit(0);
    }
    FILE *fp1 = fopen("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/build/output_420_y.y", "wb+");
    FILE *fp2 = fopen("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/build/output_420_u.y", "wb+");
    FILE *fp3 = fopen("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/build/output_420_v.y", "wb+");
    
    const int size = w*h*3/2;
    unsigned char *pic = (unsigned char *)malloc(size);

    for(int i=0; i<num; i++){
        fread(pic, 1, size, fp);

        fwrite(pic, 1, w*h, fp1);
        fwrite(pic+w*h, 1, w*h/4, fp2);
        fwrite(pic+w*h*5/4, 1, w*h/4, fp3);
    }
    free(pic);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    return 0;
    
}


//分离YUV444P像素数据中的Y、U、V分量
int yuv444_split(char *url, int w, int h, int  num){
    FILE *fp;
    if((fp = fopen(url, "rb+")) == NULL){
        printf("Fail to open file!\n");
        exit(0);
    }
    FILE *fp1 = fopen("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/build/output_444_y.y", "wb+");
    FILE *fp2 = fopen("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/build/output_444_u.y", "wb+");
    FILE *fp3 = fopen("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/build/output_444_v.y", "wb+");
    unsigned char *pic = (unsigned char *)malloc(w*h*3);
    
    for(int i=0; i<num; i++){
        fread(pic, 1, w*h*3, fp);
        fwrite(pic, 1, w*h, fp1);
        fwrite(pic+w*h, 1, w*h, fp2);
        fwrite(pic+w*h*2, 1, w*h, fp3);
    }
    free(pic);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    return 0;
}

//将YUV420P格式像素数据的彩色去掉，编程灰度图
int yuv420_gray(char *url, int w, int h, int num){
    FILE *fp;
    if((fp = fopen(url, "rb+")) == NULL){
        printf("Fail to open file!\n");
        exit(0);
    }
    FILE *fp1 = fopen("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/build/output_gray.yuv", "wb+");
    unsigned char *pic = (unsigned char *)malloc(w*h*3/2);
    for(int i=0; i<num; i++){
        fread(pic,1,w*h*3/2,fp);
        
        //将指定内存的前n个字节设置为特定的值
        memset(pic+w*h, 128, w*h/2);
        fwrite(pic, 1, w*h*3/2, fp1);
    }
    free(pic);
    fclose(fp);
    fclose(fp1);
    
    return 0;
}


//将YUV420P像素数据的亮度减半
int yuv420_halfy(char *url, int w, int h, int num){
    FILE *fp;
    if((fp = fopen(url, "rb+")) == NULL){
        printf("Fail to open file!\n");
        exit(0);
    }
    FILE *fp1 = fopen("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/build/output_half.yuv", "wb+");
    
    const int size = w*h*3/2;
    
    unsigned char *pic=(unsigned char *)malloc(size);
    
    for(int i=0; i<num; i++){
        fread(pic, 1, size, fp);
        
        for(int j=0; j<w*h; j++){
            unsigned char temp = pic[j]/2;
            pic[j] = temp;
        }
        fwrite(pic, 1,size, fp1);
    }
    free(pic);
    fclose(fp);
    fclose(fp1);
    return 0;
}


//将YUV420P像素数据的周围加上边框
int yuv420_border(char *url, int w, int h, int border, int num){
    FILE *fp;
    if((fp = fopen(url, "rb+")) == NULL){
        printf("Fail to open file!\n");
        exit(0);
    }
    FILE *fp1 = fopen("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/build/output_border.yuv", "wb+");
    
    const int size = w*h*3/2;
    unsigned char *pic = (unsigned char *)malloc(size);
    
    for(int i=0; i<num; i++){
        fread(pic, 1, size, fp);
        
        for (int j=0; j<h; j++) {
            for(int k=0; k<w; k++){
                //判断是否在四个边界像素值-10外，是就提高Y的亮度为255
                if(k<border || k>(w-border) || j<border || j>(h-border)){
                    pic[j*w+k]=255;
                }
            }
        }
        fwrite(pic, 1, size, fp1);
    }
    free(pic);
    fclose(fp);
    fclose(fp1);
    return 0;
}


//生成YUV420P格式的灰阶测试图
//@param ymin 亮度最小值
//@param ymax 亮度最大值
//@param barnum 每一个灰度条中像素的亮度分量Y的取值
int yuv420_graybar(int width, int height, int ymin, int ymax, int barnum, char *url_out){
    //灰度条的宽度
    int barwidth;
    //亮度的增长量
    float lum_inc;
    //临时的亮度值（即Y的值）
    unsigned char lum_temp;
    int uv_width,uv_height;
    FILE *fp=NULL;
    unsigned char *data_y = NULL;
    unsigned char *data_u = NULL;
    unsigned char *data_v = NULL;
    int t=0,i=0,j=0;

//    根据图像的宽度width和图像的高度height以及灰阶数量barnum确定每一个灰度条的宽度
    barwidth = width/barnum;
    //总的亮度/数量
    lum_inc = ((float)(ymax-ymin))/(float)(barnum - 1);
    uv_width = width/2;
    uv_height = height/2;

    data_y = (unsigned char *)malloc(width*height);
    data_u = (unsigned char *)malloc(uv_width*uv_height);
    data_v = (unsigned char *)malloc(uv_width*uv_height);

    if((fp = fopen(url_out, "wb+")) == NULL){
        printf("Error: Cannot create file!\n");
        return -1;
    }
    printf("Y、U、V从图片的左到右");
    for (t=0; t<barnum; t++) {
        lum_temp = ymin + (char)(t*lum_inc);
        printf("%3d, 128, 128\n", lum_temp);
    }

    //计算灰阶数据
    for(j=0; j<height; j++){
        for(i=0; i<width; i++){
            t = i/barwidth;
            lum_temp = ymin + (char)(t*lum_inc);
            data_y[j*width+i] = lum_temp;
        }
    }

    for (j=0; j<uv_height; j++) {
        for (i=0; i<uv_width; i++) {
            data_u[j*uv_width+i]=128;
        }
    }
    for (j=0; j<uv_height; j++) {
        for (i=0; i<uv_width; i++) {
            data_v[j*uv_width+i]=128;
        }
    }

    fwrite(data_y, width*height, 1, fp);
    fwrite(data_u, uv_width*uv_height, 1, fp);
    fwrite(data_v, uv_width*uv_height, 1, fp);
    fclose(fp);
    free(data_y);
    free(data_u);
    free(data_v);
    
    return 0;
}

//计算两个YUV420P像素数据的PSNR
//PSNR通常用于质量评价，就是计算受损图像与原始图像之间的差别，以此来评价受损图像的质量
//PSNR取值通常情况下都在20-50的范围内，取值越高，代表两张图像越接近，反映出受损图像质量越好。
//param url1 原始YUV图片
//param num 要处理的帧数
int yuv420_psnr(char *url1, char *url2, int w, int h, int num){
    FILE *fp1 = fopen(url1, "rb+");
    FILE *fp2 = fopen(url2, "rb+");
    
    unsigned char *pic1 = (unsigned char *)malloc(w*h);
    unsigned char *pic2 = (unsigned char *)malloc(w*h);
    
    for (int i=0; i<num; i++) {
        fread(pic1, 1, w*h, fp1);
        fread(pic2, 1, w*h, fp2);
        
        double mse_num=0,mse=0,psnr=0;
        for (int j=0; j<w*h; j++) {
            mse_num += pow((double)(pic1[j]-pic2[j]), 2);
        }
        mse = mse_num/(w*h);
        psnr = 10*log10(255.0*255.0/mse);
        printf("%5.3f\n",psnr);
        
        fseek(fp1, w*h/2, SEEK_CUR);
        fseek(fp2, w*h/2, SEEK_CUR);

    }
    
    return 0;
    
}


//分离RGB24像素数据中的R、G、B分量
int rgb24_split(char *url, int w, int h, int num){
    FILE *fp;
    if((fp = fopen(url, "rb+")) == NULL){
        printf("Fail to open file\n");
        return -1;
    }
    
    FILE *fp1 = fopen("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/build/out_put_r.y", "wb+");
    FILE *fp2 = fopen("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/build/out_put_g.y", "wb+");
    FILE *fp3 = fopen("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/build/out_put_b.y", "wb+");
    
    const int size = w*h*3;
    unsigned char *pic = (unsigned char *)malloc(size);
    
    for (int i=0; i<num; i++) {
        fread(pic, 1, size, fp);
        
        for (int j=0; j<size; j=j+3) {
            fwrite(pic+j, 1, 1, fp1);
            fwrite(pic+j+1, 1, 1, fp2);
            fwrite(pic+j+2, 1, 1, fp3);
        }
    }
    free(pic);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    
    return 0;
}

//将RGB24格式像素数据封装为BMP图像
//BMP的存储方向是从左到右、从下到上的顺序
int rgb24_to_bmp(const char *rgb24path, int width, int height, const char *bmppath){
    typedef struct {
        int imageSize;
        int blank;
        int startPosition;
    }BmpHead;
    
    typedef struct {
        int biSize; //信息头的大小
        int biWidth; //以像素为单位图像的宽度
        //4字节，以像素为单位图像的高度，同时如果为正，说明位图倒立（即数据表示从图像的左下角到右上角），如果为负说明正向；
        int biHeight;
        //为目标设备说明颜色平面数，总被设置为1；
        unsigned short biPlanes;
        //2个字节，颜色深度，每个象素所需要的位数
        unsigned short biBitCount;
        //4个字节，图像的压缩类型，最常用的就是0(BI_RGB)，表示不压缩
        int biCompression;
        //4字节，说明位图数据的大小，当用BI_RGB格式时，可以设置为0
        int biSizeImages;
        //水平方向分辨率
        int biXPelsPerMeter;
        int biYPelsPerMeter;
        //4字节,位图实际使用的颜色表中的颜色数，为0时说明使用所有；
        int biClrUsed;
        //对图像显示有重要影响的颜色索引数，为0说明都重要；
        int biClrImportant;
        
    }InfoHead;
    
    int i=0,j=0;
    BmpHead mBmpHeader = {0};
    InfoHead mInfoHeader = {0};
    char bfType[2]={'B','M'};
    int head_size = sizeof(bfType) + sizeof(BmpHead)+sizeof(InfoHead);
    unsigned char *rgb24_buffer = NULL;
    FILE *fp_rgb24 = NULL, *fp_bmp=NULL;
    
    if((fp_rgb24 = fopen(rgb24path, "rb")) == NULL){
        printf("Fail to open RGB24 file!\n");
        return -1;
    }
    if((fp_bmp = fopen(bmppath, "wb")) == NULL){
        printf("Error: Cannot open output BMP file!\n");
        return -1;
    }
    
    const int size = width*height*3;
    rgb24_buffer = (unsigned char *)malloc(size);
    fread(rgb24_buffer, 1, size, fp_rgb24);
    
    mBmpHeader.imageSize = size + head_size;
    mBmpHeader.startPosition = head_size;
    
    mInfoHeader.biSize = sizeof(InfoHead);
    mInfoHeader.biWidth = width;
    mInfoHeader.biHeight = -height;
    mInfoHeader.biPlanes = 1;
    mInfoHeader.biBitCount = 24;
    mInfoHeader.biSizeImages = size;
    
    
    fwrite(bfType, 1, sizeof(bfType), fp_bmp);
    fwrite(&mBmpHeader, 1, sizeof(mBmpHeader), fp_bmp);
    fwrite(&mInfoHeader, 1, sizeof(mInfoHeader), fp_bmp);
    
    for(j =0;j<height;j++){
            for(i=0;i<width;i++){
                char temp=rgb24_buffer[(j*width+i)*3+2];
                rgb24_buffer[(j*width+i)*3+2]=rgb24_buffer[(j*width+i)*3+0];
                rgb24_buffer[(j*width+i)*3+0]=temp;
            }
        }
 
    fwrite(rgb24_buffer, size, 1, fp_bmp);
    fclose(fp_rgb24);
    fclose(fp_bmp);
    free(rgb24_buffer);
    
    return 0;
    
}


unsigned char clip_value(unsigned char x,unsigned char min_val,unsigned char  max_val){
    if(x>max_val){
        return max_val;
    }else if(x<min_val){
        return min_val;
    }else{
        return x;
    }
}
 
//RGB to YUV420
bool RGB24_TO_YUV420(unsigned char *RgbBuf,int w,int h,unsigned char *yuvBuf)
{
    unsigned char*ptrY, *ptrU, *ptrV, *ptrRGB;
    memset(yuvBuf,0,w*h*3/2);
    ptrY = yuvBuf;
    ptrU = yuvBuf + w*h;
    ptrV = ptrU + (w*h*1/4);
    unsigned char y, u, v, r, g, b;
    for (int j = 0; j<h;j++){
        ptrRGB = RgbBuf + w*j*3 ;
        for (int i = 0;i<w;i++){
            
            r = *(ptrRGB++);
            g = *(ptrRGB++);
            b = *(ptrRGB++);
            y = (unsigned char)( ( 66 * r + 129 * g +  25 * b + 128) >> 8) + 16  ;
            u = (unsigned char)( ( -38 * r -  74 * g + 112 * b + 128) >> 8) + 128 ;
            v = (unsigned char)( ( 112 * r -  94 * g -  18 * b + 128) >> 8) + 128 ;
            *(ptrY++) = clip_value(y,0,255);
            if (j%2==0&&i%2 ==0){
                *(ptrU++) =clip_value(u,0,255);
            }
            else{
                if (i%2==0){
                *(ptrV++) =clip_value(v,0,255);
                }
            }
        }
    }
    return true;
}
 
/**
 * 将RGB24格式像素数据转换为YUV420P格式像素数据
 * @param url_in  Location of Input RGB file.
 * @param w       Width of Input RGB file.
 * @param h       Height of Input RGB file.
 * @param num     Number of frames to process.
 * @param url_out Location of Output YUV file.
 */
int simplest_rgb24_to_yuv420(char *url_in, int w, int h,int num,char *url_out){
    FILE *fp=fopen(url_in,"rb+");
    FILE *fp1=fopen(url_out,"wb+");
 
    unsigned char *pic_rgb24=(unsigned char *)malloc(w*h*3);
    unsigned char *pic_yuv420=(unsigned char *)malloc(w*h*3/2);
 
    for(int i=0;i<num;i++){
        fread(pic_rgb24,1,w*h*3,fp);
        RGB24_TO_YUV420(pic_rgb24,w,h,pic_yuv420);
        fwrite(pic_yuv420,1,w*h*3/2,fp1);
    }
 
    free(pic_rgb24);
    free(pic_yuv420);
    fclose(fp);
    fclose(fp1);
 
    return 0;
}


/**
 * 生成RGB24格式的彩条测试图
 * @param width    Width of Output RGB file.
 * @param height   Height of Output RGB file.
 * @param url_out  Location of Output RGB file.
 */
int simplest_rgb24_colorbar(int width, int height,char *url_out){
 
    unsigned char *data=NULL;
    int barwidth;
    char filename[100]={0};
    FILE *fp=NULL;
    int i=0,j=0;
 
    data=(unsigned char *)malloc(width*height*3);
    barwidth=width/8;
 
    if((fp=fopen(url_out,"wb+"))==NULL){
        printf("Error: Cannot create file!");
        return -1;
    }
 
    for(j=0;j<height;j++){
        for(i=0;i<width;i++){
            int barnum=i/barwidth;
            switch(barnum){
            case 0:{
                data[(j*width+i)*3+0]=255;
                data[(j*width+i)*3+1]=255;
                data[(j*width+i)*3+2]=255;
                break;
                   }
            case 1:{
                data[(j*width+i)*3+0]=255;
                data[(j*width+i)*3+1]=255;
                data[(j*width+i)*3+2]=0;
                break;
                   }
            case 2:{
                data[(j*width+i)*3+0]=0;
                data[(j*width+i)*3+1]=255;
                data[(j*width+i)*3+2]=255;
                break;
                   }
            case 3:{
                data[(j*width+i)*3+0]=0;
                data[(j*width+i)*3+1]=255;
                data[(j*width+i)*3+2]=0;
                break;
                   }
            case 4:{
                data[(j*width+i)*3+0]=255;
                data[(j*width+i)*3+1]=0;
                data[(j*width+i)*3+2]=255;
                break;
                   }
            case 5:{
                data[(j*width+i)*3+0]=255;
                data[(j*width+i)*3+1]=0;
                data[(j*width+i)*3+2]=0;
                break;
                   }
            case 6:{
                data[(j*width+i)*3+0]=0;
                data[(j*width+i)*3+1]=0;
                data[(j*width+i)*3+2]=255;
 
                break;
                   }
            case 7:{
                data[(j*width+i)*3+0]=0;
                data[(j*width+i)*3+1]=0;
                data[(j*width+i)*3+2]=0;
                break;
                   }
            }
 
        }
    }
    fwrite(data,width*height*3,1,fp);
    fclose(fp);
    free(data);
 
    return 0;
}
