


class WorldMap {
    
private:
    
    
public:
    
    
    int wX, wY, wZ;
    int cX, cY, cZ;
       
    //boost::multi_array<3, EntityMap *> eMap;
    //std::vector<std::vector<std::vector<TileMap*> > > *tMap;
    std::vector<std::vector<std::vector<EntityMap*> > > *eMap;
    

    WorldMap(int x=10, int y=10, int z=10) : wX(x), wY(y), wZ(z), cX(x/2), cY(y/2), cZ(z/2)
    {
        
        cout << "World Latitude = " << wX << endl;
        cout << "World Longitude = " << wY << endl;
        cout << "World Height = " << wZ << endl;
        
        //tMap = new std::vector<std::vector<std::vector<TileMap*> > >(wX, std::vector<std::vector<TileMap*> >(wY, std::vector<TileMap*>(wZ, new TileMap(MAP_WIDTH, MAP_HEIGHT))));
        eMap = new std::vector<std::vector<std::vector<EntityMap*> > >(wX, std::vector<std::vector<EntityMap*> >(wY, std::vector<EntityMap*>(wZ, nullptr) ) );

        
    };
    
    void initWorldMap();

    
    
    void addEntToCenter(Entity *tgt);
    void removeEnt(Entity *tgt);
    
    void moveEnt(Entity *tgt, int x, int y);
    void moveEntTo(Entity *tgt, int x, int y, int z, int px, int py);
    
    void changEntZ(Entity *tgt, int z);
    
    
    
    EntityMap *getNextEntMap(Entity *tgt, int dir);
    EntityMap *getNextEntMap(EntityMap *tgt, int dir);
    EntityMap *getEntityZ(EntityMap *tgt, int z);
    
};