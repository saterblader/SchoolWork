#include <iostream>
#include "FileSystem.h"

void demo_read_write_file_in_buffer()
{
	std::cout << "Demo Read/Write File through Buffer" << std::endl;
	std::cout << "===================================\n" << std::endl;

	std::string ReadFilePath = "FileSystem.cpp";
	std::string WriteFilePath = "FileSystem_Copy_Buffer.cpp";

	if (!FileSystem::File::exists(ReadFilePath)) {
		std::cout << "Input doesn't exist" << std::endl;
		return;
	}
	FileSystem::File ReadFile(ReadFilePath);
	ReadFile.open(FileSystem::File::in, FileSystem::File::binary);
	if (!ReadFile.isGood())
	{
		std::cout << "Error while opening input file" << std::endl;
		return;
	}

	if (FileSystem::File::exists(WriteFilePath)) {
		std::cout << "Output file "<< WriteFilePath <<" already exist" << std::endl;
		return;
	}
	FileSystem::File WriteFile(WriteFilePath);
	WriteFile.open(FileSystem::File::out, FileSystem::File::binary);
	if (!WriteFile.isGood())
	{
		std::cout << "Error while opening output file" << std::endl;
		return;
	}

	const int BufferLength = 1024;
	char buffer[BufferLength];
	size_t ReadLength;

	std::cout << "Copy from \""<<ReadFilePath<<"\" to \""<<WriteFilePath<<"\" through Buffer\n" << std::endl;

	while (true)
	{
		ReadLength = ReadFile.getBuffer(BufferLength, buffer);
		WriteFile.putBuffer(ReadLength, buffer);
		if (ReadLength < 1024)
		{
			ReadFile.close();
			WriteFile.close();
			break;
		}
	}
	if (ReadFile.isGood())
	{
		std::cout << "Error while closing read file" << std::endl;
		return;
	}
	if (WriteFile.isGood())
	{
		std::cout << "Error while closing write file" << std::endl;
		return;
	}
	std::cout << "Copy Finish\n" << std::endl;
}
void demo_read_write_file_in_block()
{
	std::cout << "\nDemo Read/Write File through Block" << std::endl;
	std::cout << "==================================\n" << std::endl;

	std::string ReadFilePath = "FileSystem.cpp";
	std::string WriteFilePath = "FileSystem_Copy_Block.cpp";

	if (!FileSystem::File::exists(ReadFilePath)) {
		std::cout << "Input doesn't exist" << std::endl;
		return;
	}
	FileSystem::File ReadFile(ReadFilePath);
	ReadFile.open(FileSystem::File::in, FileSystem::File::binary);
	if (!ReadFile.isGood())
	{
		std::cout << "Error while opening input file" << std::endl;
		return;
	}

	if (FileSystem::File::exists(WriteFilePath)) {
		std::cout << "Output file " << WriteFilePath << " already exist" << std::endl;
		return;
	}
	FileSystem::File WriteFile(WriteFilePath);
	WriteFile.open(FileSystem::File::out, FileSystem::File::binary);
	if (!WriteFile.isGood())
	{
		std::cout << "Error while opening output file" << std::endl;
		return;
	}
	FileSystem::Block Block_;
	const int BlockLength = 1024;

	std::cout << "Copy from \"" << ReadFilePath << "\" to \"" << WriteFilePath << "\" through Block\n" << std::endl;

	while (true)
	{
		Block_ = ReadFile.getBlock(BlockLength);
		WriteFile.putBlock(Block_);
		if (Block_.size() < 1024)
		{
			WriteFile.close();
			ReadFile.close();
			break;
		}
	}
	if (ReadFile.isGood())
	{
		std::cout << "Error while closing read file" << std::endl;
		return;
	}
	if (WriteFile.isGood())
	{
		std::cout << "Error while closing write file" << std::endl;
		return;
	}
	std::cout << "Copy Finish\n" << std::endl;
}
int main() {
	demo_read_write_file_in_buffer();
	demo_read_write_file_in_block();
}