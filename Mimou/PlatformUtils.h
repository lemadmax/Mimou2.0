#pragma once

namespace Mimou
{
	class FileDialog
	{
	public:
		static std::string OpenFile(const std::wstring& Filter);
		static std::string SaveFile(const std::string& Filter);
	};
}