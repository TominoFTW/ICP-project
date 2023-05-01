#ifndef SQUAREGRID_H
#define SQUAREGRID_H

#include <QWidget>
#include <QPainter>
#include <vector>
#include "map_object.h"

class SquareGrid : public QWidget
{
    Q_OBJECT

public:
    SquareGrid(const std::vector<std::vector<MapObject>>& data, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::vector<std::vector<MapObject>> mData;
};

#endif // SQUAREGRID_H