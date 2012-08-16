class ScrollBox : public Widget {
    
private:
    
    std::vector<std::string> *textBuffer;
    char *scrollbackBuffer;
    
    int maxBuffer;
    
    TCODConsole *console;
    
    
public :
    
    ScrollBox( int x, int y, int w, int h, int MaxBuffer, TCODConsole *Console);
    virtual ~ScrollBox();
    void attachConsole(TCODConsole *Console);
    void render();
    void update(const TCOD_key_t k);
    void insertText(std::string newText);
    
    
protected :
    
    bool onArrows;
    bool scrollUp;
    bool scrollDown;
    
    
    
        
    void onButtonPress();
    void onButtonRelease();
    void onScrollUp();
    void onScrollDown();
};