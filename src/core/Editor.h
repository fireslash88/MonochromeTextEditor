#pragma once

#include "../settings/config.h"
#include "TextBuffer.h"
#include "raylib.h"
#include "../ui/UIDraw.h"

class Editor {

    EditorConfig config;

    TextBuffer text;

    Font font = {};

    UIDraw ui;

public:
    void Initializing();
    void Update();
    void DrawFrame();
    void UnloadResources();

private:
    // This is used to declare the controls of the editor.
    // Defined in EditorControls.cpp

    void HandleTyping();
    void HandleNewLine();
    void HandleBackspace();
    void HandleTab();
    void HandleCursorMovement();

    void HandleDebugMode();

    void HandleLoadingFile();
    void HandleSavingFile();

};