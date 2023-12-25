#pragma once

namespace Mimou
{
	class FileDialog
	{
	public:
		static std::string GetFileName(const std::string& Filter);
		static std::string SaveFile(const std::string& Filter);
	};
}