console.log("start index.js");//comment
$(document).ready(function(){//YOUR CODE HERE
  window.onload = function(){
  'use strict';
  console.log("document ready");
  
  console.log("load header.js");
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
                //console.log(allText);
                return allText;
            }
        }
    }
    console.log(rawFile.onreadystatechange);
    rawFile.send(null);
}
var theDiv = document.getElementById("headerJS");
console.log(readTextFile("https://raw.githubusercontent.com/andythebreaker/car_pi/gh-pages/header.html"));
var content = document.createTextNode(readTextFile("https://raw.githubusercontent.com/andythebreaker/car_pi/gh-pages/header.html"));
theDiv.appendChild(content);
console.log("end header.js");
  };});
