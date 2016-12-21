#include "ZipTool.h"
#include "QFile"
#include "QTextStream"


ZipTool::ZipTool()
{
}


ZipTool::~ZipTool()
{
}

bool ZipTool::write_dlg(QString path, QString text)
{
	QFile file(path);
	if (!file.open(QFile::WriteOnly | QFile::Append | QFile::Text))
		return false;
	QTextStream out(&file);
	out << text<<"\n";
	return true;
}
