#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "datastructures.hpp"

class UpgradeButtonWidget : public QWidget {
  Q_OBJECT
public:
  explicit UpgradeButtonWidget(const QString &displayName, QWidget *parent = nullptr);

  void updateData(const UpgradeData &data);

signals:
  void clicked();

protected:
  void mousePressEvent(QMouseEvent *event) override;
  void enterEvent(QEnterEvent *event) override;
  void leaveEvent(QEvent *event) override;

private:
  QLabel *m_nameLabel;
  QLabel *m_valueLabel;
  QLabel *m_costLabel;
  QLabel *m_levelLabel;

  void applyStyle(bool hovered);
};
