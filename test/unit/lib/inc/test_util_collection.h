#ifndef TEST_UTIL_COLLECTION_H
#define TEST_UTIL_COLLECTION_H

#include <QtTest/QTest>

class TestUtilCollection : public QObject{
 Q_OBJECT
private slots:
    void constructor();
    void has_command();
    void insert_util();
    void command_list();
};

#endif //TEST_UTIL_COLLECTION_H
