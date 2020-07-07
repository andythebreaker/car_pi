//using .h github.com/yhirose/cpp-httplib
//using .h github.com/sheredom/json.h

#include <iostream>
#include <string>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include "httplib.h"
#include "json.h"

using namespace std;

//int i = 0;//for loop
//int j = 0;//for loop

string pig_get_parse(string in_str, int ifvisual);
int getdir(string dir, vector<string> &files);

const string place_of_mp3_lib="HowHow-parser/result/mp3";

int main(){
  cout<<"start"<<endl;
  cout<<pig_get_parse("測試訊息",0)<<endl;
  cout<<"end"<<endl;
  string dir = ".";
  vector<string> files = vector<string>();
  getdir(dir, files);
  int i=0;
  for(i=0;i<files.size();i++){
    cout<<files[i]<<endl;
  }
  return 0;
}

//chinese 2 pinging
string pig_get_parse(string in_str, int ifvisual){
  //const
  string str_data="data";
  string str_text="text";
  int http_port = 80;
  string str_url="api.zhconvert.org";
  string str_get1="/convert?converter=Pinyin&text=";
  string str_get2="&prettify=1";
  int i=0;//loop
  int j=0;//loop
  string wget="";
  string str_get=str_get1+in_str+str_get2;
  
  //http get
  //httplib::Client cli("api.zhconvert.org",80);
  //make client
  httplib::Client cli(str_url,http_port);

  //get
  //auto res = cli.Get("/convert?converter=Pinyin&text=這是一格測試的請求&prettify=1");
  auto res = cli.Get(str_get.c_str());
  if (res && res->status == 200){
    wget=res->body;
    if(ifvisual==1)cout<<wget.c_str()<<endl;
    //cout<<res->body<<endl;
  }

  //parse json
  if(ifvisual==1)cout<<"=====josn====="<<endl;
  string target_ans="";
  string inside_data="";
  struct json_value_s* json_root = json_parse(wget.c_str(), strlen(wget.c_str()));
  struct json_object_s* json_obj = json_value_as_object(json_root);
  assert(json_obj != NULL);//stop and print code if statement is true
  if(ifvisual==1)cout<<"json length = "<<json_obj->length<<endl;
  if(ifvisual==1)cout<<"top layer :{"<<endl;
  struct json_object_element_s* elem_tmp = json_obj->start;
  if(ifvisual==1)cout<<"    "<<elem_tmp->name->string<<endl;
  //top layer
  for(i=0;i<json_obj->length-1;i++){
    elem_tmp = elem_tmp->next;
    if(ifvisual==1)cout<<"    "<<elem_tmp->name->string<<endl;
    if (strncmp(elem_tmp->name->string, str_data.c_str(), strlen(str_data.c_str()))==0){//compare if elem name == "data" , using "strncmp" to compare the first 4 char is/or not the same, return 0 if true
      struct json_object_element_s* elem_inside_data = json_value_as_object(elem_tmp->value)->start;
      inside_data+=elem_inside_data->name->string;
      inside_data+="\n";
      //inside data
      for(j=0;j<json_value_as_object(elem_tmp->value)->length-1;j++){
        elem_inside_data=elem_inside_data->next;
        inside_data+=elem_inside_data->name->string;
        /*if(j<json_value_as_object(elem_tmp->value)->length-2)*/inside_data+="\n";
        if ((strncmp(elem_inside_data->name->string,str_text.c_str(),strlen(str_text.c_str()))==0)&&(elem_inside_data->name->string_size==strlen(str_text.c_str()))){
          target_ans=json_value_as_string(elem_inside_data->value)->string;
        }
      }
    }
  }
  if(ifvisual==1)cout<<"}"<<endl;
  free(json_root);
  if(ifvisual==1)cout<<"inside \"data\" have these element :{\n"<<inside_data<</*"\n}"*/"}"<<endl;
  if(ifvisual==1)cout<<"target = "<<target_ans<<endl;
  return target_ans;
}

//list file
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
