#include <string>
#include <iostream>
#include <dirent.h>
#include <errno.h>
#include <vector>

using namespace std;

int getdir(string dir, vector<string> &files);

int main(){
  string dir = ".";
  vector<string> files = vector<string>();
  getdir(dir, files);
  int i=0;
  for(i=0;i<files.size();i++){
    cout<<files[i]<<endl;
  }
  return 0;
}

int getdir(string dir, vector<string> &files){
  DIR *dp;//dir pointer
  struct dirent *dirp;
  if((dp=opendir(dir.c_str()))==NULL){
    cout<<"ERROR("<<errno<<") opening "<<dir<<endl;
    return errno;
  }
  while((dirp=readdir(dp))!=NULL){
    //if dir pointer != null
    files.push_back(string(dirp->d_name));//put dir & file name into vector
  }
  closedir(dp);
  return 0;
}

//const string place_of_mp3_lib="HowHow-parser/result/mp3";
