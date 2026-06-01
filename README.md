# File Compressor

The compressor program is a file compressor which compresses a txt file using huffman coding and the decompressor program decompresses the compressed file back to its original form.

## Installation and User Guide
1) Run the command given below in your terminal:
git clone https://github.com/Tejas007bond/File-Compressor.git

2) After cloning the repository open the compressor.cpp file and locate to line 69 and type your desired  filename.

NOTE :- The txt and file and the compressor file should be in the same folder.
NOTE :- Right now the compression supports only txt files.

3) Run the commands given below in you terminal:

g++ compressor.cpp -o compressor
compressor.exe

These commands will give you your output bin file

3) After compression send the bin file and on the reciever computer save the decompressor file and the bin file in the same folder and run the commands given below in your terminal:

g++ decompressor.cpp -o decompressor
decompressor.exe

The above commands will give the restored text file back.