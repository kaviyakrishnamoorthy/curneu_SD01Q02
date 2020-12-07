
#include <cstdio>
#include <string>
#include <iostream>
#include "unzip.h" // MiniZip library
 
#define WRITEBUFFERSIZE (5242880) 
 
using namespace std;
 
string readZipFile(string zipFile, string fileInZip) {
    int err = UNZ_OK;                 // error status
    uInt size_buf = WRITEBUFFERSIZE;  // byte size of buffer to store raw csv data
    void* buf;                        // the buffer  
    string sout;                      // output strings
    char filename_inzip[256];         // for unzGetCurrentFileInfo
    unz_file_info file_info;          // for unzGetCurrentFileInfo   
 
    unzFile uf = unzOpen(zipFile.c_str()); // open zipfile stream
    if (uf==NULL) {
        cerr << "Cannot open " << zipFile << endl;
        return sout;
    } // file is open
 
    if ( unzLocateFile(uf,fileInZip.c_str(),1) ) { // try to locate file inside zip
        // second argument of unzLocateFile: 1 = case sensitive, 0 = case-insensitive
        cerr << "File " << fileInZip << " not found in " << zipFile << endl;
        return sout;
    } // file inside zip found
 
    if (unzGetCurrentFileInfo(uf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0)) {
        cerr << "Error " << err << " with zipfile " << zipFile << " in unzGetCurrentFileInfo." << endl;
        return sout;
    } // obtained the necessary details about file inside zip
 
    buf = (void*)malloc(size_buf); // setup buffer
    if (buf==NULL) {
        cerr << "Error allocating memory for read buffer" << endl;
        return sout;
    } // buffer ready
 
    err = unzOpenCurrentFilePassword(uf,NULL); // Open the file inside the zip (password = NULL)
    if (err!=UNZ_OK) {
        cerr << "Error " << err << " with zipfile " << zipFile << " in unzOpenCurrentFilePassword." << endl;
        return sout;
    } // file inside the zip is open
 
    // Copy contents of the file inside the zip to the buffer
    cout << "Extracting: " << filename_inzip << " from " << zipFile << endl;
    do {
        err = unzReadCurrentFile(uf,buf,size_buf);
        if (err<0) {
            cerr << "Error " << err << " with zipfile " << zipFile << " in unzReadCurrentFile" << endl;
            sout = ""; // empty output string
            break;
        }
        // copy the buffer to a string
        if (err>0) for (int i = 0; i < (int) err; i++) sout.push_back( *(((char*)buf)+i) );
    } while (err>0);
 
    err = unzCloseCurrentFile (uf);  // close the zipfile
    if (err!=UNZ_OK) {
            cerr << "Error " << err << " with zipfile " << zipFile << " in unzCloseCurrentFile" << endl;
            sout = ""; // empty output string
        }
 
    free(buf); // free up buffer memory
    return sout;
}
 
int main(int argc, char *argv[]) {
    string string_buffer = readZipFile("test.zip", "testfile.txt");
    cout << string_buffer << endl;
    return 0;
}