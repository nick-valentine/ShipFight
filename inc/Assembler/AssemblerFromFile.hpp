#ifndef ASSEMBLERFROMFILE_HPP
#define ASSEMBLERFROMFILE_HPP

#include "Assembler/AbstractAssembler.hpp"

#include <fstream>
#include <string>

class AssemblerFromFile : public AbstractAssembler
{
private:
  int statement_iterator;

  std::vector<std::string> file_data;
protected:
  std::string file_name;
public:
  AssemblerFromFile(std::string file_name);

  void load_file();
  std::vector<std::string> json_parse();

  int translate_statement();
};

#endif //ASSEMBLERFROMFILE_HPP
