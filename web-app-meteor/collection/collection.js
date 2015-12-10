imagesPath = "~/ESE-519-Project/bin/images"
var imageStore = new FS.Store.FileSystem("images", {path: imagesPath} );

Images = new FS.Collection("images", {
  stores: [imageStore]
});

