#pragma once
#pragma execution_character_set("utf-8")


#include <wtypes.h>
#include <vector>
// #include <afxstr.h>
#include "tZipToolDef.h"
#include <atlstr.h>
#include "zlib\zip.h"
#include "zlib\unzip.h"
// #include "..\tZipLib\tZipLibInc.h"

/*
 * \class:tZipTool
 * \brief:压缩、解压相关操作
 * \
 * \notice：
 */
class tZipTool
{
public:
	tZipTool(void);
	~tZipTool(void);
public:	//相关设置
	void tEnableExportErrLog(bool bable = true){ m_bWriteZipDirLog = bable;}; //生成错误日志 tZiplog.txt
	void tEnableSkipErrFile(bool bable = true){m_bSkipErrFile = bable;};		//允许跳过压缩或解压文件，当允许时，建议输出日志，便于查看
public:	//压缩（分三步：创建zip文件，zip内添加文件，保存zip文件）
	/*=============================================================================*\
	replace值:
	const int IN_TZIP_FILE_APPEND			= 0;// 如果文件存在追加（压缩）
	const int IN_TZIP_FILE_REPLACE			= 1;// 如果文件存在替换（压缩解压缩）
	const int IN_TZIP_FILE_EXIT				= 2;// 如果文件存在退出（压缩）
	const int IN_TZIP_FILE_SKIP				= 3;// 如果文件存在跳过（解压缩）
	return值：
		0 - 成功
		小于0 - 失败 查看def.h文件查看
	\*=============================================================================*/
	int ZipCreate(LPCTSTR zipFileName,int replace = 2);	//创建zip文件
	int AddFiles(LPCTSTR szPathName,bool bHasShowPath = true);	//bHasShowPath = false时，文件在zip内无路径
	int ZipSave();

public:		//直接压缩或解压，一个函数搞定

	/*=============================================================================*\
	压缩
	 * directory，待压缩的目录或文件
	 * zipfile，输出的文件
	 * replaceFlag，如果输出文件存在的处理方式，设置为HT_ZIP_REPLACE将替换原有文件，如果
	 *              设置为HT_ZIP_APPEND将在原有的基础上追加新文件，其他为停止压缩操作
	 * 返回 0：表示操作成功，其余见def.h
	 \*=============================================================================*/
	int ZipCompress(LPCTSTR dirFile,LPCTSTR szZipPathName,int replaceFlag = 0);

	/*=============================================================================*\
	 * 解压缩文件到指定目录
	 * szZipFile，要解压缩的文件
	 * szOutDir，输出目录，如果目录不存在，自动创建
	 * replaceFlag，如果输出文件存在的处理方式，设置为HT_ZIP_REPLACE将替换原有文件，如果
	 *              设置为HT_ZIP_FILE_SKIP跳过该文件，其他参数皆作为替换
	 * 返回 0：表示操作成功，其余见def.h
	 \*=============================================================================*/
	int ZipExtract(LPCTSTR szZipFile,LPCTSTR szOutDir,int replaceFlag = 1);	//解压
	int ExtractFilestoDir(LPCTSTR szZipFile,LPCTSTR szOutDir,int replaceFlag = 1);	//去掉压缩目录层级解压
protected:	//压缩调用函数
	int tcompress_file(zipFile& file, CString showPath, CString path);
	uLong tget_file_last_access_time(CString filePath);

protected:	//获取目录文件
	bool tget_files(CString directory, __FILEINFOS& infos,bool hasShowPath);		//showPath文件在zip内路径
	bool tget_dir_allfiles(CString directory,int ndirLen, __FILEINFOS& infos);
	void taddarr_file_info(CString filePath, CString pathNameInZip, __FILEINFOS& infos);

protected:	//解压调用函数
	int tunzip_current_file(unzFile unzfile,LPCTSTR strFilePathName,int replaceFlag);

protected:	//文件相关
	int  tcreate_dirtory(LPCTSTR szPath);	//目录不存在则创建，存在或创建成功，返回true
	bool tis_path_file(LPCTSTR szPath);		//是文件，且存在

protected:	//写日志相关
	void tget_zip_dir(LPCTSTR szZipFile);
	bool twrite_zip_log(char* szText);
public:
	bool m_bWriteZipDirLog;		//在Zip文件目录写日志
	bool m_bSkipErrFile;		//跳过错误文件
private:
	zipFile m_zip_file;		//压缩、解压使用句柄，类型相同，获取方式不同
	CString m_zip_dir;		//压缩文件目录
 	__FILEINFOS m_fileInfos;

};

