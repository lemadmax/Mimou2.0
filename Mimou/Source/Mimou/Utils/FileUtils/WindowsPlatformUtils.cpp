#include "mepch.h"
#include "PlatformUtils.h"
#include "Mimou/Application.h"

#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Mimou
{

	std::string FileDialog::MEGetOpenFileName(const std::string& Filter)
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
		ofn.nFilterIndex = 0;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&ofn) == TRUE)
		{
			std::string Out(ofn.lpstrFile);
			return Out;
		}
		return std::string();
	}

	std::string FileDialog::MEGetSaveFileName(const std::string& Filter)
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
		ofn.nFilterIndex = 0;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetSaveFileNameA(&ofn) == TRUE)
		{
			std::string Out(ofn.lpstrFile);
			return Out;
		}

		return std::string();
	}
}