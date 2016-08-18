#include "Assembler/AssemblerFromFile.hpp"

AssemblerFromFile::AssemblerFromFile(std::string file_name)
{
  this->file_name = file_name;

  this->statement_iterator = 0;
}

void AssemblerFromFile::load_file()
{
  file_data = std::vector<std::string>();

  std::ifstream ifile(this->file_name.c_str());

  std::string line;
  while(ifile.good()) {
    ifile>>line;
    file_data.push_back(line);
  }

  ifile.close();
}

std::vector<std::string> AssemblerFromFile::json_parse()
{

}

int AssemblerFromFile::translate_statement()
{

}
