//
// main.cpp for  in /home/nicolaschr/Work/artificial_intelligence/src
//
// Made by Nicolas Charvoz
// Login   <nicolaschr@epitech.net>
//
// Started on  Sun Jan 10 14:12:40 2016 Nicolas Charvoz
// Last update Sun Jan 10 14:23:51 2016 Nicolas Charvoz
//
#include <Root.hpp>

int             main(int ac, char **av)
{
  (void) ac;
  (void) av;
  Root *r = new Root("Root");
  for (std::string line; std::getline(std::cin, line);) {
    r->analyze(line, false);
  }
  return (0);
}
