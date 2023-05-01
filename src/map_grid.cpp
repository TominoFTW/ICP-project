#include "map_grid.h"

SquareGrid::SquareGrid(const std::vector<std::vector<MapObject>>& data, QWidget *parent)
    : QWidget(parent)
    , mData(data)
{
    setFixedSize(800, 600);
}

void SquareGrid::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int size = qMin(width(), height()) / mData.size();

    for (size_t row = 0; row < mData.size(); ++row) {
        for (size_t col = 0; col < mData[row].size(); ++col) {
            if (!mData[row][col].is_static()) {
                continue;
            }
            QRect rect(col * size, row * size, size, size);
            painter.fillRect(rect, mData[row][col].getColor());
            painter.drawRect(rect);
        }
    }
}
