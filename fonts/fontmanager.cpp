#include "fontmanager.hpp"
#include <QDebug>
#include <QFontDatabase>

namespace {
QString g_inkFont;
}

void FontManager::loadFonts() {
  int fontId =
      QFontDatabase::addApplicationFont(":/fonts/resources/Clagista.ttf");
  if (fontId == -1) {
    qWarning() << "Failed to load handwriting font — falling back to default";
    g_inkFont = QString(); // empty means "use system default"
    return;
  }

  QStringList families = QFontDatabase::applicationFontFamilies(fontId);
  if (!families.isEmpty()) {
    g_inkFont = families.at(0);
  }
}

QString FontManager::inkFont() {
  return g_inkFont.isEmpty() ? "Arial" : g_inkFont; // safe fallback
}