#include "Editor.h"
#include "../external/raygui.h"

void Editor::Initializing() {
    //Loads font at startup
    std::string fontPath = std::string(GetApplicationDirectory()) + "fonts-styles/fonts/0xProtoNerdFont-Regular.ttf";
    font = LoadFontEx(fontPath.c_str(), config.fontSize, nullptr, 0);

    if (font.texture.id==0) {
        TraceLog(LOG_WARNING,"Failed to load custom font");
        font = GetFontDefault();
        config.textColor=BLACK;
        config.fontSize=20.0;
    }

    GuiSetStyle(DEFAULT,TEXT_SIZE,static_cast<int>(config.fontSize));
    GuiSetFont(font);

    config.gridWidth = MeasureTextEx(font, "A", config.fontSize, config.spacing).x;
    config.gridHeight = MeasureTextEx(font, "A", config.fontSize, config.spacing).y;

    ui.InitWindowFile();
}


void Editor::Update() {

    HandleLoadingFile();

    if (text.isFileLoaded && ui.focusedWindow == UIDraw::TextPanel) {
        HandleTyping();
        HandleNewLine();
        HandleBackspace();
        HandleTab();
        HandleCursorMovement();
    }
    HandleDebugMode();

    HandleSavingFile();
}

//Draws the frames
void Editor::DrawFrame() {
    BeginDrawing();
    ClearBackground(config.background);

    //Main UI, WIP(?)
    ui.DrawButtons();
    ui.DrawMenuSeparatorLine();

    ui.DrawFileTreePanel();
    ui.DrawFileTreeSeparatorLine();

    ui.DrawFileTabsPanel();
    ui.DrawFileTabs(config, text, font);

    ui.DrawCodePanel();
    // ui.DrawCursorPositionPanel();

    ui.DrawLineNumber(config,text,font);
    ui.DrawLineSeparator(config);
    ui.DrawFileText(config,text,font);
    ui.DrawCursor(config,text);
    ui.DrawCursorPosition(config,text,font);

    //UI for debugging
    ui.DrawDebugLines(config,text);
    ui.DrawDebugInfo(config,text);

    ui.DrawFilePanel(text);
    ui.DrawEditPanel(config, text, font);

    ui.DrawStartingText(config,text, font);

    ui.DrawWindowFileDialog(text);
    ui.DrawRenameFileWindow(config,text,font);


    EndDrawing();
}

//Unload resources
void Editor::UnloadResources() {
    UnloadFont(font);

}
