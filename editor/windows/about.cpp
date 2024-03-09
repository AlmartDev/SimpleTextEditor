#include "about.h"

namespace editor {
    void About::show(bool* p_open) {
        if (!*p_open) return;
        ImGui::SetNextWindowSize(ImVec2(230, 100));
        ImGui::Begin("About", p_open);
        ImGui::Text("Simple Text Editor");
        ImGui::Text("Version 1.0");
        ImGui::Text("By: @AlmartDev");
        ImGui::End();
    }
}