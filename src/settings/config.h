#pragma once

#include "raylib.h"

class EditorConfig {
public:

    bool debugLines;
    bool debugInfo;

    int windowPadding;
    int verticalLineSpacing;

    float gridWidth{};
    float gridHeight{};

    float fontSize;
    float spacing;

    Color textColor{};
    Color background{};

    EditorConfig() {

        debugLines=false;
        debugInfo=false;

        windowPadding=20;

        verticalLineSpacing=5;
        spacing=0;
        fontSize=30;

        textColor=WHITE;
        background={46,53,61,0};
    }
};