Template.playGifTemplate.events( {
  'click button': function(event) {
    event.preventDefault();
    var duration_ms = document.getElementById("durationText").value;
    var files = document.getElementById("imgFile").files;
    Images.insert(files[0], function (err, fileObj) { //only accept one image
      // Inserted new doc with ID fileObj._id, and kicked off the data upload using HTTP  
      var filePath = imagesPath + "/" + fileObj.collectionName + 
                     "-" + fileObj._id + "-" + fileObj.name();
      Meteor.call('playGIF', filePath, duration_ms);
    });

  }
});


