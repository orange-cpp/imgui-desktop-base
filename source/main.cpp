//
// Created by Orange on 11/11/2024.
//
#include <Windows.h>
#include "gui/MainWindow.hpp"

int APIENTRY WinMain(HINSTANCE, HINSTANCE, PSTR, int)
{
    imgui_desktop::gui::MainWindow("ImGUI Desktop", 700, 500).Run();
}