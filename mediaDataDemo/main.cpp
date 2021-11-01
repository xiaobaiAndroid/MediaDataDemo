//
//  main.cpp
//  mediaDataDemo
//
//  Created by BZF on 2021/10/29.
//

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "simple_mediadata_raw.h"


int main(int argc, const char * argv[]) {
    
//    simples_yuv420_gray("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/Assets/lena_256x256_yuv420p.yuv", 256, 256, 1);
    
//    yuv444_split("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/Assets/lena_256x256_yuv444p.yuv", 256, 256, 1);
    
//    yuv420_gray("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/Assets/lena_256x256_yuv420p.yuv", 256, 256, 1);
    
//    yuv420_halfy("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/Assets/lena_256x256_yuv420p.yuv", 256, 256, 1);
    
//    yuv420_border("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/Assets/lena_256x256_yuv420p.yuv", 256, 256, 20,1);
    
//    yuv420_graybar(640, 360, 0, 255, 10, "/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/Assets/graybar_640x360.yuv");
    
//    yuv420_psnr("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/Assets/lena_256x256_yuv420p.yuv", "/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/Assets/lena_distort_256x256_yuv420p.yuv", 256, 256, 1);
    
    
//    rgb24_split("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/Assets/cie1931_500x500.rgb", 500, 500, 1);
    
//    rgb24_to_bmp("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/Assets/lena_256x256_rgb24.rgb", 256, 256, "/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/build/output_lena.bmp");
    
//    simplest_rgb24_to_yuv420("/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/Assets/lena_256x256_rgb24.rgb", 256, 256, 1, "/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/build/output_lena.yuv");
    
    simplest_rgb24_colorbar(640, 360, "/Users/bzf/Desktop/XcodeDemo/mediaDataDemo/mediaDataDemo/Assets/colorbar_640x360.rgb");
    
    return 0;
}


