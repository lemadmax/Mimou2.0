#include "mepch.h"
#include "FileHelper.h"

namespace Mimou
{
	FileHelper* FileHelper::s_Instance = nullptr;

	FileHelper* FileHelper::Get()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new FileHelper();
		}
		return s_Instance;
	}
	std::string FileHelper::ReadFile(const std::string& FilePath)
	{
		std::string Result;
		std::ifstream In(FilePath, std::ios::in, std::ios::binary);
		if (In)
		{
			In.seekg(0, std::ios::end);
			Result.resize(In.tellg());
			In.seekg(0, std::ios::beg);
			In.read(&Result[0], Result.size());
			In.close();
		}
		else
		{
			ME_ENGINE_ASSERT("Cannot open file: {}", FilePath);
		}
		return Result;
	}
	std::string FileHelper::GetFileNameFromPath(const std::string& FilePath)
	{
		std::string Result;

		size_t LastSlash = FilePath.find_last_of("/\\");
		LastSlash = LastSlash == std::string::npos ? 0 : LastSlash + 1;
		size_t LastDot = FilePath.rfind('.');
		size_t Count = LastDot == std::string::npos ? FilePath.size() - LastSlash : LastDot - LastSlash;
		Result = FilePath.substr(LastSlash, Count);

		return Result;
	}
}