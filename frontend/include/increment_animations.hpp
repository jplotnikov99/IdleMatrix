#pragma once

#include <QFont>
#include <QPointF>
#include <QtGlobal>
#include <vector>

struct PaintCharacter {
  int fontSize;
  qreal opacity;
  QString text;
  qreal x = 0, y = 0;
};

// This class is responsible for calculating the positions and properties of the characters
// it assumes a box of 200x100 for each character, and the center point is the center of the box
class IncrementScalar {
public:
  IncrementScalar(QPointF &center, qreal progress, int curNumber,
                  int newNumber);

  std::vector<PaintCharacter> characters;
  qreal spread = 80.0;

  ~IncrementScalar() = default;

private:
};