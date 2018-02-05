#include <tfs.h>

static const unsigned char data_header_jpg[] = {
    /* /header.jpg */
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 
    0x41, 0x42, 0x43, 0x44, 0x45, 0x46 };

static const unsigned char data_index_html[] = {
    /* /index.html */
    0x3c, 0x48, 0x54, 0x4d, 0x4c, 0x3e, 0x0d, 0x0a, 0x3c, 0x2f, 
    0x48, 0x54, 0x4d, 0x4c, 0x3e };

static const unsigned char data_Readme_txt[] = {
    /* /Readme.txt */
    0x20, 0x48, 0x69, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21, 
    0x20, 0x49, 0x20, 0x61, 0x6d, 0x20, 0x54, 0x46, 0x53, 0x20, 
    0x66, 0x69, 0x6c, 0x65, 0x2e };

const TFS_DIR_ENTRY tfs_data[] = {
    { "/header.jpg", 0, (unsigned char*)data_header_jpg, sizeof(data_header_jpg) },
    { "/index.html", 0, (unsigned char*)data_index_html, sizeof(data_index_html) },
    { "/Readme.txt", 0, (unsigned char*)data_Readme_txt, sizeof(data_Readme_txt) },
    { 0, 0, 0, 0 }
};
