#include "UIDraw.h"
#include "../core/Editor.h"
#include "../settings/config.h"

void UIDraw::DrawDebugLines(EditorConfig& config, TextBuffer& text) {
    int gridRows = GetScreenHeight();
    int gridCols = GetScreenWidth() / config.gridWidth;
    //Draws debug grid
    if (config.debugLines) {
        BeginScissorMode(panelView.x,panelView.y,panelView.width,panelView.height);

        for (int i = 0; i < gridCols; i++) {
            DrawRectangleLines(
                i * config.gridWidth + CodePanelAnchor.x,
                CodePanelAnchor.y + scroll.x,
                2,
                GetScreenHeight(),
                GRAY);
        }

        for (int i = 0; i < gridRows; i++) {
            DrawRectangleLines(
                CodePanelAnchor.x + scroll.x,
                i * config.verticalLineSpacing + (i+1) * config.gridHeight + CodePanelAnchor.y + scroll.y,
                GetScreenWidth(),
                2,
                GRAY);
            DrawRectangleLines(
                CodePanelAnchor.x + scroll.x,
                i * config.verticalLineSpacing + i  * config.gridHeight + CodePanelAnchor.y + scroll.y,
                GetScreenWidth(),
                2,
                GRAY);
        }
        EndScissorMode();
    }
}

void UIDraw::DrawDebugInfo(EditorConfig& config, TextBuffer& text) {
    if (config.debugInfo) {
        DrawText(TextFormat("cursorColumn %i" , text.GetCursorColumn()),1000,500,20,RED);
        DrawText(TextFormat("cursorLine %i" , text.GetCursorLine()),1000,520,20,RED);
        DrawText(TextFormat("fontSize %.00f" , config.fontSize),1000,540,20,RED);

        DrawText(TextFormat("filePath %s", text.filePath.c_str()),300,560,20,RED);
    }
}