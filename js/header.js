console.log("load header.js");
var fs = require('fs'); 
var data = fs.readFileSync('../header.html', 'utf8');
console.log(data);
