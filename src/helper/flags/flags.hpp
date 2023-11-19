#pragma once

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

// #include "../../compiler/compiler.hpp"
// #include "../../generation/gen.hpp"
#include "../../lexer/lexer.hpp"
#include "getCurrentTime.hpp"
#include "../../common.hpp"
#include "version.hpp"

using namespace std;

static char *read_file(const char *path) {
  ifstream file(path, ios::binary);
  if (!file) {
    cerr << "Could not open file \"" << path << "\"." << endl;
    NebrixExit(INVALID_FILE);
  }

  file.seekg(0, ios::end);
  size_t file_size = file.tellg();
  file.seekg(0, ios::beg);

  char *buffer = new char[file_size + 1];
  file.read(buffer, file_size);
  file.close();

  buffer[file_size] = '\0';
  return buffer;
}

// void compileASM(char* name) {
//   char compileCommand[256];
//   snprintf(compileCommand, sizeof(compileCommand), "gcc -m32 a.s -o %s", name);
//   system(compileCommand);
// }

// void run_file(const char *path, char* outName) {
//   const char *source = read_file(path);
//   compile(source);
  
//   delete[] source;

//   writeASM();
//   compileASM(outName);
//   system("rm -rf a.s");
// }

// void run_file_save(const char *path, char* outName) {
//   const char *source = read_file(path);
//   compile(source);
  
//   delete[] source;

//   writeASM();
//   compileASM(outName);
// }

inline void run_file(const char *path) {
   // This needs to be setup for transpiling to assembly
   // the command for it will be 
   // zura -t <file> -o <output>
    // the output will be a .s file

  const char *source = read_file(path);
  tokens.init_tokenization(source);
  Tokens::Token token = tokens.scan_token();
  while (token.kind != Tokens::Kind::EOF_TOKEN) {
    cout << "Token Kind: " << token.kind << endl;
    cout << "Token Start: " << token.start - token.length << endl;
    cout << "Token Pos: " << token.pos << endl;
    cout << "Token Line: " << token.line << endl;
    cout << endl;
    token = tokens.scan_token();
  }
  delete[] source;
}

inline void flags(int argc, char *argv[]) {

  if (argc == 2 && strcmp(argv[1], "--help") == 0) {
    cout << "Usage: " << argv[0] << " [options]" << endl;
    cout << "Options:" << endl;
    cout << "  --help\t\t\tPrints this help message" << endl;
    cout << "  --version\t\t\tPrints the version of the compiler" << endl;
    cout << "  --license\t\t\tPrints the license of the Zura Lang" << endl;
    cout << "Compiler:" << endl;
    cout << "   -s, \t\tsave the generated assembly file and the a.o file" << endl;
    cout << "   -o, \t\tOutput the transpiled file to <file>" << endl;
    cout << "   -c, \t\tDelete the exacutable file and asm file if it is there." << endl;
    cout << "Package Manager: (Not yet implemented)" << endl;
    cout << "   -i, \t\tInstall a package" << endl;
    cout << "   -u, \t\tUninstall a package" << endl;
    cout << "   -l, \t\tList all installed packages" << endl;
    cout << "   -s, \t\tSearch for a package" << endl;
    cout << "   -v, \t\tView a package" << endl;
    NebrixExit(OK);
  }

  if (argc == 3 && strcmp(argv[1], "-c") == 0) {
    char* outName = argv[2];
    char rmCommand[256];
    snprintf(rmCommand, sizeof(rmCommand), "rm -rf %s", outName);
    system(rmCommand);
    snprintf(rmCommand, sizeof(rmCommand), "rm -rf a.s");
    system(rmCommand);
    NebrixExit(OK);
  }

  if (argc == 4 && strcmp(argv[2], "-o") == 0) {
    char* outName = argv[3];
    // run_file(argv[1], outName);
  }

  if (argc == 5 && strcmp(argv[2], "-o") == 0 && strcmp(argv[4], "-s") == 0) {
    char* outName = argv[3];
    // run_file_save(argv[1], outName);
  }

  if (argc == 2 && strcmp(argv[1], "--version") == 0) {
    cout << get_Nebrix_version_string() << "(" << getCurrentTime() << ")" << endl;
    NebrixExit(OK);
  }
  if (argc == 2 && strcmp(argv[1], "--license") == 0) {
    cout << "Nebrix Lang is licenesed under GPL-3.0 "
            "license(https://www.gnu.org/licenses/gpl-3.0.en.html) "
         << endl;
    NebrixExit(OK);
  }
}