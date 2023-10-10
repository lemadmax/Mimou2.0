#include "mepch.h"
#include "WindowsInput.h"
#include "GLFW/glfw3.h"
#include "Mimou/Application.h"

namespace Mimou
{
    Input* Input::s_Instance = new WindowsInput();
    bool Mimou::WindowsInput::IsKeyPressed_Implement(INT32 KeyCode)
    {
        GLFWwindow* Window = static_cast<GLFWwindow*>(Application::GetInstance()->GetWindow().GetNativeWindow());
        INT32 KeyStatus = glfwGetKey(Window, KeyCode);
        return KeyStatus == GLFW_PRESS;
    }

    bool Mimou::WindowsInput::IsMouseButtonPressed_Implement(INT32 Button)
    {
        GLFWwindow* Window = static_cast<GLFWwindow*>(Application::GetInstance()->GetWindow().GetNativeWindow());
        INT32 ButtonStatus = glfwGetMouseButton(Window, Button);
        return ButtonStatus == GLFW_PRESS;
    }

    bool Mimou::WindowsInput::IsMouseButtonReleased_Implement(INT32 Button)
    {
        GLFWwindow* Window = static_cast<GLFWwindow*>(Application::GetInstance()->GetWindow().GetNativeWindow());
        INT32 ButtonStatus = glfwGetMouseButton(Window, Button);
        return ButtonStatus == GLFW_RELEASE;
    }

    std::pair<float, float> Mimou::WindowsInput::GetMousePosition_Implement()
    {
        double PosX, PosY;
        GLFWwindow* Window = static_cast<GLFWwindow*>(Application::GetInstance()->GetWindow().GetNativeWindow());
        glfwGetCursorPos(Window, &PosX, &PosY);
        return std::pair<float, float>(PosX, PosY);
    }

}