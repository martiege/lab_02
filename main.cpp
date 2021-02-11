#include "lab_2.h"
#include <iostream>

int main()
{
  std::cout << "Starting main...\n"; 
  try
  {
    lab2();
  }
  catch (const std::exception& e)
  {
    std::cerr << "Caught exception:" << std::endl
              << e.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "Caught unknown exception" << std::endl;
  }

  return EXIT_SUCCESS;
}
