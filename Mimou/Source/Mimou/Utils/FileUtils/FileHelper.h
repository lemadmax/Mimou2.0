#pragma once

namespace Mimou
{
	class ME_API FileHelper
	{
	private:
		FileHelper() {}

	public:
		static FileHelper* Get();

		std::string ReadFile(const std::string& FilePath);
		std::string GetFileNameFromPath(const std::string& FilePath);
	private:
		static FileHelper* s_Instance;
	};
}