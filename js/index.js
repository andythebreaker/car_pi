console.log("start index.js");//comment
$(document).ready(function(){//YOUR CODE HERE
  window.onload = function(){
  'use strict';
  console.log("document ready");
  
  console.log("load header.js");
  var glob="";
  function readTextFile(file)
  {
    var rawFile = new XMLHttpRequest();
    rawFile.open("GET", file, false);
    rawFile.onreadystatechange = function ()
    {
        if(rawFile.readyState === 4)
        {
            if(rawFile.status === 200 || rawFile.status == 0)
            {
                var allText = rawFile.responseText;
                glob=allText;
                //console.log(allText);
            }
        }
    }
    rawFile.send(null);
}
var theDiv = document.getElementById("headerJS");
readTextFile("https://raw.githubusercontent.com/andythebreaker/car_pi/gh-pages/header.html");
console.log(glob);
//var content=document.createTextNode(glob);
//theDiv.appendChild(content);
theDiv.insertAdjacentHTML( 'beforeend', glob );
//$(glob).appendTo( "header" );
console.log("end header.js");
  };
});
