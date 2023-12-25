#include "mepch.h"
#include "PlatformUtils.h"
#include "Mimou/Application.h"

#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Mimou
{

	std::string FileDialog::GetFileName(const std::string& Filter)
	{
		OPENFILENAMEA ofn;
		char szFile[260] = { 0 };
		HWND hwnd = glfwGetWin32Window((GLFWwindow*)Application::GetInstance()->GetWindow().GetNativeWindow());
		HANDLE hf;

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hwnd;
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = Filter.c_str();
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&ofn) == TRUE)
		{
			std::string Out(ofn.lpstrFile);
			return Out;
		}
	}

	std::string FileDialog::SaveFile(const std::string& Filter)
	{
		return std::string();
	}
}