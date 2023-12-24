#include "mepch.h"
#include "PlatformUtils.h"
#include "Mimou/Application.h"

#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Mimou
{

	std::string FileDialog::OpenFile(const std::string& Filter)
	{
		OPENFILENAME ofn;
		WCHAR szFile[260] = { 0 };
		HWND hwnd = glfwGetWin32Window((GLFWwindow*)Application::GetInstance()->GetWindow().GetNativeWindow());
		HANDLE fh;

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hwnd;
		ofn.lpstrFile = szFile;
	}

	std::string FileDialog::SaveFile(const std::string& Filter)
	{

	}
}