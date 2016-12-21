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
 * \brief:ѹ������ѹ��ز���
 * \
 * \notice��
 */
class tZipTool
{
public:
	tZipTool(void);
	~tZipTool(void);
public:	//�������
	void tEnableExportErrLog(bool bable = true){ m_bWriteZipDirLog = bable;}; //���ɴ�����־ tZiplog.txt
	void tEnableSkipErrFile(bool bable = true){m_bSkipErrFile = bable;};		//��������ѹ�����ѹ�ļ���������ʱ�����������־�����ڲ鿴
public:	//ѹ����������������zip�ļ���zip������ļ�������zip�ļ���
	/*=============================================================================*\
	replaceֵ:
	const int IN_TZIP_FILE_APPEND			= 0;// ����ļ�����׷�ӣ�ѹ����
	const int IN_TZIP_FILE_REPLACE			= 1;// ����ļ������滻��ѹ����ѹ����
	const int IN_TZIP_FILE_EXIT				= 2;// ����ļ������˳���ѹ����
	const int IN_TZIP_FILE_SKIP				= 3;// ����ļ�������������ѹ����
	returnֵ��
		0 - �ɹ�
		С��0 - ʧ�� �鿴def.h�ļ��鿴
	\*=============================================================================*/
	int ZipCreate(LPCTSTR zipFileName,int replace = 2);	//����zip�ļ�
	int AddFiles(LPCTSTR szPathName,bool bHasShowPath = true);	//bHasShowPath = falseʱ���ļ���zip����·��
	int ZipSave();

public:		//ֱ��ѹ�����ѹ��һ�������㶨

	/*=============================================================================*\
	ѹ��
	 * directory����ѹ����Ŀ¼���ļ�
	 * zipfile��������ļ�
	 * replaceFlag���������ļ����ڵĴ���ʽ������ΪHT_ZIP_REPLACE���滻ԭ���ļ������
	 *              ����ΪHT_ZIP_APPEND����ԭ�еĻ�����׷�����ļ�������Ϊֹͣѹ������
	 * ���� 0����ʾ�����ɹ��������def.h
	 \*=============================================================================*/
	int ZipCompress(LPCTSTR dirFile,LPCTSTR szZipPathName,int replaceFlag = 0);

	/*=============================================================================*\
	 * ��ѹ���ļ���ָ��Ŀ¼
	 * szZipFile��Ҫ��ѹ�����ļ�
	 * szOutDir�����Ŀ¼�����Ŀ¼�����ڣ��Զ�����
	 * replaceFlag���������ļ����ڵĴ���ʽ������ΪHT_ZIP_REPLACE���滻ԭ���ļ������
	 *              ����ΪHT_ZIP_FILE_SKIP�������ļ���������������Ϊ�滻
	 * ���� 0����ʾ�����ɹ��������def.h
	 \*=============================================================================*/
	int ZipExtract(LPCTSTR szZipFile,LPCTSTR szOutDir,int replaceFlag = 1);	//��ѹ
	int ExtractFilestoDir(LPCTSTR szZipFile,LPCTSTR szOutDir,int replaceFlag = 1);	//ȥ��ѹ��Ŀ¼�㼶��ѹ
protected:	//ѹ�����ú���
	int tcompress_file(zipFile& file, CString showPath, CString path);
	uLong tget_file_last_access_time(CString filePath);

protected:	//��ȡĿ¼�ļ�
	bool tget_files(CString directory, __FILEINFOS& infos,bool hasShowPath);		//showPath�ļ���zip��·��
	bool tget_dir_allfiles(CString directory,int ndirLen, __FILEINFOS& infos);
	void taddarr_file_info(CString filePath, CString pathNameInZip, __FILEINFOS& infos);

protected:	//��ѹ���ú���
	int tunzip_current_file(unzFile unzfile,LPCTSTR strFilePathName,int replaceFlag);

protected:	//�ļ����
	int  tcreate_dirtory(LPCTSTR szPath);	//Ŀ¼�������򴴽������ڻ򴴽��ɹ�������true
	bool tis_path_file(LPCTSTR szPath);		//���ļ����Ҵ���

protected:	//д��־���
	void tget_zip_dir(LPCTSTR szZipFile);
	bool twrite_zip_log(char* szText);
public:
	bool m_bWriteZipDirLog;		//��Zip�ļ�Ŀ¼д��־
	bool m_bSkipErrFile;		//���������ļ�
private:
	zipFile m_zip_file;		//ѹ������ѹʹ�þ����������ͬ����ȡ��ʽ��ͬ
	CString m_zip_dir;		//ѹ���ļ�Ŀ¼
 	__FILEINFOS m_fileInfos;

};

