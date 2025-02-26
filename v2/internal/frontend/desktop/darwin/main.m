//go:build ignore
//  main.m
//  test
//
//  Created by Lea Anthony on 10/10/21.
//

// ****** This file is used for testing purposes only ******

#import <Foundation/Foundation.h>
#import "Application.h"

void processMessage(const char*t) {
    NSLog(@"processMessage called");
}

void processMessageDialogResponse(int t) {
    NSLog(@"processMessage called");
}

void processOpenFileDialogResponse(const char *t) {
    NSLog(@"processMessage called %s", t);
}
void processSaveFileDialogResponse(const char *t) {
    NSLog(@"processMessage called %s", t);
}
 
void processCallback(int callbackID) {
    NSLog(@"Process callback %d", callbackID);
}

void processURLRequest(void *ctx, const char* url) {
    NSLog(@"processURLRequest called");
    const char myByteArray[] = { 0x3c,0x68,0x31,0x3e,0x48,0x65,0x6c,0x6c,0x6f,0x20,0x57,0x6f,0x72,0x6c,0x64,0x21,0x3c,0x2f,0x68,0x31,0x3e };
    ProcessURLResponse(ctx, url, "text/html", (void*)myByteArray, 21);
}

unsigned char _Users_username_Pictures_SaltBae_png[] = {

0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x14,
0x08, 0x06, 0x00, 0x00, 0x00, 0x8d, 0x89, 0x1d, 0x0d, 0x00, 0x00, 0x00,
0x04, 0x67, 0x41, 0x4d, 0x41, 0x00, 0x00, 0xb1, 0x8f, 0x0b, 0xfc, 0x61,
0x05, 0x00, 0x00, 0x00, 0x20, 0x63, 0x48, 0x52, 0x4d, 0x00, 0x00, 0x7a,
0x26, 0x00, 0x00, 0x80, 0x84, 0x00, 0x00, 0xfa, 0x00, 0x00, 0x00, 0x80,
0xe8, 0x00, 0x00, 0x75, 0x30, 0x00, 0x00, 0xea, 0x60, 0x00, 0x00, 0x3a,
0x98, 0x00, 0x00, 0x17, 0x70, 0x9c, 0xba, 0x51, 0x3c, 0x00, 0x00, 0x00,
0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x0b, 0x13, 0x00, 0x00, 0x0b,
0x13, 0x01, 0x00, 0x9a, 0x9c, 0x18, 0x00, 0x00, 0x01, 0xd5, 0x69, 0x54,
0x58, 0x74, 0x58, 0x4d, 0x4c, 0x3a, 0x63, 0x6f, 0x6d, 0x2e, 0x61, 0x64,
0x6f, 0x62, 0x65, 0x2e, 0x78, 0x6d, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
0x3c, 0x78, 0x3a, 0x78, 0x6d, 0x70, 0x6d, 0x65, 0x74, 0x61, 0x20, 0x78,
0x6d, 0x6c, 0x6e, 0x73, 0x3a, 0x78, 0x3d, 0x22, 0x61, 0x64, 0x6f, 0x62,
0x65, 0x3a, 0x6e, 0x73, 0x3a, 0x6d, 0x65, 0x74, 0x61, 0x2f, 0x22, 0x20,
0x78, 0x3a, 0x78, 0x6d, 0x70, 0x74, 0x6b, 0x3d, 0x22, 0x58, 0x4d, 0x50,
0x20, 0x43, 0x6f, 0x72, 0x65, 0x20, 0x35, 0x2e, 0x34, 0x2e, 0x30, 0x22,
0x3e, 0x0a, 0x20, 0x20, 0x20, 0x3c, 0x72, 0x64, 0x66, 0x3a, 0x52, 0x44,
0x46, 0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73, 0x3a, 0x72, 0x64, 0x66, 0x3d,
0x22, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e,
0x77, 0x33, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x31, 0x39, 0x39, 0x39, 0x2f,
0x30, 0x32, 0x2f, 0x32, 0x32, 0x2d, 0x72, 0x64, 0x66, 0x2d, 0x73, 0x79,
0x6e, 0x74, 0x61, 0x78, 0x2d, 0x6e, 0x73, 0x23, 0x22, 0x3e, 0x0a, 0x20,
0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x72, 0x64, 0x66, 0x3a, 0x44, 0x65,
0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x72, 0x64,
0x66, 0x3a, 0x61, 0x62, 0x6f, 0x75, 0x74, 0x3d, 0x22, 0x22, 0x0a, 0x20,
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x78,
0x6d, 0x6c, 0x6e, 0x73, 0x3a, 0x74, 0x69, 0x66, 0x66, 0x3d, 0x22, 0x68,
0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x6e, 0x73, 0x2e, 0x61, 0x64, 0x6f,
0x62, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x74, 0x69, 0x66, 0x66, 0x2f,
0x31, 0x2e, 0x30, 0x2f, 0x22, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x3c, 0x74, 0x69, 0x66, 0x66, 0x3a, 0x43, 0x6f,
0x6d, 0x70, 0x72, 0x65, 0x73, 0x73, 0x69, 0x6f, 0x6e, 0x3e, 0x31, 0x3c,
0x2f, 0x74, 0x69, 0x66, 0x66, 0x3a, 0x43, 0x6f, 0x6d, 0x70, 0x72, 0x65,
0x73, 0x73, 0x69, 0x6f, 0x6e, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x3c, 0x74, 0x69, 0x66, 0x66, 0x3a, 0x4f, 0x72,
0x69, 0x65, 0x6e, 0x74, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x3e, 0x31, 0x3c,
0x2f, 0x74, 0x69, 0x66, 0x66, 0x3a, 0x4f, 0x72, 0x69, 0x65, 0x6e, 0x74,
0x61, 0x74, 0x69, 0x6f, 0x6e, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x3c, 0x74, 0x69, 0x66, 0x66, 0x3a, 0x50, 0x68,
0x6f, 0x74, 0x6f, 0x6d, 0x65, 0x74, 0x72, 0x69, 0x63, 0x49, 0x6e, 0x74,
0x65, 0x72, 0x70, 0x72, 0x65, 0x74, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x3e,
0x32, 0x3c, 0x2f, 0x74, 0x69, 0x66, 0x66, 0x3a, 0x50, 0x68, 0x6f, 0x74,
0x6f, 0x6d, 0x65, 0x74, 0x72, 0x69, 0x63, 0x49, 0x6e, 0x74, 0x65, 0x72,
0x70, 0x72, 0x65, 0x74, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x3e, 0x0a, 0x20,
0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x2f, 0x72, 0x64, 0x66, 0x3a, 0x44,
0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x3e, 0x0a,
0x20, 0x20, 0x20, 0x3c, 0x2f, 0x72, 0x64, 0x66, 0x3a, 0x52, 0x44, 0x46,
0x3e, 0x0a, 0x3c, 0x2f, 0x78, 0x3a, 0x78, 0x6d, 0x70, 0x6d, 0x65, 0x74,
0x61, 0x3e, 0x0a, 0x02, 0xd8, 0x80, 0x05, 0x00, 0x00, 0x04, 0xdc, 0x49,
0x44, 0x41, 0x54, 0x38, 0x11, 0x1d, 0x94, 0x49, 0x6c, 0x1b, 0x65, 0x18,
0x86, 0x9f, 0x99, 0xf9, 0x67, 0xc6, 0x6b, 0xbc, 0x26, 0xce, 0xda, 0xa4,
0x25, 0x69, 0x0b, 0x2d, 0x28, 0x34, 0x2c, 0x95, 0x00, 0x89, 0x45, 0x08,
0x5a, 0x95, 0x03, 0x08, 0x09, 0x21, 0xe0, 0x80, 0x38, 0xc3, 0x85, 0x03,
0xe2, 0x00, 0x47, 0xc4, 0x1d, 0x38, 0x70, 0xe3, 0xc6, 0x01, 0x01, 0x42,
0x20, 0x54, 0x7a, 0x2a, 0x6b, 0x0b, 0x94, 0xd2, 0xd2, 0x25, 0x69, 0x9b,
0xa4, 0x0d, 0x2d, 0xa9, 0xb3, 0x78, 0x89, 0x9d, 0xf1, 0x2c, 0x9e, 0x85,
0x2f, 0xb5, 0x35, 0xb6, 0x35, 0x96, 0xde, 0x79, 0xdf, 0xef, 0x7f, 0x9f,
0x4f, 0xfb, 0xe0, 0xad, 0x37, 0x12, 0xfd, 0xf0, 0xb3, 0x9c, 0xfb, 0xb7,
0xc5, 0x8d, 0x46, 0x9b, 0x71, 0x5b, 0xf1, 0xd0, 0xf4, 0x18, 0xdb, 0xeb,
0x4b, 0x1c, 0xff, 0xf1, 0x57, 0x98, 0xdc, 0x87, 0x72, 0x3a, 0x8c, 0x3a,
0xcb, 0x8c, 0xea, 0x31, 0x35, 0xb7, 0xc3, 0x99, 0xba, 0xc3, 0xd7, 0xab,
0x3e, 0x87, 0x2a, 0x8a, 0xb3, 0xff, 0xdc, 0xe0, 0x9b, 0x8f, 0x5f, 0xa2,
0x1c, 0xc5, 0xfc, 0x72, 0xc9, 0x41, 0x99, 0x71, 0x48, 0xca, 0x84, 0x3c,
0x3e, 0xda, 0xd2, 0x05, 0x9a, 0xb1, 0xc7, 0x35, 0x67, 0x1c, 0xdd, 0x4c,
0x68, 0xeb, 0x26, 0xd9, 0x30, 0x26, 0x09, 0x23, 0x5c, 0x3f, 0xc2, 0xd3,
0x43, 0xc2, 0x24, 0x21, 0x4e, 0x34, 0x40, 0x27, 0x89, 0x13, 0xf9, 0x1e,
0x22, 0x6e, 0xd5, 0x45, 0x43, 0x63, 0xc6, 0xd2, 0x50, 0xa9, 0xc4, 0x67,
0x24, 0x15, 0x72, 0xa9, 0x7e, 0x95, 0xfa, 0x4f, 0x27, 0x78, 0x64, 0x76,
0x86, 0x23, 0x61, 0xc0, 0xf0, 0x58, 0x15, 0xc3, 0x29, 0x71, 0x06, 0x45,
0x2e, 0xa5, 0x48, 0xbb, 0x0a, 0x3d, 0x89, 0xa0, 0x8f, 0x08, 0x8a, 0x8e,
0x08, 0xbb, 0xc1, 0x8e, 0xb0, 0x8d, 0xdd, 0x0f, 0xc9, 0x84, 0x06, 0x65,
0x34, 0xf4, 0xed, 0x8d, 0xff, 0x58, 0xbd, 0xfc, 0x27, 0x17, 0x2f, 0x9e,
0xe3, 0xf0, 0x81, 0x49, 0x5e, 0xde, 0x5f, 0xe1, 0x9e, 0x82, 0xcd, 0xdc,
0x78, 0x8d, 0xd9, 0xb2, 0xc9, 0x56, 0x12, 0x32, 0x94, 0x4f, 0x91, 0xcb,
0x88, 0x68, 0xda, 0x42, 0x13, 0x77, 0x11, 0xa2, 0xa8, 0xc3, 0x5a, 0x5f,
0x46, 0x30, 0x65, 0x52, 0x29, 0xe4, 0x24, 0x4d, 0x8e, 0xcc, 0x68, 0x19,
0xe5, 0x76, 0xbb, 0xac, 0x5c, 0x98, 0xa7, 0xb3, 0xed, 0xd0, 0x37, 0x62,
0xa2, 0xb0, 0xc7, 0x89, 0xe5, 0x2e, 0x03, 0x0d, 0x97, 0x95, 0x46, 0x8f,
0x31, 0xd7, 0xa6, 0x63, 0x81, 0x65, 0x25, 0x84, 0xba, 0x45, 0x5f, 0x65,
0x31, 0x2c, 0x71, 0x6b, 0x77, 0x69, 0xf5, 0x7a, 0xbc, 0xb0, 0x3b, 0xcd,
0xf9, 0xa5, 0x90, 0xd1, 0xb0, 0xcd, 0xd4, 0xb0, 0xdc, 0xd7, 0xc4, 0xfa,
0xf0, 0x78, 0x95, 0x7b, 0x27, 0xab, 0x5c, 0x5e, 0x6e, 0xd2, 0xee, 0x05,
0xdc, 0xd8, 0xea, 0xf1, 0xf7, 0xe2, 0x1a, 0xc7, 0xee, 0x1a, 0x62, 0x2e,
0x1f, 0xe3, 0xe8, 0xb6, 0xc4, 0x4c, 0xd3, 0x6d, 0x6e, 0xd0, 0x6b, 0xfc,
0x4c, 0xe3, 0xd4, 0x1f, 0xc4, 0x4b, 0xf3, 0x1c, 0x2c, 0x65, 0x29, 0x67,
0x4d, 0xbe, 0xfb, 0xad, 0x45, 0x65, 0x0c, 0xea, 0x7e, 0x1f, 0x15, 0x6b,
0x09, 0x0b, 0x8b, 0xb7, 0x19, 0xc9, 0xa5, 0x78, 0x75, 0x6e, 0x18, 0xdf,
0xf5, 0x79, 0x72, 0xd0, 0xa2, 0x2d, 0xb3, 0x3a, 0xbb, 0xb4, 0x41, 0x3e,
0x53, 0xe6, 0xf4, 0xca, 0x3c, 0xa5, 0x7c, 0x86, 0xe9, 0xfd, 0x47, 0x18,
0x2e, 0xbd, 0xce, 0xd1, 0x97, 0x26, 0x78, 0xbc, 0x7e, 0x1d, 0xff, 0xcc,
0xa7, 0x5c, 0x71, 0x74, 0x16, 0xe3, 0x18, 0xd7, 0x1e, 0x23, 0xe8, 0xac,
0xa3, 0x0c, 0xcd, 0x60, 0x22, 0x6f, 0x43, 0x36, 0x43, 0x3b, 0x19, 0xc6,
0x08, 0x7a, 0xe0, 0x6c, 0xe3, 0x27, 0x8a, 0xdb, 0x4e, 0xc0, 0xd4, 0xa0,
0xcd, 0x27, 0xaf, 0xbd, 0xcb, 0x86, 0x36, 0xc6, 0xcc, 0xfe, 0x59, 0xd2,
0xca, 0x90, 0x93, 0x36, 0x70, 0xaf, 0x9c, 0xe4, 0xcb, 0x6f, 0x65, 0x54,
0xd9, 0x47, 0x59, 0x70, 0xbb, 0x74, 0x1b, 0x0e, 0x89, 0xe7, 0xa3, 0xc7,
0x12, 0x39, 0x63, 0xea, 0x68, 0x12, 0x6b, 0x53, 0x5c, 0x9e, 0xef, 0x76,
0xf0, 0x55, 0x86, 0x0d, 0x17, 0x56, 0x9a, 0x4d, 0x94, 0x95, 0x65, 0xe6,
0xbe, 0x67, 0x98, 0xbe, 0xfb, 0x21, 0x52, 0xd2, 0x43, 0xaf, 0x5d, 0x47,
0x6b, 0x5c, 0xa3, 0x59, 0xbf, 0xc2, 0x62, 0xdd, 0x26, 0xa5, 0x12, 0x6a,
0x41, 0x44, 0xdf, 0xbd, 0xcd, 0x92, 0x17, 0xa0, 0xb6, 0x03, 0x43, 0xba,
0x66, 0x91, 0xe9, 0xdc, 0xc2, 0xce, 0xed, 0xa1, 0xfc, 0xc0, 0x2b, 0x14,
0xff, 0xfd, 0x1e, 0x4b, 0xb3, 0xa9, 0x29, 0x87, 0x81, 0xd2, 0x04, 0x8e,
0x66, 0x89, 0x58, 0x00, 0x7e, 0x07, 0xaf, 0xdb, 0xa4, 0xbb, 0xb5, 0x49,
0xb9, 0xaa, 0x18, 0xb9, 0x77, 0x8e, 0xcd, 0xdb, 0x6d, 0x1e, 0x1c, 0xb5,
0x38, 0x7d, 0xa5, 0xcf, 0xaa, 0x08, 0xeb, 0x77, 0x3f, 0x35, 0xc7, 0xda,
0xfc, 0x02, 0xaa, 0xf6, 0x1c, 0xbb, 0x9f, 0x78, 0x9f, 0x89, 0x43, 0x47,
0xa4, 0x6f, 0x3d, 0x06, 0xed, 0x90, 0x92, 0x79, 0x95, 0xd4, 0xe4, 0xfd,
0x98, 0x66, 0x4a, 0x6a, 0xd7, 0xc7, 0x0b, 0x62, 0xa4, 0xe3, 0x8c, 0x4d,
0xc4, 0xe8, 0x85, 0x98, 0xe5, 0x46, 0x44, 0x26, 0x97, 0x21, 0xe9, 0xf7,
0xf9, 0x61, 0xc5, 0xe3, 0xd4, 0x66, 0x84, 0xd2, 0x70, 0xc9, 0xee, 0x79,
0x98, 0x43, 0xc7, 0x5e, 0x27, 0xb6, 0x8a, 0xd2, 0x5a, 0x1f, 0xf3, 0xa9,
0xf7, 0x88, 0xce, 0x7d, 0x85, 0x71, 0xe0, 0x79, 0x98, 0x7a, 0x90, 0x9e,
0x1b, 0xd0, 0x13, 0x52, 0x4a, 0x66, 0x97, 0x7d, 0x33, 0x1e, 0xed, 0xae,
0xc7, 0x87, 0x1f, 0x7d, 0xce, 0xc2, 0xd5, 0x3a, 0xe6, 0xde, 0x02, 0xcb,
0xdb, 0x3e, 0xbe, 0xa6, 0x91, 0x95, 0x62, 0x6b, 0x2f, 0xce, 0x90, 0x3c,
0xfd, 0xce, 0x71, 0x0e, 0xcc, 0x3e, 0x82, 0x13, 0xf4, 0x09, 0xd5, 0x00,
0x16, 0x82, 0x98, 0xb3, 0x49, 0x24, 0xb1, 0x83, 0xc8, 0xc0, 0xd6, 0x3a,
0x54, 0x33, 0xab, 0x14, 0x8c, 0x16, 0x4e, 0x38, 0xcc, 0xe5, 0xeb, 0x4d,
0x5e, 0x7b, 0xfb, 0x4d, 0xaa, 0x79, 0xa1, 0x45, 0x1c, 0x9b, 0xd2, 0x94,
0xcc, 0x0e, 0x8c, 0x52, 0x7a, 0x65, 0x17, 0xc7, 0xa9, 0x0c, 0x8e, 0xe2,
0xf7, 0xba, 0xa8, 0xc8, 0x13, 0x87, 0x32, 0x87, 0x0b, 0x27, 0x30, 0x36,
0x57, 0xe8, 0xea, 0x15, 0xce, 0x06, 0x65, 0x5e, 0x3d, 0x5a, 0x94, 0x53,
0xb7, 0x59, 0x58, 0xdf, 0x25, 0xc4, 0xe4, 0xc9, 0x65, 0x3d, 0xb4, 0xb4,
0x4e, 0x37, 0x0c, 0x29, 0x98, 0x4a, 0xe8, 0x11, 0xde, 0x85, 0x42, 0x43,
0x1c, 0xaa, 0x38, 0x55, 0xc4, 0xb4, 0x2c, 0x22, 0x3d, 0xcd, 0xfa, 0xea,
0x0d, 0xf4, 0x8d, 0x1f, 0xc9, 0x5f, 0xfa, 0x82, 0x6d, 0xc7, 0xe1, 0xa6,
0x57, 0xe3, 0x56, 0x6e, 0x96, 0xbf, 0x16, 0x1f, 0xa3, 0x54, 0xaa, 0x91,
0x16, 0x5a, 0xb2, 0xa9, 0x04, 0xaf, 0x67, 0xc9, 0xac, 0x6c, 0xfa, 0x32,
0x9e, 0x48, 0xea, 0xa5, 0x0b, 0x89, 0x3b, 0x54, 0x47, 0xf2, 0xa1, 0xf2,
0x2a, 0x4d, 0xeb, 0xf4, 0x17, 0xdc, 0xd4, 0x72, 0x6c, 0xb5, 0x36, 0x28,
0xb6, 0x7e, 0x17, 0x04, 0xd3, 0xac, 0x7a, 0x42, 0xc1, 0xf4, 0x6e, 0x9e,
0xbf, 0x6b, 0xb7, 0x3c, 0x3a, 0x21, 0x67, 0xcb, 0x41, 0x48, 0x07, 0x91,
0xde, 0x1a, 0xe2, 0xaa, 0x9c, 0xb1, 0x59, 0xdb, 0x12, 0x25, 0xc1, 0x32,
0x92, 0xea, 0xc9, 0xaf, 0x3b, 0x97, 0xca, 0xca, 0xfe, 0x5b, 0xfe, 0xe5,
0x33, 0x29, 0xeb, 0x16, 0x95, 0xd2, 0x24, 0xeb, 0xda, 0x30, 0xeb, 0x95,
0x1a, 0xd3, 0xf7, 0x0f, 0x51, 0x1c, 0xd9, 0x0b, 0x99, 0x12, 0x7a, 0x4a,
0xd0, 0xd3, 0x25, 0x9a, 0x88, 0x45, 0xb1, 0x04, 0x33, 0x2c, 0x8a, 0x99,
0x34, 0x6b, 0x75, 0x19, 0x91, 0x9d, 0x92, 0x29, 0x89, 0xa0, 0x2c, 0x8b,
0x9d, 0xd8, 0x7a, 0x5e, 0x04, 0x07, 0x87, 0x66, 0x28, 0x56, 0x67, 0xb9,
0xd6, 0xd2, 0x39, 0xd9, 0xec, 0x33, 0x30, 0xb2, 0x8b, 0xea, 0xae, 0x83,
0x18, 0xb9, 0x31, 0x34, 0xbb, 0x42, 0x22, 0x0b, 0x21, 0x96, 0x3c, 0x61,
0xac, 0xcb, 0x95, 0x60, 0x2a, 0xe9, 0x68, 0x79, 0x08, 0x36, 0x56, 0x65,
0x27, 0x4a, 0xd9, 0x83, 0x00, 0xcf, 0x0b, 0xf1, 0xfc, 0x10, 0x15, 0x0a,
0x6a, 0x75, 0x77, 0x8b, 0x86, 0xdc, 0x58, 0x57, 0x45, 0x52, 0xe9, 0x84,
0x81, 0x7c, 0x91, 0x28, 0x55, 0x23, 0x96, 0x13, 0xd7, 0x24, 0xbe, 0xac,
0x17, 0xfa, 0xf2, 0x78, 0x63, 0xc7, 0x82, 0x08, 0xda, 0xa6, 0xc5, 0x50,
0x55, 0x04, 0xe5, 0x65, 0x5b, 0x06, 0xde, 0xce, 0xf0, 0x24, 0xf3, 0x4e,
0x70, 0xb5, 0x15, 0x6a, 0x34, 0x7b, 0x11, 0x9d, 0xbe, 0x10, 0x53, 0xd0,
0xa8, 0x86, 0x2e, 0x76, 0xb6, 0x2a, 0x9d, 0x2c, 0x48, 0x3c, 0x5b, 0xa2,
0xc8, 0x3a, 0x37, 0xd4, 0x9d, 0xed, 0x6c, 0x4a, 0xab, 0x95, 0x6e, 0x08,
0x66, 0x3d, 0x5a, 0xad, 0x4d, 0x18, 0xc8, 0xca, 0xfa, 0xd5, 0x85, 0x6f,
0xf9, 0x5f, 0xde, 0x02, 0x30, 0xff, 0x03, 0x8c, 0x47, 0x35, 0xad, 0xbc,
0xbf, 0x26, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae,
0x42, 0x60, 0x82

};

unsigned int _Users_username_Pictures_SaltBae_png_len = 1863;

int main(int argc, const char * argv[]) {
    // insert code here...
    int frameless = 0;
    int resizable = 1;
    int fullscreen = 1;
    int fullSizeContent = 1;
    int hideTitleBar = 0;
    int titlebarAppearsTransparent = 0;
    int hideTitle = 0;
    int useToolbar = 0;
    int hideToolbarSeparator = 0;
    int webviewIsTransparent = 1;
    int alwaysOnTop = 0;
    int hideWindowOnClose = 0;
    const char* appearance = "NSAppearanceNameDarkAqua";
    int windowIsTranslucent = 1;
    int debug = 1;
    int windowStartState = 0;
    int startsHidden = 0;
    WailsContext *result = Create("OI OI!",400,400, frameless,  resizable, fullscreen, fullSizeContent, hideTitleBar, titlebarAppearsTransparent, hideTitle, useToolbar, hideToolbarSeparator, webviewIsTransparent, alwaysOnTop, hideWindowOnClose, appearance, windowIsTranslucent, debug, windowStartState,
                                  startsHidden, 400, 400, 600, 600);
    SetRGBA(result, 255, 0, 0, 255);
    void *m = NewMenu("");
    SetAbout(result, "Fake title", "I am a description", _Users_username_Pictures_SaltBae_png, _Users_username_Pictures_SaltBae_png_len);
//    AddMenuByRole(result, 1);
    
    AppendRole(result, m, 1);
    AppendRole(result, m, 2);
    void* submenu = NewMenu("test");
    void* menuITem = AppendMenuItem(result, submenu, "Woohoo", "p", 0, 0, 0, 470);
    AppendSubmenu(m, submenu);
    UpdateMenuItem(menuITem, 1);
    SetAsApplicationMenu(result, m);
//    SetPosition(result, 100, 100);

    
    
    Run((void*)CFBridgingRetain(result));
    return 0;
}
