#include "ViewerCore.h"

int main(int argc, char **argv)
{

  ViewerCore viewerCore;
  viewerCore.setup();
  while (viewerCore.frame()) {}
  return 0;
}