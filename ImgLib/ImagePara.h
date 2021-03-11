#pragma once

// 灰度级别
const int GRAY_LEVEL = 256;
// 8色灰度级别
const int GRAY_LEVEL_8 = 8;
// 256灰度级别　
const int GRAY_LEVEL_256 = 256;


const int IMAGE_TYPE_BIT_32 = 32;
//  24位颜色图像
const int IMAGE_TYPE_BIT_24 = 24;
// 8位图像
const int IMAGE_TYPE_BIT_8 = 8;
// 1位图像
const int IMAGE_TYPE_BIT_1 = 1;

// 图像类型(24位彩色图像、256色彩色图像、256灰度图像、1位颜色图像)
enum IMAGE_TYPE { COLOR_32_BIT, COLOR_24_BIT, COLOR_8_BIT, GRAY_8_BIT, GRAY_1_BIT, UNKNOWN_IMAGE_TYPE };

// 空间变换参数的矩阵长度
const int SPACE_SWITCH_PARA_LENGTH = 9;

// PI
const double PI = 3.1415926535;
