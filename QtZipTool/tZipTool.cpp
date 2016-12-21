// #include "stdafx.h"
#include "tZipTool.h"
#include "zlib\unzip.h"
// #include <afxwin.h>
#include <shlobj.h>
// #include <afx.h>


tZipTool::tZipTool(void)
{
	m_zip_file = NULL;
	m_bWriteZipDirLog = false;
	m_bSkipErrFile = false;
}


tZipTool::~tZipTool(void)
{
}

int tZipTool::tcreate_dirtory(LPCTSTR szPath)
{
	if(szPath == NULL)
		return false;
	if(PathIsDirectory(szPath))
		return RT_TZIP_FLAG_OK;
	int nRes = ::SHCreateDirectoryEx(NULL,szPath,NULL);
	return nRes;
}

bool tZipTool::tis_path_file(LPCTSTR szPath)
{
	if(szPath == NULL)
		return false;
	if (!PathFileExists(szPath))
		return false;
	return !PathIsDirectory(szPath);
}

int tZipTool::ZipCompress(LPCTSTR dirFile,LPCTSTR zipfile,int replaceFlag /*= 0*/)
{
	int ret = RT_TZIP_FLAG_OK;	
	try
	{	
		ret = ZipCreate(zipfile);
		if(ret != RT_TZIP_FLAG_OK)
			throw "����ѹ���ļ�ʧ��";
		ret = AddFiles(dirFile);
		if(ret != RT_TZIP_FLAG_OK)
			throw "���ѹ���ļ�ʧ��";
		ret = ZipSave();
		if(ret != RT_TZIP_FLAG_OK)
			throw "����ѹ���ļ�ʧ��";
	}
	catch (char* serr)
	{
		if (m_bWriteZipDirLog)
		{
			twrite_zip_log(CString(serr));
		}
	}
	return ret;

}


int tZipTool::ZipExtract(LPCTSTR zipfile,LPCTSTR outDirectory,int replaceFlag /*= 1*/)
{
	tget_zip_dir(zipfile);
// 	CFile cfile; //�Ƴ��ļ�ʹ��
	int ret = RT_TZIP_FLAG_OK;
	if (!PathFileExists(zipfile)){
		return RT_TZIP_FLAG_FILE_NOT_FOUND;
	}
	CString u_dir(outDirectory);
	u_dir.TrimRight(_T("\\"));
	u_dir += "\\";

	if (PathFileExists(outDirectory)){
		if (!PathIsDirectory(outDirectory)){
			// ���Ŀ¼Ϊ�ļ���
			return RT_TZIP_FLAG_EXTRACT_IS_FILE;
		}
	}else{
		// �����ļ���
		if (tcreate_dirtory(u_dir) != RT_TZIP_FLAG_OK)
		{
			return RT_TZIP_FLAG_IO_ERROR;
		}
	}
	try{
		unzFile unzfile = unzOpen64(zipfile); // ���ļ�
// 		char in[BUF_LEN]; // �ļ���ȡ������
// 		unsigned int readLen; // �����ļ�����
		if(unzfile != NULL)
		{
			unz_global_info64 unzInfo;
			ZeroMemory(&unzInfo,sizeof(unz_global_info64));

			if (unzGetGlobalInfo64(unzfile, &unzInfo) == UNZ_OK)
			{				
				// �ֲ���ѹ���ļ�
				for(ZPOS64_T i = 0, j = unzInfo.number_entry; i < j && ret == RT_TZIP_FLAG_OK; i ++)
				{
					char szFilePathA[MAX__PATH] = {0};
					unz_file_info64 unzfileinfo;
					ZeroMemory(&unzfileinfo,sizeof(unz_file_info64));

					ret = unzGetCurrentFileInfo64(unzfile, &unzfileinfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0); // ��ȡ�ļ�
					// �޸��ļ�·����Ϣ
					CString outFilePath = u_dir + szFilePathA;
// 					TRACE(outFilePath);
 					outFilePath.Replace('/', '\\');
					CString strTmp = outFilePath;
					int ns = (int)strTmp.ReverseFind('\\');
					strTmp = strTmp.Mid(0,ns);
					if (tcreate_dirtory(strTmp) != RT_TZIP_FLAG_OK)
					{
						if(m_bWriteZipDirLog)
						{
							twrite_zip_log(strTmp + _T("\tĿ¼����ʧ�ܣ��޷�������ѹ��"));
						}
						ret = RT_TZIP_FLAG_IO_ERROR;
						break;
					}
					// �ж��ļ��Ƿ���ڣ�������ڣ���������״̬���д���
					if(!PathIsDirectory(outFilePath))
						ret = tunzip_current_file(unzfile,outFilePath,replaceFlag);
					ret = unzGoToNextFile(unzfile);
				}
			}
			else{
				ret = RT_TZIP_FLAG_IO_ERROR; // ��ȡѹ���ļ�ͷ��Ϣʧ�ܣ�
			}
			unzClose(unzfile);
		}else{
			ret = RT_TZIP_FLAG_IO_ERROR;// ��ѹ���ļ�ʧ��
		}
	}catch(...){
// 		e->ReportError();
// 		e->Delete();
		ret = RT_TZIP_FLAG_ERROR;
	}
	return ret;
}


int tZipTool::tunzip_current_file(unzFile unzfile,LPCTSTR outFilePath,int replaceFlag)
{
	int ret = RT_TZIP_FLAG_BAD_INPUT;
	if(!unzfile)
		return ret;
	//����
	try
	{
		//�滻
		if(tis_path_file(outFilePath))
		{
			if (replaceFlag == IN_TZIP_FILE_SKIP)
			{
// 				if(m_bWriteZipDirLog)
// 				{
// 					write_zip_log(outFilePath + _T("\t�Ѵ��ڣ�����Ҫ��������ѹ"));
// 				}
				ret = RT_TZIP_FILE_SKIP;
				throw"\t�Ѵ��ڣ�����Ҫ��������ѹ";
			}	
			BOOL bDel = DeleteFile(outFilePath);
			if (!bDel)
			{
// 				if(m_bWriteZipDirLog)
// 				{
// 			 			write_zip_log(CString(outFilePath) + _T("\t�ļ��滻ʧ�ܣ�����"));
// 				}
				ret = RT_TZIP_FILE_SKIP;
				throw"\t�ļ��滻ʧ�ܣ�����";
			}
		}

		//��ʼд�ļ�
		ret = unzOpenCurrentFile(unzfile);
		char file_buf[BUF_LEN] = {0};		//��ȡ�ļ�������
		unsigned int readLen;		// �����ļ�����
		FILE* write_file = NULL;
		ret = fopen_s(&write_file,outFilePath, "wb");
		if(ret || write_file == NULL)
			throw "�ļ���ʧ��";
		while(1)
		{
			readLen = unzReadCurrentFile(unzfile, file_buf, BUF_LEN);
			if (readLen < 0){
				ret = RT_TZIP_FLAG_IO_ERROR;
				// ���ļ�����
				throw"���ļ�����";
			}
			if (readLen == 0){
				break;
			}
			ret = fwrite(file_buf, 1, readLen, write_file);
			if (ferror(write_file)){
				ret = RT_TZIP_FLAG_IO_ERROR;
				throw"д�ļ�����"; // д�ļ�����
			}
		}
		ret = fclose(write_file);
		if(ret)
			throw"�ļ��ر��쳣";
		ret = unzCloseCurrentFile(unzfile);	
	}
	catch (char* strInfo)
	{
		if(m_bWriteZipDirLog)
		{
			twrite_zip_log(outFilePath + CString(strInfo));
		}
	}
	return ret;
}


void tZipTool::taddarr_file_info(CString filePath, CString pathNameInZip, __FILEINFOS& infos)
{
	pathNameInZip.TrimLeft(_T("\\"));
	sZipFileInfo info;
 	info.pathNameInZip = pathNameInZip;
	info.filePath = filePath;
	infos.push_back(info);
}


bool tZipTool::tget_files(CString directory, __FILEINFOS& infos,bool hasShowPath /*= true*/)
{
	if (!PathFileExists(directory))
		return false;
	int ndirLen = -1;
	if (hasShowPath)
	{
		if (PathIsDirectory(directory))
		{
			ndirLen = directory.GetLength();
		}
		else
		{
			ndirLen = directory.ReverseFind('\\');
		}
	}
	return tget_dir_allfiles(directory,ndirLen,infos);
}


bool tZipTool::tget_dir_allfiles(CString directory,int ndirLen, __FILEINFOS& infos)
{
	if (!PathFileExists(directory))
		return false;

	if(PathIsDirectory(directory))
	{
		directory.TrimRight(_T("\\"));
		directory += "\\*.*";
	}

	CFileFind _find;
	int res = _find.FindFile(directory);
	while(res)
	{
		CString nameInZip;		//��zip�ڵ�·������
		res = _find.FindNextFile();
		nameInZip = _find.GetFilePath();
		if (_find.IsDirectory())
		{
			if (!_find.IsDots())
			{
				tget_dir_allfiles(nameInZip,ndirLen, infos);
				if (ndirLen > 0)
				{
					CString strZipFolder = nameInZip.Mid(ndirLen);
					strZipFolder.Trim('\\');
					strZipFolder += '\\';		//�ļ���ֻ��ȡ�Ҳ�� ��\��
					taddarr_file_info(nameInZip, strZipFolder, infos);	//ѹ���ļ��У���ֹ���ֿ��ļ���û�б�ѹ�������
				}
			}
		}
		else{
// 			nameInZip = _find.GetFilePath();
			if (ndirLen > 0)
			{
				taddarr_file_info(nameInZip, nameInZip.Mid(ndirLen), infos);
			}
			else
			{
				//��showPath
				int nlen = nameInZip.ReverseFind('\\');
				taddarr_file_info(nameInZip, nameInZip.Mid(nlen), infos);
			}
			
		}
	}
	_find.Close();
	return true;
}

int tZipTool::tcompress_file(zipFile& zipfile, CString showPath, CString filePath)
{
	char read_buf[BUF_LEN];
	unsigned int readLen;
	int ret = RT_TZIP_FLAG_OK;
	int err = ZIP_OK;

	zip_fileinfo fileinfo;
	ZeroMemory(&fileinfo,sizeof(zip_fileinfo));
	fileinfo.dosDate = tget_file_last_access_time(filePath);
	err = zipOpenNewFileInZip64(zipfile, showPath, &fileinfo, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION, 1);
	
	//�ļ��в���Ҫ��д�ļ�������ֱ���˳����ɣ���Ȼfopen_s��ʧ�ܡ�
	if (showPath.Right(1) == '\\')
	{
		err = zipCloseFileInZip(zipfile);
		return err;
	}
	//�ļ�ѹ������
	FILE* __file = NULL;
	err = fopen_s(&__file,filePath, _T("rb"));
	//���ļ��쳣ʱ����ʽ
	if (err != 0)
	{
		zipCloseFileInZip(zipfile);
		if(m_bWriteZipDirLog)
		{
			twrite_zip_log(filePath +_T("\tѹ��ʧ�ܣ��޷���ȡ�ļ�"));
		}
		if (m_bSkipErrFile)
		{
			err = RT_TZIP_FILE_SKIP;
			return err;
		}
		else
		{
			twrite_zip_log(_T("���쳣��ֹѹ��"));
			throw _T("ԭ�ļ���ȡʧ��");
		}
	}
	do{
		readLen = fread(read_buf, 1, BUF_LEN, __file);
		if (readLen<BUF_LEN)
		{
			if(feof(__file)==0)		//������ϵ��ļ���������
			{
				err = ZIP_ERRNO;
				ret = RT_TZIP_FLAG_IO_ERROR;
			}
		}
		if(readLen>0)
		{
			// д�ļ�
			err = zipWriteInFileInZip(zipfile, read_buf, readLen);
			if (err < 0)
			{
				ret = RT_TZIP_FLAG_IO_ERROR;
			}
		}
	}while(err == Z_OK && readLen>0);

	if(__file)
		fclose(__file);
	if(err <0)
		ret = err;
	else
	{
		err = zipCloseFileInZip(zipfile);
		if (err < 0)
		{
			ret = RT_TZIP_FLAG_IO_ERROR;
		}
	}
	return ret;
}

uLong tZipTool::tget_file_last_access_time(CString filePath)
{
	long result = 0;
	CFileFind _find;
	if (_find.FindFile(filePath)){
		_find.FindNextFile();
		::FILETIME time;
		_find.GetLastAccessTime(&time);
		result = time.dwHighDateTime;
	}
	_find.Close();
	return result;
}

int tZipTool::ZipCreate(LPCTSTR zipFileName,int nReplace /*= 0*/)
{
 	m_fileInfos.clear();
	if(!zipFileName || nReplace < 0 || nReplace > 2)
		return RT_TZIP_FLAG_BAD_INPUT;
	int openMode = APPEND_STATUS_CREATE;	//����
	if(PathFileExists(zipFileName))
	{
		if(nReplace == IN_TZIP_FILE_APPEND)
		{
			openMode = APPEND_STATUS_ADDINZIP;
		}
		else if(nReplace == IN_TZIP_FILE_REPLACE)
		{
			BOOL bDel = DeleteFile(zipFileName);
			if(!bDel)
				return RT_TZIP_FLAG_REPLACE_ERROR;
		}
		else if(nReplace == IN_TZIP_FILE_EXIT)
		{
			return RT_TZIP_FILE_SKIP;
		}
	}	

	m_zip_file = zipOpen64(zipFileName, openMode);
	if(m_zip_file == NULL)
		return RT_TZIP_FLAG_CREATE_ERROR;
	tget_zip_dir(zipFileName);
	return RT_TZIP_FLAG_NO_ERROR;
}


int tZipTool::AddFiles(LPCTSTR szPathName,bool bHasShowPath /*= true*/)
{
	int ret = RT_TZIP_FLAG_BAD_INPUT;
	if (!PathFileExists(szPathName))
		return ret;
	ret = tget_files(szPathName,m_fileInfos,bHasShowPath);
	return ret;
}


bool tZipTool::twrite_zip_log(char* szText)
{
	QString strlog = "tZiplog.txt";

	QFile file(szText);
	if (!file.open(QFile::WriteOnly | QFile::Append | QFile::Text))
	{
		return false;
	}

	

// 	CStdioFile sfLog;
// 	if(!PathIsDirectory(m_zip_dir))
// 		return false;
// 	m_zip_dir.TrimRight('\\');
// 	m_zip_dir += _T("\\");
// 	CString strLog = m_zip_dir + _T("tZiplog.txt");
// 	if (PathFileExists(strLog))
// 	{
// 		if (!sfLog.Open(strLog,CFile::modeWrite | CFile::typeText))
// 			return false;
// 	}
// 	else
// 	{
// 		if (!sfLog.Open(strLog,CFile::modeCreate | CFile::modeWrite | CFile::typeText))
// 			return false;
// 	}
// 	CTime time;
// 	time = CTime::GetCurrentTime();
// 	time.Format(_T("t��%Y-%m-%d  %H��%M"));
// 	sfLog.SeekToEnd();
// 	sfLog.WriteString(CString(szText) + time.Format(_T("\t %Y-%m-%d  %H��%M")) + _T("\n"));
// 	sfLog.Close();
	return true;
}

int tZipTool::ZipSave()
{
	int ret ;
	for (int i = 0; i < (int)m_fileInfos.size(); i++)
	{
		CString showfilePath = m_fileInfos[i].pathNameInZip;
		CString filePath = m_fileInfos[i].filePath;
		ret = tcompress_file(m_zip_file,showfilePath,filePath);
		if (ret != RT_TZIP_FLAG_OK && ret != RT_TZIP_FILE_SKIP)
		{
			twrite_zip_log(showfilePath + _T("ѹ���쳣"));
		}
	}
	
	m_fileInfos.clear();
	ret = zipClose(m_zip_file,NULL);
	if (m_bWriteZipDirLog)
	{
		twrite_zip_log("ѹ��������");
	}
	return ret;
}

int tZipTool::ExtractFilestoDir(LPCTSTR szZipFile,LPCTSTR szOutDir,int replaceFlag /*= 1*/)
{
	//������־ʹ��
	tget_zip_dir(szZipFile);

	CFile cfile; //�Ƴ��ļ�ʹ��
	int ret = RT_TZIP_FLAG_OK;
	if (!PathFileExists(szZipFile)){
		return RT_TZIP_FLAG_FILE_NOT_FOUND;
	}
	CString u_dir(szOutDir);
	u_dir.TrimRight(_T("\\"));
	u_dir += "\\";

	if (PathFileExists(szOutDir)){
		if (!PathIsDirectory(szOutDir)){
			// ���Ŀ¼Ϊ�ļ���
			return RT_TZIP_FLAG_EXTRACT_IS_FILE;
		}
	}else{
		// �����ļ���
		if (tcreate_dirtory(u_dir) != RT_TZIP_FLAG_OK)
		{
			return RT_TZIP_FLAG_IO_ERROR;
		}
	}
	try{
		unzFile unzfile = unzOpen64(szZipFile); // ���ļ�
		if(unzfile != NULL)
		{
			unz_global_info64 unzInfo;
			ZeroMemory(&unzInfo,sizeof(unz_global_info64));

			if (unzGetGlobalInfo64(unzfile, &unzInfo) == UNZ_OK)
			{				
				// �ֲ���ѹ���ļ�
				for(ZPOS64_T i = 0, j = unzInfo.number_entry; i < j && ret == RT_TZIP_FLAG_OK; i ++)
				{
					char szFilePathA[256] = {0};
					unz_file_info64 unzfileinfo;
					ZeroMemory(&unzfileinfo,sizeof(unz_file_info64));

					ret = unzGetCurrentFileInfo64(unzfile, &unzfileinfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0); // ��ȡ�ļ�
					// �޸��ļ�·����Ϣ
					CString zipOutFile(szFilePathA);
					zipOutFile.Replace("/", "\\");
					zipOutFile = zipOutFile.Mid(zipOutFile.ReverseFind('\\')+1);

					CString outFilePath = u_dir + zipOutFile;
					TRACE(outFilePath);
					outFilePath.Replace("/", "\\");
					CString strTmp = outFilePath;
					int ns = (int)strTmp.ReverseFind(_T('\\'));
					strTmp = strTmp.Mid(0,ns);
					if (tcreate_dirtory(strTmp) != RT_TZIP_FLAG_OK)
					{
						if(m_bWriteZipDirLog)
						{
							twrite_zip_log(strTmp + _T("\tĿ¼����ʧ�ܣ��޷�������ѹ��"));
						}
						ret = RT_TZIP_FLAG_IO_ERROR;
						break;
					}
					// �ж��ļ��Ƿ���ڣ�������ڣ���������״̬���д���
					if(!PathIsDirectory(outFilePath))
						ret = tunzip_current_file(unzfile,outFilePath,replaceFlag);
					ret = unzGoToNextFile(unzfile);
				}
			}
			else{
				ret = RT_TZIP_FLAG_IO_ERROR; // ��ȡѹ���ļ�ͷ��Ϣʧ�ܣ�
			}
			unzClose(unzfile);
		}else{
			ret = RT_TZIP_FLAG_IO_ERROR;// ��ѹ���ļ�ʧ��
		}
	}catch(...){
// 		e->ReportError();
// 		e->Delete();
		ret = RT_TZIP_FLAG_ERROR;
	}
	return ret;
}

void tZipTool::tget_zip_dir(LPCTSTR szZipFile)
{
	m_zip_dir = szZipFile;
	m_zip_dir = m_zip_dir.Mid(0,m_zip_dir.ReverseFind('\\'));
}

