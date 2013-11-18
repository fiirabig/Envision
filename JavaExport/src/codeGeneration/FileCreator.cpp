/*
 * FileCreator.cpp
 *
 *  Created on: Nov 13, 2013
 *      Author: marti
 */


#include "FileCreator.h"
#include <QDir>

namespace JavaExport {

FileCreator::FileCreator()
{
	// TODO Auto-generated constructor stub

}

FileCreator::~FileCreator()
{
	// TODO Auto-generated destructor stub
}

QFile* FileCreator::createFile(const QString& outputDirectory, Model::Node* node) const
{
	QDir dir(outputDirectory);
	dir.mkpath(targetDirectory(node, outputDirectory));
	QString path = filePath(node, outputDirectory);
	QFile* file = new QFile(path);
	if (!file->open(QIODevice::WriteOnly)) {
		//TODO: throw Exception
			qDebug() << "problem with file " + path;
			Q_ASSERT(false);
		}
	return file;
}

QString FileCreator::filePath(Model::Node* node, const QString& outputDirectory) const
{
	QString path(outputDirectory);
	path.append("/");
	path.append(targetDirectory(node, outputDirectory));
	path.append("/");
	path.append(fileName(node));
	return path;
}

} /* namespace JavaExport */
