#pragma once

/**
 * @brief ApplyVignetting 添加暗角
 *
 * @param channelY 8BitYUV图片的Y通道起始地址
 * @param width 宽
 * @param height 高
 * @param startPos 暗角起点离中点的距离百分比，有效范围 0~1。
 * @param endStrength 暗角终止强度，有效范围 0~1。（1为最暗，0为最亮）
 * @return int 0为正确，其他为错误。
 */
int ApplyVignetting(unsigned char* channelY, const int width, const int height, const float startPos,
                    const float endStrength);
