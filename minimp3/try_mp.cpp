#define MINIMP3_IMPLEMENTATION
#include "minimp3_ex.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

int decode_mp3_file(string str_in);
int read_mp3_ng();
int main(){
  read_mp3_ng();
  return 0;
}
int read_mp3_ng(){
  cout<<"mini_mp3_try"<<endl;
  string filename1="nv1.mp3";
  string filename2="kuan1.mp3";
  decode_mp3_file(filename2);
  decode_mp3_file(filename1);
  cout<<"end_of_mini_mp3_try"<<endl;

  int wtf=0;
  //for(wtf=0;wtf<10;wtf++){
    mp3dec_ex_t dec2;
    cout<<"=================="<<endl;
    cout<<mp3dec_ex_open(&dec2,filename1.c_str(),MP3D_SEEK_TO_SAMPLE)<<endl;
    cout<<mp3dec_ex_seek(&dec2,wtf)<<endl;
    cout<<dec2.samples<<endl;
    mp3d_sample_t *buffer2 = (mp3d_sample_t*)malloc((int)dec2.samples*sizeof(mp3d_sample_t));
    size_t readed = mp3dec_ex_read(&dec2,buffer2,dec2.samples);
    cout<<"readed="<<readed<<" | dec2.samples="<<dec2.samples<<endl;
    cout<<dec2.last_error<<endl;
    cout<<"==="<<endl;
  //}
  ofstream myfile;
  myfile.open("haha.csv",ios_base::app);
  
  for(wtf=0;wtf<(int)readed;wtf++){
    myfile<<", "<<buffer2[wtf];
  }
  myfile.close();
  cout<<endl;

  return 0;
}

int decode_mp3_file(string str_in){
  static mp3dec_t mp3d;
  mp3dec_init(&mp3d);
  
  //bin in file
  string filename=str_in;
  ifstream in(filename, ios::in | ios::binary);
  if(!in){
    cout<<"can't read file"<<endl;
    return 1;
  }
  char ch;
  //print bin
  int ifvisual=0;
  int count=0;
  vector<unsigned char> input_buf_v;
  while(!in.eof()){
    in.get(ch);
    if(ifvisual)cout<<hex<<static_cast<int>(ch);
    input_buf_v.push_back(static_cast<unsigned char>(ch));
    count++;
  }
  unsigned char* input_buf = &input_buf_v[0];
  int i=0;
  for(i=0;i<count;i++){
    if(ifvisual)cout<<static_cast<int>(input_buf[i]);
  }
  /*char input_buf1[count]={""};
  int count2=0;
  while(!in.eof()){
    in.get(input_buf1[count2]);
    count2++;
  }
  unsigned char input_buf[count]={""};
  int i=0;
  cout<<endl<<"======================"<<endl;
  for(i=0;i<count;i++){
    input_buf[i]=static_cast<unsigned char>(input_buf1[i]);
    cout<<static_cast<int>(input_buf[i]);
  }
*/

  mp3dec_frame_info_t info;
  short pcm[MINIMP3_MAX_SAMPLES_PER_FRAME];
  auto samples=mp3dec_decode_frame(&mp3d,input_buf,count,pcm,&info);
  cout<</*endl<<*/"samples:"<<samples<<endl;
  cout<<"frame_bytes:"<<info.frame_bytes<<endl<<"channels:"<<info.channels<<endl<<"hz:"<<info.hz<<endl<<"layer:"<<info.layer<<endl<<"bitrate_kbps:"<<info.bitrate_kbps<<endl;
  int visualpcm=0;
  if(visualpcm){
    cout<<"========================="<<endl;
    int bit_i=0;
    for(bit_i=0;bit_i<(int)(sizeof(pcm)/sizeof(pcm[0]));bit_i++){
      cout<<pcm[bit_i];
    }
  }
  return 0;
}
