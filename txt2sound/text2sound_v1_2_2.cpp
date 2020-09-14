//TODO:
/*
https://openhome.cc/Gossip/CppGossip/BinaryFileIO.html
*/

//What files need to be included to work
/*
    using .h github.com/yhirose/cpp-httplib
    using .h github.com/sheredom/json.h
    using for test :: kuan1.mp3, minimp3.h, minimp3_ex.h, nv1.mp3
    ref: https://github.com/lieff/minimp3
    ref: https://docs.zhconvert.org/api/convert/
    ref: https://github.com/EarlySpringCommitee/HowHow-parser
*/

//include
#define MINIMP3_IMPLEMENTATION //minimp3/try_mp.cpp
#include "minimp3_ex.h"        //minimp3/try_mp.cpp
#include <fstream>             //minimp3/try_mp.cpp
#include <iomanip>             //minimp3/try_mp.cpp
#include <string>              //v0.0.1
#include <iostream>            //v0.0.1
#include <fstream>             //v0.0.1
#include <stdlib.h>            //v0.0.1
#include <sstream>             //v0.0.1
#include <dirent.h>            //getdir
#include <errno.h>             //getdir
#include <vector>              //getdir
#include "httplib.h"           //wget_json.cpp
#include "json.h"              //wget_json.cpp
#include <algorithm>           //std::find

//define
#define DEBUG_PART01 0      //v0.0.1
#define DEBUG_CUT_PINGING 0 //v0.0.1
#define PRINT_LIST 0        //v0.0.1
#define DEBUG12 0           //v0.0.1
#define DEBUG_FFMPEG 1      //v0.0.1
#define OLD_API_GET 0
#define OLD_MP3_LIB 0
#define THIS_IS_A_TRY_FUNCTION 0

using namespace std;

//Global variable
int FileInit();
int getdir(string dir, vector<string> &files);                 //getdir
string pig_get_parse(string in_str, int ifvisual);             //wget_json.cpp
int decode_mp3_file(string str_in);                            //minimp3/try_mp.cpp
int read_mp3_ng();                                             //minimp3/try_mp.cpp
const string place_of_mp3_lib1 = "HowHow-parser/result/mp3/1"; //old
const string place_of_mp3_lib2 = "HowHow-parser/result/mp3/2"; //old
vector<string> files1 = vector<string>();
vector<string> files2 = vector<string>();
string command = ""; //RM this line if define OLD==1

//main
int main(int argc, char *argv[])
{
    //init
    FileInit();
    if (THIS_IS_A_TRY_FUNCTION)
    {
        read_mp3_ng();
    }

    //const string
    const string str_mp3 = ".mp3";
    const string place_of_mp3_lib = "HowHow-parser/result/mp3";
    const string str_mp3_place1 = "/1";
    const string str_mp3_place2 = "/2";
    const string str_wget = "wget ";
    const string str_http = "http://";
    const string srt_api = "api.zhconvert.org/";
    const string str_convert = "convert?";
    const string str_parameter_converter = "converter=";
    const string str_pinying = "Pinyin";
    const string str_parameter_text = "&text=";
    const string str_parameter_prettify = "&prettify=1";
    const string str_file_out_O = " -O ";
    const string str_file_out_name = "zh2pinging_tmp.txt";
    const string str_file_out = str_file_out_O + str_file_out_name;
    const string str_dir = "dir ";
    const string str_dir_list_text_1 = "tmp_dir_mp3_lib_list_1.txt";
    const string str_dir_list_text_2 = "tmp_dir_mp3_lib_list_2.txt";
    const string str_out_to_text = " > ";
    const string str_out_to_text_1 = str_out_to_text + str_dir_list_text_1;
    const string str_out_to_text_2 = str_out_to_text + str_dir_list_text_2;

    //no use or old const string
    if (DEBUG_FFMPEG == 0)
    {
        const string str_ffmpeg_head = "ffmpeg";
    }
    if (DEBUG_FFMPEG == 0)
    {
        const string str_ffmpeg_end = " -filter_complex [0:a][1:a]concat=n=2:v=0:a=1 output.mp3";
    }

    //char/string
    char ch;
    string file_res = "";
    //string txt = "引擎轉速為二十公尺每秒";
    string txt = argv[1];

    //api down
    if (OLD_API_GET)
    {
        cout << "start" << endl;
        string command = str_wget + "\'" + str_http + srt_api + str_convert + str_parameter_converter + str_pinying + str_parameter_text + txt + str_parameter_prettify + "\'" + str_file_out;
        system(command.c_str());
        ifstream tmp_fin;
        tmp_fin.open(str_file_out_name);
        if (!tmp_fin)
        {
            cout << "api download error!" << endl;
            return 1;
        }
        else
        {
            while (!tmp_fin.eof())
            {
                tmp_fin.get(ch);
                file_res += ch;
            }
        }
        cout << file_res;
        tmp_fin.close();
        if (DEBUG_PART01)
            cout << "\nFOUND(data)@" << file_res.find("data") << endl;
        if ((file_res.find("data") != string::npos) && (file_res.find("text") != string::npos) && (file_res.find("data") < file_res.find("text")))
        {
            if (DEBUG_PART01)
                cout << "OK" << endl;
        }
        else
        {
            cout << "phase error!" << endl;
            return 1;
        }
        int st = (int)file_res.find("\"", 1 + file_res.find("\"", file_res.find("text")));
        int ed = (int)file_res.find("\"", 1 + file_res.find("\"", 1 + file_res.find("\"", file_res.find("text"))));
        if (DEBUG_PART01)
            cout << st << endl
                 << ed - st << endl
                 << file_res.substr(st + 1, ed - st - 1);
        string response = file_res.substr(st + 1, ed - st - 1);
        cout << endl
             << "========GOT answer========" << endl
             << txt << " = " << response << endl
             << "==========================" << endl;
    }
    //new api get
    string response = pig_get_parse(txt, 0);

    //check mp3 lib
    if (OLD_MP3_LIB)
    {
        command = "";
        command = str_dir + place_of_mp3_lib + str_mp3_place1 + str_out_to_text_1;
        system(command.c_str());
        command = str_dir + place_of_mp3_lib + str_mp3_place2 + str_out_to_text_2;
        system(command.c_str());
        string list_mp3_lib_1 = "";
        string list_mp3_lib_2 = "";
        ifstream list_mp3_lib1;
        ifstream list_mp3_lib2;
        list_mp3_lib1.open(str_dir_list_text_1);
        list_mp3_lib2.open(str_dir_list_text_2);
        if (!list_mp3_lib1)
        {
            cout << "mp3 lib 1 open error!" << endl;
            return 1;
        }
        else
        {
            while (!list_mp3_lib1.eof())
            {
                list_mp3_lib1.get(ch);
                list_mp3_lib_1 += ch;
            }
        }
        if (!list_mp3_lib2)
        {
            cout << "mp3 lib 2 open error!" << endl;
            return 1;
        }
        else
        {
            while (!list_mp3_lib2.eof())
            {
                list_mp3_lib2.get(ch);
                list_mp3_lib_2 += ch;
            }
        }
        if (PRINT_LIST)
            cout << "=====mp3 lib 1=====" << endl
                 << list_mp3_lib_1 << endl
                 << "=====mp3 lib 2=====" << endl
                 << list_mp3_lib_2 << endl;
        list_mp3_lib1.close();
        list_mp3_lib2.close();
    }

    //cut target pinging
    int how_meny_word = 0;
    int i_check_how_much_word = 0;
    for (i_check_how_much_word = 0; i_check_how_much_word < response.length(); i_check_how_much_word++)
    {
        char tmp_ch = response[i_check_how_much_word];
        if (tmp_ch == ' ')
        {
            how_meny_word++;
        }
    }
    how_meny_word++;
    string str2ary = response;
    int i_cut = 0;
    string arr[how_meny_word];
    stringstream ssin(str2ary);
    while (ssin.good() && i_cut < how_meny_word)
    {
        ssin >> arr[i_cut];
        ++i_cut;
    }
    if (DEBUG_CUT_PINGING)
    {
        for (i_cut = 0; i_cut < how_meny_word; i_cut++)
        {
            cout << arr[i_cut] << endl;
        }
    }
    int pinging_mp3_loc[how_meny_word] = {0};
    for (i_cut = 0; i_cut < how_meny_word; i_cut++)
    {
        pinging_mp3_loc[i_cut] = (std::find(files1.begin(), files1.end(), arr[i_cut] + ".mp3") != files1.end()) ? 1 : 0; //new
        if (pinging_mp3_loc[i_cut] == 0)
            pinging_mp3_loc[i_cut] = (std::find(files2.begin(), files2.end(), arr[i_cut] + ".mp3") != files2.end()) ? 2 : 0; //new
    }
    int check_no_mp3 = -1;
    for (i_cut = 0; i_cut < how_meny_word; i_cut++)
    {
        cout << "mp3 loc folder (1/2): " << pinging_mp3_loc[i_cut] << endl;
        check_no_mp3 *= pinging_mp3_loc[i_cut];
    }
    if (check_no_mp3 == 0)
    {
        cout << "ERROR, some word don't have mp3 file." << endl;
        if (DEBUG12 == 0)
            return 1;
        if (DEBUG12)
            cout << "DEBUG12 is on, do _2_ anyway" << endl;
    }
    string real_mp3_loc[how_meny_word] = {""};
    for (i_cut = 0; i_cut < how_meny_word; i_cut++)
    {
        if (DEBUG12 == 0)
        {
            if (pinging_mp3_loc[i_cut] == 1)
            {
                real_mp3_loc[i_cut] += place_of_mp3_lib;
                real_mp3_loc[i_cut] += str_mp3_place1;
            }
            else if (pinging_mp3_loc[i_cut] == 2)
            {
                real_mp3_loc[i_cut] += place_of_mp3_lib;
                real_mp3_loc[i_cut] += str_mp3_place2;
            }
            else
            {
                cout << "ERROR!(no word mp3)" << endl;
                return 1;
            }
        }
        if (DEBUG12)
            real_mp3_loc[i_cut] += place_of_mp3_lib;
        if (DEBUG12)
            real_mp3_loc[i_cut] += str_mp3_place2;
        real_mp3_loc[i_cut] += "/";
        real_mp3_loc[i_cut] += arr[i_cut];
        real_mp3_loc[i_cut] += str_mp3;
    }
    string all_mp3_file = "";
    for (i_cut = 0; i_cut < how_meny_word; i_cut++)
    {
        //if(i_cut!=0)all_mp3_file+="|";
        if (DEBUG_FFMPEG)
        {
            if (i_cut == 0)
            {
                all_mp3_file += "#\n";
            }
        };
        if (DEBUG_FFMPEG == 0)
            all_mp3_file += " -i ";
        if (DEBUG_FFMPEG)
            all_mp3_file += "file '";
        all_mp3_file += real_mp3_loc[i_cut];
        if (DEBUG_FFMPEG)
            all_mp3_file += "'\n";
    }
    //command="yes | "+str_ffmpeg_head+all_mp3_file+str_ffmpeg_end;
    //cout<<command<<endl;
    //system(command.c_str());
    system("rm tmp_ffmpeg_mix.txt");
    string command_2 = "echo \"" + all_mp3_file + "\" >> tmp_ffmpeg_mix.txt";
    cout << command_2 << endl;
    system(command_2.c_str());
    system("yes | ffmpeg -f concat -i tmp_ffmpeg_mix.txt -c copy output.mp3");
    
    //ffmpeg play
    string do_you_want_to_play_it_out=argv[2];
    if(do_you_want_to_play_it_out.compare("1")==0){
      system("ffplay -autoexit output.mp3");
    }
}
//========================END OF MAIN======================================================

//car_pi/clean_code/wget_json.cpp
string pig_get_parse(string in_str, int ifvisual)
{
    //const
    string str_data = "data";
    string str_text = "text";
    int http_port = 80;
    string str_url = "api.zhconvert.org";
    string str_get1 = "/convert?converter=Pinyin&text=";
    string str_get2 = "&prettify=1";
    int i = 0; //loop
    int j = 0; //loop
    string wget = "";
    string str_get = str_get1 + in_str + str_get2;

    //http get
    //httplib::Client cli("api.zhconvert.org",80);
    //make client
    httplib::Client cli(str_url, http_port);

    //get
    //auto res = cli.Get("/convert?converter=Pinyin&text=這是一格測試的請求&prettify=1");
    auto res = cli.Get(str_get.c_str());
    if (res && res->status == 200)
    {
        wget = res->body;
        if (ifvisual == 1)
            cout << wget.c_str() << endl;
        //cout<<res->body<<endl;
    }

    //parse json
    if (ifvisual == 1)
        cout << "=====josn=====" << endl;
    string target_ans = "";
    string inside_data = "";
    struct json_value_s *json_root = json_parse(wget.c_str(), strlen(wget.c_str()));
    struct json_object_s *json_obj = json_value_as_object(json_root);
    assert(json_obj != NULL); //stop and print code if statement is true
    if (ifvisual == 1)
        cout << "json length = " << json_obj->length << endl;
    if (ifvisual == 1)
        cout << "top layer :{" << endl;
    struct json_object_element_s *elem_tmp = json_obj->start;
    if (ifvisual == 1)
        cout << "    " << elem_tmp->name->string << endl;
    //top layer
    for (i = 0; i < json_obj->length - 1; i++)
    {
        elem_tmp = elem_tmp->next;
        if (ifvisual == 1)
            cout << "    " << elem_tmp->name->string << endl;
        if (strncmp(elem_tmp->name->string, str_data.c_str(), strlen(str_data.c_str())) == 0)
        { //compare if elem name == "data" , using "strncmp" to compare the first 4 char is/or not the same, return 0 if true
            struct json_object_element_s *elem_inside_data = json_value_as_object(elem_tmp->value)->start;
            inside_data += elem_inside_data->name->string;
            inside_data += "\n";
            //inside data
            for (j = 0; j < json_value_as_object(elem_tmp->value)->length - 1; j++)
            {
                elem_inside_data = elem_inside_data->next;
                inside_data += elem_inside_data->name->string;
                /*if(j<json_value_as_object(elem_tmp->value)->length-2)*/ inside_data += "\n";
                if ((strncmp(elem_inside_data->name->string, str_text.c_str(), strlen(str_text.c_str())) == 0) && (elem_inside_data->name->string_size == strlen(str_text.c_str())))
                {
                    target_ans = json_value_as_string(elem_inside_data->value)->string;
                }
            }
        }
    }
    if (ifvisual == 1)
        cout << "}" << endl;
    free(json_root);
    if (ifvisual == 1)
        cout << "inside \"data\" have these element :{\n"
             << inside_data << /*"\n}"*/ "}" << endl;
    if (ifvisual == 1)
        cout << "target = " << target_ans << endl;
    return target_ans;
}
//mini_mp3_try
int read_mp3_ng()
{
    cout << "mini_mp3_try" << endl;
    string filename1 = "nv1.mp3";
    string filename2 = "kuan1.mp3";
    decode_mp3_file(filename2);
    decode_mp3_file(filename1);
    cout << "end_of_mini_mp3_try" << endl;

    int wtf = 0;
    //for(wtf=0;wtf<10;wtf++){
    mp3dec_ex_t dec2;
    cout << "==================" << endl;
    cout << mp3dec_ex_open(&dec2, filename1.c_str(), MP3D_SEEK_TO_SAMPLE) << endl;
    cout << mp3dec_ex_seek(&dec2, wtf) << endl;
    cout << dec2.samples << endl;
    mp3d_sample_t *buffer2 = (mp3d_sample_t *)malloc((int)dec2.samples * sizeof(mp3d_sample_t));
    size_t readed = mp3dec_ex_read(&dec2, buffer2, dec2.samples);
    cout << "readed=" << readed << " | dec2.samples=" << dec2.samples << endl;
    cout << dec2.last_error << endl;
    cout << "===" << endl;
    //}
    ofstream myfile;
    myfile.open("haha.csv", ios_base::app);

    for (wtf = 0; wtf < (int)readed; wtf++)
    {
        myfile << ", " << buffer2[wtf];
    }
    myfile.close();
    cout << endl;

    return 0;
}

int decode_mp3_file(string str_in)
{
    static mp3dec_t mp3d;
    mp3dec_init(&mp3d);

    //bin in file
    string filename = str_in;
    ifstream in(filename, ios::in | ios::binary);
    if (!in)
    {
        cout << "can't read file" << endl;
        return 1;
    }
    char ch;
    //print bin
    int ifvisual = 0;
    int count = 0;
    vector<unsigned char> input_buf_v;
    while (!in.eof())
    {
        in.get(ch);
        if (ifvisual)
            cout << hex << static_cast<int>(ch);
        input_buf_v.push_back(static_cast<unsigned char>(ch));
        count++;
    }
    unsigned char *input_buf = &input_buf_v[0];
    int i = 0;
    for (i = 0; i < count; i++)
    {
        if (ifvisual)
            cout << static_cast<int>(input_buf[i]);
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
    auto samples = mp3dec_decode_frame(&mp3d, input_buf, count, pcm, &info);
    cout << /*endl<<*/ "samples:" << samples << endl;
    cout << "frame_bytes:" << info.frame_bytes << endl
         << "channels:" << info.channels << endl
         << "hz:" << info.hz << endl
         << "layer:" << info.layer << endl
         << "bitrate_kbps:" << info.bitrate_kbps << endl;
    int visualpcm = 0;
    if (visualpcm)
    {
        cout << "=========================" << endl;
        int bit_i = 0;
        for (bit_i = 0; bit_i < (int)(sizeof(pcm) / sizeof(pcm[0])); bit_i++)
        {
            cout << pcm[bit_i];
        }
    }
    return 0;
}

//getdir
int getdir(string dir, vector<string> &files)
{
    DIR *dp; //dir pointer
    struct dirent *dirp;
    if ((dp = opendir(dir.c_str())) == NULL)
    {
        cout << "ERROR(" << errno << ") opening " << dir << endl;
        return errno;
    }
    while ((dirp = readdir(dp)) != NULL)
    {
        //if dir pointer != null
        files.push_back(string(dirp->d_name)); //put dir & file name into vector
    }
    closedir(dp);
    return 0;
}

int FileInit()
{
    //string dir = ".";
    //vector<string> files = vector<string>();
    getdir(place_of_mp3_lib1, files1);
    int i_ = 0;
    for (i_ = 0; i_ < files1.size(); i_++)
    {
        cout << files1[i_] << endl;
    }
    getdir(place_of_mp3_lib2, files2);

    for (i_ = 0; i_ < files2.size(); i_++)
    {
        cout << files2[i_] << endl;
    }
    return 0;
}
