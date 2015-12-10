var spawn = Npm.require('child_process').spawn;
//FS.debug = true;

Meteor.methods({
  'playGIF': function(filePath, duration_ms) {
  spawn('playGIF', [filePath, duration_ms]);
  /*console.log(filePath);*/
  /*console.log(duration_ms);*/
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
