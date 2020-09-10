//const url=require('url');
function main_get(){
  var http, server, url;
  http=require('http');
  url=require('url');
  server=http.createServer(function(req, res){
    var action,urlData,user_data;
    urlData=url.parse(req.url, true);
    action=urlData.pathname;
    res.writeHead(200,{
      "Content-Type":"text/html"
    });
    if (action==="/anything"){
      user_data=urlData.query;
       const fs=require('fs');
      fs.appendFile('car_data.html',"<tr><td>"+user_data.user+"</td><td>"+user_data.RPM+"</td><td>"+new Date()+"</td></tr>",function(err){
        if (err) {
          console.log("can't save");
          throw err;
        }
        console.log('Saved!');
      });

      return res.end("<h1>"+user_data.user+"</h1>"+"<h1>"+user_data.RPM+"</h1>");
     }else if(action==="/data"){
       console.log("txt out!");
      const fs_exp=require('fs');
       const exp_send=fs_exp.readFileSync('car_data.html','utf-8');
       res.write(exp_send);
       return res.end();
       
     }else if(action==="/index"){
console.log("index ->");
      const fs_id=require('fs');
       const id_send=fs_id.readFileSync('views/index.html','utf-8');
       res.write(id_send);
       return res.end();
 
     }
  });
  server.listen(10087);
  console.log('going...'+new Date());
}
main_get();
/*
console.log("move on 2 ->");
const express =require('express');
const app=express();
const http_srv =require('http').Server(app);
const port=process.env.PORT||13087;
app.get('',(req_http,res_http)=>{
  //url_t=require('url');
  //var spliter = url_t.parse(req_http.url,true).pathname;
  //console.log(spliter);
  //if(spliter==="/js"){
    //res_http.sendFile(__dirname+'/http_js/header.js');
  //}else{
    res_http.sendFile(__dirname+'/views/index.html');
  //}
});

http_srv.listen(port,()=>{
  console.log("http_srv on!");
});
*/
