#pragma once

#include <imgui.h>

namespace editor {
    class About {
        public:
            void show(bool* p_open);
            bool showAbout;
    };
}