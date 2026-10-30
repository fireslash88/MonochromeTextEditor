#include "TextBuffer.h"
#include "raylib.h"

#include <iostream>
#include <fstream>

void TextBuffer::LoadFromFile(const std::string& filepath2) {
    std::ifstream file(filepath2);

    if (!file.is_open()) {
        TraceLog(LOG_ERROR,"Error while loading the file");
        return;
    }

    lines.clear();

    std::string line;

    while (std::getline(file, line)){
        lines.push_back(line);
    }

    if (lines.empty()) {
        lines.emplace_back();
    }

    cursorColumn=0;
    cursorLine=0;

    filePath=filepath2;

    isFileLoaded=true;

    TraceLog(LOG_INFO,"File loaded");
    file.close();
}

void TextBuffer::SaveToFile(const std::string& filepath2) {
    std::ofstream file (filepath2);

    if (!file.is_open()) {
        TraceLog(LOG_ERROR,"Error while saving file");
        return;
    }

    for (std::size_t i=0;i<lines.size();i++) {
        file<<lines.at(i);

        if (i+1<lines.size()) {
            file<<'\n';
        }
    }

    TraceLog(LOG_INFO,"File saved");
    file.close();
}

void TextBuffer::InsertText(char character) {
    lines.at(cursorLine).insert(
        cursorColumn,
        1,
        character);
    cursorColumn++;
}

void TextBuffer::NewLine() {
    std::string& currentLine = lines.at(cursorLine);

    std::string newLine = currentLine.substr(cursorColumn);

    currentLine.erase(cursorColumn);

    lines.insert(
        lines.begin() + cursorLine + 1,
        newLine
        );

    cursorLine++;
    cursorColumn=0;
}

void TextBuffer::Backspace() {
    if (cursorColumn>0) {
        lines.at(cursorLine).erase(cursorColumn-1,1);
        cursorColumn--;

        return;
    }

    if (cursorLine>0) {
        std::size_t previousLineLength = lines.at(cursorLine-1).size();

        lines.at(cursorLine-1) += lines.at(cursorLine);

        lines.erase(lines.begin()+ cursorLine);

        cursorLine--;

        cursorColumn = previousLineLength;
    }
}

void TextBuffer::InsertTab() {
    lines.at(cursorLine).insert(
        cursorColumn,
        4,
        ' '
        );
    cursorColumn+=4;
}

void TextBuffer::MoveCursorLeft() {
    if (cursorColumn>0) {
        cursorColumn--;
        return;
    }

    if (cursorLine>0) {
        cursorLine--;
        cursorColumn=lines.at(cursorLine).size();
    }
}

void TextBuffer::MoveCursorRight() {
    if (cursorColumn<lines.at(cursorLine).size()) {
        cursorColumn++;
        return;
    }
    if (cursorLine+1 < lines.size()) {
        cursorLine++;
        cursorColumn=0;
    }
}

void TextBuffer::MoveCursorUp() {
    if (cursorLine>0) {
        cursorLine--;
        cursorColumn=lines.at(cursorLine).size();
    }
}

void TextBuffer::MoveCursorDown() {
    if (cursorLine+1<lines.size()) {
        cursorLine++;
        cursorColumn=lines.at(cursorLine).size();
    }
}

std::string TextBuffer::GetLine(std::size_t line) {
    return lines.at(line);
}

std::size_t TextBuffer::GetLineCounter() {
    return lines.size();
}

std::size_t TextBuffer::GetCursorLine() {
    return cursorLine;
}

std::size_t TextBuffer::GetCursorColumn() {
    return cursorColumn;
}
