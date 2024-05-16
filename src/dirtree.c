/*-----------------------------------------------------------------------------
 * File      - dirTree.c
 * Author(s) - Sathish Kumar Srinivasan
 *
 * Purpose   - A tiny and simple but not so perfect way to display 
 *             directories only tree        
 *
 *----------------------------------------------------------------------------- 
 * Notes     - This program do not use any data structure to store directory
 *             information. This causes it to identify the last item in the 
 *             directory subtree, which results in imperfect solution.
 *             A better solution would be store the directory information in a
 *             data structure such as a linked list and call print function to 
 *             display the contents of the data structure.
 *-----------------------------------------------------------------------------
 * Revisions - v0.0.1 - May 16,2024
 *---------------------------------------------------------------------------*/

#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "src/dirtree.h"

#define BUFFER 800

void
dirTree (char *dir_path, int * level) 
{
  DIR *dirp;
  struct stat statbuf;
  struct dirent *dp;
  int errno;
  char filepath[BUFFER];
  int i, k=0;

  dirp = opendir(dir_path);
  if (dirp == NULL) {  // invalid directory name
    return;
  }
  
  //printf("%d\n", *level);
  *level = *level+1;
  for (i=0;;i++) {
    errno = 0;
    dp = readdir(dirp);

    // base case for recursive operation
    if (dp == NULL) {
      *level = *level-1;
      break; // End of directory contents
    }
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
        continue; // Skip . and .. 

    snprintf(filepath, BUFFER, "%s/%s", dir_path, dp->d_name);
    filepath[BUFFER - 1] = '\0'; /* Ensure string is null-terminated */

    if (lstat(filepath, &statbuf) == -1) {
      printf("Error: lstat\n");
    } else if (S_ISDIR(statbuf.st_mode)) {  // filter directory file types
      for (k=1; k < *level; k++) {
        printf("%s", "│" );
        printf("%*s", 2, "" );
      } 
      printf("%s%s\n", "└──", dp->d_name);
      dirTree(filepath, level);  // recursive call
    }
  }

  if (errno != 0)
    printf("Error: readdir\n");

  if (closedir(dirp) == -1)
    printf("Error: closedir\n");

  return;
}


int
main(int argc, char *argv[])
{
  char *dir_path;
  int level = 0;
  
  if (argc < 2) {
    printf("%s\n", "Error: missing directory path" );
    return 1;
  }

  dir_path = argv[1];
  puts(dir_path);
  dirTree(dir_path, &level);
  return 0;
}
