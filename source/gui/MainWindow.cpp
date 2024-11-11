//
// Created by Orange on 11/11/2024.
//

#include "MainWindow.hpp"

#include <algorithm>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


namespace imgui_desktop::gui
{
    bool MainWindow::m_canMoveWindow = false;

    MainWindow::MainWindow(const std::string_view &caption, int width, int height)
    {
        if (!glfwInit())
            std::exit(EXIT_FAILURE);

        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);
        m_window = glfwCreateWindow(width, height, caption.data(), nullptr, nullptr);

        glfwSetMouseButtonCallback(m_window, OnMouseClick);
        glfwSetCursorPosCallback(m_window, OnMouseMove);

        glfwSetWindowAttrib(m_window, GLFW_DECORATED, false);
        glfwMakeContextCurrent(m_window);

        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    void MainWindow::Run()
    {
        while (!glfwWindowShouldClose(m_window) && m_opened)
        {
            glfwPollEvents();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();


            ImGui::Begin("ImGUI Desktop", &m_opened,
                ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
            {
                ImGui::SetWindowPos({});
                ImGui::SetWindowSize(ImGui::GetMainViewport()->Size);
                ImGui::Text("Hello World!");
                ImGui::End();
            }
            ImGui::Render();

            int display_w, display_h;

            glfwGetFramebufferSize(m_window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);

            glClearColor(0.f, 0.f, 0.f, 0.f);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(m_window);
        }
        glfwDestroyWindow(m_window);
    }

    void MainWindow::OnMouseMove(GLFWwindow *window, double, double)
    {
        const auto getMousePos = [window]
        {
            int wx, wy;
            double cx, cy;
            glfwGetWindowPos(window, &wx, &wy);
            glfwGetCursorPos(window, &cx, &cy);

            return std::make_pair<int, int>(wx + cx, wy + cy);
        };

        static auto oldMousePos = getMousePos();
        const auto curMousePos = getMousePos();

        if (m_canMoveWindow)
        {
            const auto mouseDiffX = curMousePos.first - oldMousePos.first;
            const auto mouseDiffY = curMousePos.second - oldMousePos.second;

            int x, y;
            glfwGetWindowPos(window, &x, &y);

            int width, height;
            glfwGetWindowSize(window, &width, &height);
            const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            glfwSetWindowPos(window, std::clamp(x + mouseDiffX, 0, mode->width - width),
                             std::clamp(y + mouseDiffY, 0, mode->height - height));
        }
        oldMousePos = curMousePos;
    }

    void MainWindow::OnMouseClick(GLFWwindow* wnd, int button, int action, int)
    {
        double wx, wy;
        glfwGetCursorPos(wnd, &wx, &wy);

        m_canMoveWindow = button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && (wy >= 0 && wy <= 19);
    }
} // gui
// imgui_desktop
