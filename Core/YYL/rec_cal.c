#include "rec_cal.h"


int ix1, iy1, ix2, iy2, ix3, iy3, ix4, iy4;

void calculate_inner_border(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int t) {
    // 计算方向向量
    float d1x = x2 - x1, d1y = y2 - y1;
    float d2x = x3 - x2, d2y = y3 - y2;
    float d3x = x4 - x3, d3y = y4 - y3;
    float d4x = x1 - x4, d4y = y1 - y4;

    // 计算向量长度
    float len1 = sqrt(d1x * d1x + d1y * d1y);
    float len2 = sqrt(d2x * d2x + d2y * d2y);
    float len3 = sqrt(d3x * d3x + d3y * d3y);
    float len4 = sqrt(d4x * d4x + d4y * d4y);

    // 计算单位法向量
    float n1x = -d1y / len1, n1y = d1x / len1;
    float n2x = -d2y / len2, n2y = d2x / len2;
    float n3x = -d3y / len3, n3y = d3x / len3;
    float n4x = -d4y / len4, n4y = d4x / len4;

    // 计算内边框顶点坐标
    ix1 = x1 + t * n1x;
    iy1 = y1 + t * n1y;
    ix2 = x2 + t * n2x;
    iy2 = y2 + t * n2y;
    ix3 = x3 + t * n3x;
    iy3 = y3 + t * n3y;
    ix4 = x4 + t * n4x;
    iy4 = y4 + t * n4y;
}
