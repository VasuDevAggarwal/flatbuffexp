========================================================
STEPS TO FOLLOW FOR COMPILATION
========================================================

1. open the soln file in VS2017(or above might also work), and go to [Build->Build Solution] to build the solution
[flatbuffer is a header only dependency and has been included with the pkg]
[the schema is available under the fb_schemas folder and has been compiled using: flatc.exe --cpp --scoped-enums <PATH_TO_SCHEMA_FILE>]

2. cd to the folder where the compiled binaries present: [$SolutionDIr/$Platform/$BuildConfiguration] and use them as specfied below:
fb_encoder <PATH_TO_BINARY_FILE>
fb_decoder <PATH_TO_BINARY_FILE>
