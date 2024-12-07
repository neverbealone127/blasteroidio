// incomplete!!!

var http = require('http');
var path = require('path');
var fs = require('fs');

var httpServer = http.createServer(function(req, res) {
  if (req.url === '/' || req.url === '/index') {
    
  }
})

function serverStaticFile(filePath, res) {
  fs.readFile(filePath, function(err, data) {
    if (err) {
      throw err;
    }
  })
}
