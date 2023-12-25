#pragma once

namespace Mimou
{
	class FileDialog
	{
	public:
		static std::string MEGetOpenFileName(const std::string& Filter);
		static std::string MEGetSaveFileName(const std::string& Filter);
	};
}