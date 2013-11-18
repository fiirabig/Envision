/*
 * FileCreator.h
 *
 *  Created on: Nov 13, 2013
 *      Author: marti
 */

#pragma once

namespace Model {
	class Node;
}

namespace JavaExport {

class FileCreator {
	public:
		FileCreator();
		virtual ~FileCreator();
		QFile* createFile(const QString& outputDirectory, Model::Node* node) const;
	protected:
		virtual QString targetDirectory(Model::Node* node,const QString& outputDirectory) const;
		virtual QString fileName(Model::Node* node) const;
		virtual QString filePath(Model::Node* node, const QString& outputDirectory) const;

};

inline QString FileCreator::targetDirectory(Model::Node* /*node*/, const QString& /*outputDirectory*/) const
{
	return QString();
}

inline QString FileCreator::fileName(Model::Node* /*node*/) const
{
	return QString();
}


} /* namespace JavaExport */
