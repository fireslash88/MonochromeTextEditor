#include "UIDraw.h"
#include "../external/raygui.h"
#include "raylib.h"

#define GUI_WINDOW_FILE_DIALOG_IMPLEMENTATION
#include "../external/gui_window_file_dialog.h"

void UIDraw::DrawButtons() {
    if (GuiButton(Rectangle{ FileAnchor.x + 0, FileAnchor.y + -32, 80, 24 }, "File")) {
        if (editButtonState) {
            editButtonState=false;
        }
        fileButtonState=!fileButtonState;
    }
    if (GuiButton(Rectangle{ EditAnchor.x + 0, EditAnchor.y + -32, 80, 24 }, "Edit")) {
        if (fileButtonState) {
            fileButtonState=false;
        }
        editButtonState=!editButtonState;
    }
    GuiButton(Rectangle{ TBDAnchor.x + 0, TBDAnchor.y + -32, 80, 24 }, "TBD");

    // GuiButton((Rectangle){ 1456, 32, 24, 24 }, "#193#");
    // GuiButton((Rectangle){ 1488, 32, 24, 24 }, "#191#");
}

void UIDraw::DrawMenuSeparatorLine() {
    GuiLine(Rectangle{ TabsAnchor.x + 0, TabsAnchor.y + -8, static_cast<float>(GetScreenWidth()), 16 }, NULL);
}

void UIDraw::DrawFileTreePanel() {
    GuiPanel(Rectangle{ TreeFileAnchor.x + 0, TreeFileAnchor.y + 0, 169, static_cast<float>(GetScreenHeight()) },NULL);
}

void UIDraw::DrawFileTreeSeparatorLine() {
    GuiLine(Rectangle{ SeparatorLineAnchor.x + 0, SeparatorLineAnchor.y + -8, 168, 16 }, NULL);
}

void UIDraw::DrawFileTabsPanel() {
    GuiPanel(Rectangle{ TabsAnchor.x + 0, TabsAnchor.y + 0, static_cast<float>(GetScreenWidth()), 33 }, NULL);
}

void UIDraw::DrawFileTabs(EditorConfig& config, TextBuffer& text, Font font) {
    int scrollTab=0;
    int active=0;
    float dynamicWidth = MeasureTextEx(font,fileDialogState.fileNameText,config.fontSize,config.spacing).x;
    GuiTabBar({TabsAnchor.x+8,TabsAnchor.y+4,100,24},fileDialogState.fileNameText,&scrollTab,&active);
}

void UIDraw::DrawCodePanel() {
    GuiPanel(Rectangle{ CodePanelAnchor.x + 0, CodePanelAnchor.y + 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) }, NULL);
}

// void UIDraw::DrawCursorPositionPanel() {
//     GuiPanel((Rectangle){ StarterAnchor.x + static_cast<float>(GetScreenWidth()-240), StarterAnchor.y + static_cast<float>(GetScreenHeight()-48), 240, 48 }, NULL);
// }

void UIDraw::DrawLineNumber(EditorConfig& config, TextBuffer& text, Font font) {

    Rectangle DrawLineRec = {CodePanelAnchor.x,CodePanelAnchor.y,(float)config.gridWidth*6, GetScreenHeight()-CodePanelAnchor.y};

    BeginScissorMode(DrawLineRec.x, DrawLineRec.y,DrawLineRec.width,DrawLineRec.height);

    for (std::size_t i = 0; i < text.GetLineCounter(); i++) {
        float posX = CodePanelAnchor.x + config.gridWidth * 5; //*6
        float posY = CodePanelAnchor.y + i * (config.verticalLineSpacing+config.gridHeight) + scroll.y;

        std::string lineText = std::to_string(i + 1);

        Vector2 size = MeasureTextEx(font, lineText.c_str(), config.fontSize, config.spacing);

        DrawTextEx(font, lineText.c_str(), {posX - size.x, posY}, config.fontSize, config.spacing, config.textColor);
    }

    EndScissorMode();
}

void UIDraw::DrawLineSeparator(EditorConfig& config) {
    DrawLine(CodePanelAnchor.x + config.gridWidth * 6, CodePanelAnchor.y, CodePanelAnchor.x + config.gridWidth * 6,
             GetScreenHeight(),LIGHTGRAY);
}

void UIDraw::DrawCursor(EditorConfig& config, TextBuffer& text) {
    Color cursorColor = {
        47,129,247,120
    };

    BeginScissorMode(panelView.x,panelView.y,panelView.width,panelView.height);

    DrawRectangle(
        text.GetCursorColumn() * config.gridWidth + CodePanelAnchor.x + config.gridWidth*6 + scroll.x,
        text.GetCursorLine() * config.gridHeight + text.GetCursorLine()*config.verticalLineSpacing+CodePanelAnchor.y + scroll.y,
        config.gridWidth, config.gridHeight, cursorColor
        );

    EndScissorMode();
}

void UIDraw::DrawCursorPosition(EditorConfig& config, TextBuffer& text, Font font) {
    DrawTextEx(font,TextFormat("%zu:%zu",text.GetCursorLine()+1,text.GetCursorColumn()+1),{
        TreeFileAnchor.x+60,
        GetScreenHeight()- TreeFileAnchor.y+30},
        30,
        0,
        WHITE);
}

void UIDraw::DrawFilePanel(TextBuffer& text) {
    if (fileButtonState) {
        GuiPanel({FileAnchor.x,FileAnchor.y+5,150,110},NULL);
        if (GuiButton({FileAnchor.x+5,FileAnchor.y+10,140,30},"Open file")) {
            fileDialogState.windowActive=true;
        }
        if (GuiButton({FileAnchor.x+5,FileAnchor.y+15 + 30,140,30},"Save file")) {
            if (text.isFileLoaded) {
                text.SaveToFile(text.filePath);
            }
        }
        // GuiButton({FileAnchor.x+5,FileAnchor.y+20 + 60,140,30},"Save as..");
    }
}

void UIDraw::DrawEditPanel(EditorConfig& config,TextBuffer& text, Font font) {
    if (editButtonState) {
        GuiPanel({EditAnchor.x,EditAnchor.y+5,150,110},NULL);
        if (GuiButton({EditAnchor.x+5,EditAnchor.y+10,140,30},"Rename file")) {
            if (text.isFileLoaded) {
                renameFileDialogState=!renameFileDialogState;
                focusedWindow = RenameFileWindow;

                strcpy( newFileName,fileDialogState.fileNameText);

            }else {
                TraceLog(LOG_WARNING,TextFormat("File hasn't loaded yet!"));
            }
        }
        GuiButton({EditAnchor.x+5,EditAnchor.y+15 + 30,140,30},"Copy");
        GuiButton({EditAnchor.x+5,EditAnchor.y+20 + 60,140,30},"Paste");
    }
}

void UIDraw::DrawRenameFileWindow(EditorConfig &config, TextBuffer &text, Font font) {

    if (renameFileDialogState) {
        GuiWindowBox({RenameFileAnchor.x,RenameFileAnchor.y,500,200},"Rename File");

        DrawTextEx(font,"How do you want to rename the file?",{RenameFileAnchor.x+30,RenameFileAnchor.y+50},config.fontSize,config.spacing,config.textColor);

        GuiTextBox({RenameFileAnchor.x+30,RenameFileAnchor.y+100,300,50},newFileName,config.fontSize,true);

        if (GuiButton({RenameFileAnchor.x+30,RenameFileAnchor.y+150,100,20},"Rename")) {
            renameFileDialogState=!renameFileDialogState;
            FileRename(text.filePath.c_str(),newFileName);

            focusedWindow = TextPanel;

            TraceLog(LOG_INFO,TextFormat("File has been renamed into %s",newFileName));
        }
    }
}

void UIDraw::InitWindowFile() {
    fileDialogState = InitGuiWindowFileDialog(GetWorkingDirectory());
}

void UIDraw::DrawWindowFileDialog(TextBuffer& text) {
    GuiWindowFileDialog(&fileDialogState);

    if (fileDialogState.SelectFilePressed) {
        text.filePath = TextFormat("%s" PATH_SEPERATOR "%s",fileDialogState.dirPathText,fileDialogState.fileNameText);
    }else {
        fileDialogState.SelectFilePressed=false;
    }
}

void UIDraw::DrawFileText(EditorConfig& config, TextBuffer& text, Font font){

    Rectangle scrollPanel = {CodePanelAnchor.x + config.gridWidth*6,CodePanelAnchor.y,(float)GetScreenWidth()-CodePanelAnchor.x-60,(float)GetScreenHeight()-CodePanelAnchor.y};

    float contentHeight = text.GetLineCounter() * (config.gridHeight + config.verticalLineSpacing);
    float contentWidth = scrollPanel.width;

    for (std::size_t i=0;i<text.GetLineCounter();i++) {
        Vector2 size = MeasureTextEx(font,text.GetLine(i).c_str(),config.fontSize,config.spacing);

        if (size.x>contentWidth) {
            contentWidth = size.x;
        }
    }

    Rectangle panelContentRec = {CodePanelAnchor.x+config.gridWidth*6 , CodePanelAnchor.y, contentWidth, contentHeight};

    GuiScrollPanel(scrollPanel,NULL,panelContentRec,&scroll,&panelView);

    BeginScissorMode(panelView.x,panelView.y,panelView.width,panelView.height);
    for (std::size_t i=0; i<text.GetLineCounter();i++) {

        float posX = CodePanelAnchor.x + config.gridWidth * 6+ scroll.x;
        float posY = CodePanelAnchor.y+ config.gridHeight *i+config.verticalLineSpacing*i + scroll.y;

        DrawTextEx(font,text.GetLine(i).c_str(),{posX,posY},
            config.fontSize,
            config.spacing,
            config.textColor
        );
    }
    EndScissorMode();
}

void UIDraw::DrawStartingText(EditorConfig& config, TextBuffer& text, Font font) {
    if (!text.isFileLoaded) {
        DrawTextEx(font,
            "Start by loading a file! \nKeybinds: \n"
            "F1 - Debug lines\n"
            "F2 - Debug Info\n"
            "F3 - File saving\n",
            {CodePanelAnchor.x + 100, CodePanelAnchor.y+ 200},
            config.fontSize,config.spacing,config.textColor);
    }
}
