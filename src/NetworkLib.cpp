#include "Headers.h"



boost::thread *connection;

void ScrollBox::connectServer(ClientMap *cMap, GraphicsTCOD *graphicsEngine)
{
    
    
    boost::asio::io_service pri_io_service;
    tcp::resolver pri_resolver(pri_io_service);
    tcp::resolver::query pri_query("localhost", "5250");
    
    tcp::resolver::iterator iterator = pri_resolver.resolve(pri_query);
    
    ClientSession c(pri_io_service, iterator, cMap, graphicsEngine);
    
    
}
