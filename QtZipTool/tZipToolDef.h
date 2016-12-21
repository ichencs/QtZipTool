#pragma once
#pragma execution_character_set("utf-8")

#include "QString"
#include <vector>
// #include <afxstr.h>
// #include <afxwin.h>
// #include <afxstr.h>
// #include <afxstr.h>


const int IN_TZIP_FILE_APPEND			= 0;// 如果文件存在追加（压缩）
const int IN_TZIP_FILE_REPLACE			= 1; // 如果文件存在替换（压缩解压缩）
const int IN_TZIP_FILE_EXIT				= 2;// 如果文件存在退出（压缩）

const int IN_TZIP_FILE_SKIP				= 3;// 如果文件存在跳过（解压缩）

const int RT_TZIP_FILE_SKIP				= IN_TZIP_FILE_SKIP;
const int RT_TZIP_FLAG_OK				= 0;
const int RT_TZIP_FLAG_NO_ERROR			= RT_TZIP_FLAG_OK;
const int RT_TZIP_FLAG_FILE_NOT_FOUND	= -1;
const int RT_TZIP_FLAG_FILE_IS_EXIST	= -2;
const int RT_TZIP_FLAG_EXTRACT_IS_FILE	= -2;
const int RT_TZIP_FLAG_IO_ERROR			= -3;
const int RT_TZIP_FLAG_ERROR			= -4;
const int RT_TZIP_CONTEXT				= -5;
const int RT_TZIP_FLAG_BAD_INPUT		= -6;
const int RT_TZIP_FLAG_REPLACE_ERROR	= -7;

const int RT_TZIP_FLAG_CREATE_ERROR		= -8;
const int RT_TZIP_FLAG_NOT_OPEN_ZIP		= -9	;




#define BUF_LEN 16384
#define MAX__PATH 1024 // 默认文件名长度