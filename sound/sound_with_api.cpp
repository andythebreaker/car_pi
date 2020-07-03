#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#define DEBUG_PART01 0
#define DEBUG_CUT_PINGING 0
#define PRINT_LIST 0
#define DEBUG12 0
#define DEBUG_FFMPEG 1
using namespace std;
int main(){
  const string str_mp3=".mp3";
  if(DEBUG_FFMPEG==0)const string str_ffmpeg_head="ffmpeg";
  if(DEBUG_FFMPEG==0)const string str_ffmpeg_end=" -filter_complex [0:a][1:a]concat=n=2:v=0:a=1 output.mp3";
  const string place_of_mp3_lib="HowHow-parser/result/mp3";
  const string str_mp3_place1="/1";
  const string str_mp3_place2="/2";
  const string str_wget="wget ";
  const string str_http ="http://";
  const string srt_api="api.zhconvert.org/";
  const string str_convert="convert?";
  const string str_parameter_converter="converter=";
  const string str_pinying="Pinyin";
  const string str_parameter_text="&text=";
  const string str_parameter_prettify="&prettify=1";
  const string str_file_out_O=" -O ";
  const string str_file_out_name="zh2pinging_tmp.txt";
  const string str_file_out=str_file_out_O+str_file_out_name;
  const string str_dir="dir ";
  const string str_dir_list_text_1="tmp_dir_mp3_lib_list_1.txt";
  const string str_dir_list_text_2="tmp_dir_mp3_lib_list_2.txt";
  const string str_out_to_text=" > ";
  const string str_out_to_text_1=str_out_to_text+str_dir_list_text_1;
  const string str_out_to_text_2=str_out_to_text+str_dir_list_text_2;
  char ch;
  string file_res="";

  //api down
  string txt = "引擎轉速為二十公尺每秒";
  cout<<"start"<<endl;
  string command = str_wget + "\'" + str_http + srt_api +str_convert + str_parameter_converter + str_pinying + str_parameter_text + txt + str_parameter_prettify + "\'" + str_file_out;
  system(command.c_str());
  ifstream tmp_fin;
  tmp_fin.open(str_file_out_name);
  if(!tmp_fin){
    cout<<"api download error!"<<endl;
    return 1;
  }else{
    while(!tmp_fin.eof()){
      tmp_fin.get(ch);
      file_res+=ch;
    }
  }
  cout<<file_res;
  tmp_fin.close();
  if(DEBUG_PART01)cout<<"\nFOUND(data)@"<<file_res.find("data")<<endl;
  if((file_res.find("data")!=string::npos)&&(file_res.find("text")!=string::npos)&&(file_res.find("data")<file_res.find("text"))){
    if(DEBUG_PART01)cout<<"OK"<<endl;    
  }else{
    cout<<"phase error!"<<endl;
    return 1;
  }
  int st=(int)file_res.find("\"",1+file_res.find("\"",file_res.find("text")));
  int ed=(int)file_res.find("\"",1+file_res.find("\"",1+file_res.find("\"",file_res.find("text"))));
  if(DEBUG_PART01)cout<<st<<endl<<ed-st<<endl<<file_res.substr(st+1,ed-st-1);
  string response = file_res.substr(st+1,ed-st-1);
  cout<<endl<<"========GOT answer========"<<endl<<txt<<" = "<<response<<endl<<"=========================="<<endl;
  
  //check mp3 lib
  command="";
  command=str_dir+place_of_mp3_lib+str_mp3_place1+str_out_to_text_1;
  system(command.c_str());
  command=str_dir+place_of_mp3_lib+str_mp3_place2+str_out_to_text_2;
  system(command.c_str());
  string list_mp3_lib_1="";
  string list_mp3_lib_2="";
  ifstream list_mp3_lib1;
  ifstream list_mp3_lib2;
  list_mp3_lib1.open(str_dir_list_text_1);
  list_mp3_lib2.open(str_dir_list_text_2);
  if(!list_mp3_lib1){
    cout<<"mp3 lib 1 open error!"<<endl;
    return 1;
  }else{
    while(!list_mp3_lib1.eof()){
      list_mp3_lib1.get(ch);
      list_mp3_lib_1+=ch;
    }
  }
  if(!list_mp3_lib2){
    cout<<"mp3 lib 2 open error!"<<endl;
    return 1;
  }else{
    while(!list_mp3_lib2.eof()){
      list_mp3_lib2.get(ch);
      list_mp3_lib_2+=ch;
    }
  }
  if(PRINT_LIST)cout<<"=====mp3 lib 1====="<<endl<<list_mp3_lib_1<<endl<<"=====mp3 lib 2====="<<endl<<list_mp3_lib_2<<endl;
  list_mp3_lib1.close();
  list_mp3_lib2.close();
  
  //cut target pinging 
  int how_meny_word=0;
  int i_check_how_much_word=0;
  for(i_check_how_much_word=0;i_check_how_much_word<response.length();i_check_how_much_word++){
    char tmp_ch=response[i_check_how_much_word];
    if (tmp_ch==' '){
      how_meny_word++;
    }
  }
  how_meny_word++;
  string str2ary=response;
  int i_cut=0;
  string arr[how_meny_word];
  stringstream ssin(str2ary);
  while (ssin.good()&&i_cut<how_meny_word){
    ssin>>arr[i_cut];
    ++i_cut;
  }
  if(DEBUG_CUT_PINGING){
    for(i_cut=0;i_cut<how_meny_word;i_cut++){
      cout<<arr[i_cut]<<endl;
    }
  }
  int pinging_mp3_loc[how_meny_word]={0};
  for(i_cut=0;i_cut<how_meny_word;i_cut++){
    pinging_mp3_loc[i_cut]=(list_mp3_lib_1.find(arr[i_cut])==string::npos)?0:1;
    if(pinging_mp3_loc[i_cut]==0)pinging_mp3_loc[i_cut]=(list_mp3_lib_2.find(arr[i_cut])==string::npos)?0:2;
  }
  int check_no_mp3=-1;
  for(i_cut=0;i_cut<how_meny_word;i_cut++){
    cout<<"mp3 loc folder (1/2): "<<pinging_mp3_loc[i_cut]<<endl;
    check_no_mp3*=pinging_mp3_loc[i_cut];
  }
  if(check_no_mp3==0){
    cout<<"ERROR, some word don't have mp3 file."<<endl;
    if(DEBUG12==0)return 1;
    if(DEBUG12)cout<<"DEBUG12 is on, do _2_ anyway"<<endl;
  }
  string real_mp3_loc[how_meny_word]={""};
  for(i_cut=0;i_cut<how_meny_word;i_cut++){
    if(DEBUG12==0){
      if(pinging_mp3_loc[i_cut]==1){
      real_mp3_loc[i_cut]+=place_of_mp3_lib;
      real_mp3_loc[i_cut]+=str_mp3_place1;
    }else if(pinging_mp3_loc[i_cut]==2){
      real_mp3_loc[i_cut]+=place_of_mp3_lib;
      real_mp3_loc[i_cut]+=str_mp3_place2;
    }else{
      cout<<"ERROR!(no word mp3)"<<endl;
      return 1;
    }
    }
    if(DEBUG12)real_mp3_loc[i_cut]+=place_of_mp3_lib;
    if(DEBUG12)real_mp3_loc[i_cut]+=str_mp3_place2;
    real_mp3_loc[i_cut]+="/";
    real_mp3_loc[i_cut]+=arr[i_cut];
    real_mp3_loc[i_cut]+=str_mp3;
  }
  string all_mp3_file="";
  for(i_cut=0;i_cut<how_meny_word;i_cut++){
    //if(i_cut!=0)all_mp3_file+="|";
    if(DEBUG_FFMPEG){if(i_cut==0){all_mp3_file+="#\n";}};
    if(DEBUG_FFMPEG==0)all_mp3_file+=" -i ";
    if(DEBUG_FFMPEG)all_mp3_file+="file '";
    all_mp3_file+=real_mp3_loc[i_cut];
    if(DEBUG_FFMPEG)all_mp3_file+="'\n";
  }
  //command="yes | "+str_ffmpeg_head+all_mp3_file+str_ffmpeg_end;
  //cout<<command<<endl;
  //system(command.c_str());
  system("rm tmp_ffmpeg_mix.txt");
  string command_2="echo \""+all_mp3_file+"\" >> tmp_ffmpeg_mix.txt";
  cout<<command_2<<endl;
  system(command_2.c_str());
  system("yes | ffmpeg -f concat -i tmp_ffmpeg_mix.txt -c copy output.mp3");

  //for test
  system("yes | cp output.mp3 ~/car_pi/output.mp3");
  //system("git add -A");
  //system("git commit -m \"auto up mp3\"");
  //system("git push");
}
