#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[]) {
  if (argc != 2) {
    printf(1, "Specify what to show as one of: \"state\", \"openfiles\", \"ids\"\n");
    exit();
  }
  if ((strcmp(argv[1], "state") != 0) &&
      (strcmp(argv[1], "openfiles") != 0) &&
      (strcmp(argv[1], "ids") != 0)) {
    printf(1, "Specify what to show as one of: \"state\", \"openfiles\", \"ids\"\n");
    exit();
  }
  procs(argv[1]);
  exit();
}
