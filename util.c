#include "util.h"
#include <string.h>
#include <pwd.h>
#include <unistd.h>

char* get_relative_path(char* filenameWithEnding){
    unsigned long size_of_config_path= strlen("/.config/LogOutMan/")+ strlen (filenameWithEnding)+1;
    char local_config_path[size_of_config_path];
    strcpy(local_config_path,"/.config/LogOutMan/");
    strcat(local_config_path,filenameWithEnding);
    char* home_environment=getpwuid(getuid())->pw_dir;
    char* path = strcat(home_environment,local_config_path);

    return path;
}