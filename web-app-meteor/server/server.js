var exec = Npm.require('child_process').exec;
//FS.debug = true;
//var sudo = Npm.require('sudo');
var projPath = "/home/pi/ESE-519-Project/bin"

Meteor.methods({
  'playGIF': function(fileName, duration_ms) {
  var imgPath = projPath + "/images/" + fileName;
  var execPath = projPath + "/playGIF";
  var command = execPath + " " + imgPath + " " + duration_ms
  exec(command,  function(error, stdout, stderr) {
    //console.log("stdout: " + stdout);
    //console.log("stderr: " + stderr);
    if(error !== null) {
      console.log("exec error: " + error);
    }
  });
  }
});

Images.allow({
 insert: function(){
 return true;
 },
 update: function(){
 return false;
 },
 remove: function(){
 return false;
 },
 download: function(){
 return false;
 }
});
