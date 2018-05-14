#include "printers/RotatedFile.h"


#include <fstream>



namespace oolog {
	namespace printers {

		RotatedFile::RotatedFile(const std::string logFilename,
													   unsigned long maxSizeInBytes,
													   unsigned char maxHistoryLevels) :
			filename(logFilename),
			maxSize(maxSizeInBytes),
			maxLevels(maxHistoryLevels)
		{
			// Empty
		}
		
		
		
		void RotatedFile::PrintLog(std::string& textToLog, LogLevel logLevel) {
			ExecuteRotation(filename);
			
			std::ofstream logFile = OpenFile(filename);
			WriteToFile(logFile, textToLog);
			CloseFile(logFile);
		}
		
		
		
		std::ofstream RotatedFile::OpenFile(const std::string& fileName) {
			std::ofstream logFile(fileName, std::ofstream::app);
			return logFile;
		}



		void RotatedFile::CloseFile(std::ofstream& logFile) {
			logFile.close();
		}
		
		
		
		void RotatedFile::WriteToFile(std::ofstream& file, const std::string& content) {
			file << content;
		}
		
		
		
		bool RotatedFile::FileExists(const std::string& file) {
			std::ifstream fileStream(file.c_str());
			return fileStream.good();
		}
		
		
		
		void RotatedFile::RemoveFile(const std::string& file) {
			std::remove(file.c_str());
		}
		
		
		
		void RotatedFile::RenameFile(const std::string& currentName, const std::string& newName) {
			std::rename(currentName.c_str(), newName.c_str());
		}
		
		
		
		void RotatedFile::ExecuteRotation(const std::string& fileName) {
			if(HasMaxSizeBeenReached(fileName)) {
				RotateFile(fileName);
			}
		}
		
		
		
		bool RotatedFile::HasMaxSizeBeenReached(const std::string& fileName) {
			bool maxSizeReached = false;
			
			std::ifstream file(fileName, std::ifstream::ate | std::ifstream::binary);
			std::ifstream::pos_type pos = file.tellg();
			
			if(pos > 0) {
				unsigned long fileSize = pos;
				maxSizeReached = (fileSize >= maxSize);
			}
			
			return maxSizeReached;
		}
		
		
		
		void RotatedFile::RotateFile(const std::string& fileName) {
			if(maxLevels == 0) {
				RemoveFile(fileName);
			}
			else {
				RotateToLevel(fileName, 1);
			}
		}
		
		
		
		void RotatedFile::RotateToLevel(const std::string& fileName,
										unsigned char level)
		{
			std::string previousLevelFile = (level == 1) ? 
											fileName :
											ConstructFilename(fileName, level - 1);
			std::string currentLevelFile = ConstructFilename(fileName, level);
			
			if(FileExists(currentLevelFile)) {
				if(level == maxLevels) {
					RemoveFile(currentLevelFile);
				}
				else if(level < 255) {
					RotateToLevel(fileName, level + 1);
				}
			}

			RenameFile(previousLevelFile.c_str(), currentLevelFile.c_str());
		}
		
		
		
		std::string RotatedFile::ConstructFilename(const std::string& fileName,
													unsigned char level)
		{
			std::stringstream stream;
			stream << fileName << "." << int(level);
			return stream.str();
		}

	}
}


