#include "gridlayouter.h"
#include <cmath>

GridLayouter::GridLayouter(QObject *parent)
    : AbstractLayouter(parent)
{
}

void GridLayouter::PlaceImages(const QVector<LayoutChar> &chars)
{
    int minY = INT_MAX;
    int maxW = 0;
    int maxH = 0;
    int maxEndY = INT_MIN;

    foreach (const LayoutChar& c, chars)
    {
        minY = std::min(minY, c.y);
        maxW = std::max(maxW, c.x + c.w);
        maxH = std::max(maxH, c.h);
        maxEndY = std::max(maxEndY, c.y+c.h);
    }
    //maxH -= minY;
    if (minY>0){
        printf("warning: wut\n");
    }
    maxH = std::abs(minY) - maxEndY*-1; 
    
    calculateSize(maxW, maxH, chars.size());

    int w = width();
    int h = height();

    int charsPerRow = chars.size()
            ? w / maxW
            : 0;
    int rows = charsPerRow
            ? (chars.size() + charsPerRow - 1) / charsPerRow
            : 0;

    resize(maxW * charsPerRow, maxH * rows);

    int row = 0;
    int col = 0;
    foreach (const LayoutChar& c, chars)
    {
        LayoutChar l = c;
        l.x += col * maxW;
        l.y += row * maxH - minY;
        place(l);

        if (++col >= charsPerRow)
        {
            col = 0;
            ++row;
        }
    }
}

void GridLayouter::calculateSize(int maxW, int maxH, size_t count)
{
    int area = maxW * maxH * count;

    int dim = ::sqrt(area);
    resize(dim,dim);
}

AbstractLayouter* GridLayouterFactoryFunc (QObject* parent) {
    return new GridLayouter(parent);
}
