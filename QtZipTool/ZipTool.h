#pragma once
#include "QString"
class ZipTool
{
public:
	ZipTool();
	virtual ~ZipTool();

public:
	bool write_dlg(QString path,QString text);

};

