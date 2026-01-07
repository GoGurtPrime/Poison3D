# Internal Tools

This folder contains tools build to support the development of
games using this engine.

## ttf-to-bmp

This tool is used to extract characters from a TTF font file
and rasterize them to bitmap (.bmp) image files. These 
bitmap files may then be used for rendering text within the
engine.

Currently I have only been able to use these bitmaps using
the Windows build, as some functions for drawing pixels
and specifying drawing positions with libdragon's GL
implementation are not supported. I have not yet tried 
this using Dreamcast.
