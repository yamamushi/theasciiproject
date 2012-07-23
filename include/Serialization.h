
class ClientMap;

class ClientMapPacker {

private:

    //s_render_t *sMap;
    //render_t *rMap;

    //s_render_t *csMap;

    tpl_node *tn;


public:

    ClientMapPacker();

    s_render_t clientToSerial(render_t source);
    render_t serialToClient(s_render_t lMap);

    void packToNet(render_t source, unsigned char *buf);
    void unpackFromNet(ClientMap *dest, unsigned char *buf);



};