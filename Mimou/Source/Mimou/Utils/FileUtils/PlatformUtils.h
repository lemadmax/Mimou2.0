#pragma once

namespace Mimou
{
	class FileDialog
	{
	public:
		static std::string MEGetOpenFileName(const char* Filter);
		static std::string MEGetSaveFileName(const char* Filter);
	};
}