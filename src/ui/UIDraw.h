#pragma once

#include "raylib.h"
#include "../core/TextBuffer.h"
#include "../external/gui_window_file_dialog.h"

#include "../settings/config.h"

class UIDraw {
public:
    enum WindowFocus {
        TextPanel,
        RenameFileWindow
    };

    WindowFocus focusedWindow = TextPanel;
private:
    const Vector2 StarterAnchor = { 0, 0 };
    const Vector2 FileAnchor = { 8, 56 };
    const Vector2 EditAnchor = { 104, 56 };
    const Vector2 TBDAnchor = { 200, 56 };
    const Vector2 TabsAnchor = { 168, 64 };
    const Vector2 SeparatorLineAnchor = { 0, 96 };
    const Vector2 CodePanelAnchor = { 168, 96 };
    const Vector2 TreeFileAnchor = { 0, 64 };

    const Vector2 RenameFileAnchor = {500,200};

    Vector2 scroll = { 0.0,0.0 };
    Rectangle panelView = { 0 };

    char newFileName[512]={};

    bool fileButtonState = false;
    bool editButtonState = false;
    bool renameFileDialogState = false;
    bool TBDButtonState = false;

public:
    void DrawButtons();
    void DrawMenuSeparatorLine();

    void DrawFileTreePanel();
    void DrawFileTreeSeparatorLine();

    void DrawFileTabsPanel();
    void DrawFileTabs(EditorConfig& config, TextBuffer& text, Font font);

    void DrawCodePanel();
    // void DrawCursorPositionPanel();

    void DrawLineNumber(EditorConfig& config, TextBuffer& text, Font font);
    void DrawLineSeparator(EditorConfig& config);
    void DrawCursor(EditorConfig& config, TextBuffer& text);
    void DrawCursorPosition(EditorConfig& config, TextBuffer& text, Font font);

    void DrawDebugLines(EditorConfig& config, TextBuffer& text);
    void DrawDebugInfo(EditorConfig& config, TextBuffer& text);

    void DrawFilePanel(TextBuffer& text);
    void DrawEditPanel(EditorConfig& config,TextBuffer& text, Font font);
    void DrawRenameFileWindow(EditorConfig& config,TextBuffer& text, Font font);

    void InitWindowFile();
    void DrawWindowFileDialog(TextBuffer& text);

    void DrawFileText(EditorConfig& config, TextBuffer& text, Font font);
    GuiWindowFileDialogState fileDialogState;

    void DrawStartingText(EditorConfig& config, TextBuffer& text, Font font);
};
