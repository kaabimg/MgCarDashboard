#include "test_can_decoder.h"
#include "../plugins/prius2/mgprius2canmessagesdecoder.h"


#include <QFile>
#include <QDebug>

test_can_decoder::test_can_decoder()
{
}

void test_can_decoder::run()
{
    QFile data("/home/ghaith/developement/workspace/MgCarDashboard/MgCarDashboard/test_data/data");
    bool ok = data.open(QFile::ReadOnly | QFile::Text);

    qDebug()<<"file open"<<ok;

    QByteArray line;


    MgPrius2CanMessagesDecoder decoder;

    do
    {
        line = data.readLine();
        if(line.endsWith('\n'))
            line.remove(line.size()-1,1);

        if(line .isEmpty() || line.isNull())
            break;

        decoder.decodeMessage(line);

    }
    while(true);


    qDebug()<<"closing file";


    data.close();


}
