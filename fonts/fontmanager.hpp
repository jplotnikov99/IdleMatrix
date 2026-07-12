#pragma once

#include <QString>

namespace FontManager {
void loadFonts();  // call once, at startup
QString inkFont(); // usable anywhere afterward
} // namespace FontManager
