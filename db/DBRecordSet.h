#ifndef _DB_RECONRD_SET_H_
#define _DB_RECONRD_SET_H_

#include "DBRecord.h"

#include <mysql/mysql.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

// struct DBRecordPtr;

class DBRecordSet
	: private boost::noncopyable
{
public:
	DBRecordSet(MYSQL_RES* pRes);
	~DBRecordSet();

	// ��¼����
	unsigned int		GetRecordNum();
	// �ֶθ���
	unsigned int		GetFieldCount();

	DBRecordPtr			GetNextRecord();

private:
	MYSQL_RES*			m_pRes;
	MYSQL_ROW			m_Row;

};

typedef boost::shared_ptr<DBRecordSet> DBRecordSetPtr;

#endif // _DB_RECONRD_SET_H_
