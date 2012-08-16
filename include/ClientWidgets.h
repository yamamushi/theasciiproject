class ScrollBox : public Widget {
    
private:
    
    std::vector<std::string> *textBuffer;
    char *scrollbackBuffer;
    
    int maxBuffer;
    int realX;
    int realY;
    
    TCODConsole *console;
    
    
public :
    
    ScrollBox( int x, int y, int w, int h, int MaxBuffer, TCODConsole *Console);
    virtual ~ScrollBox();
    void attachConsole(TCODConsole *Console);
    void render();
    void update(const TCOD_mouse_t k);
    void insertText(std::string newText);
    
    void setRealPosition(int x, int y);
    
protected :
    
    bool onUpArrow;
    bool onDownArrow;
    bool scrollUp;
    bool scrollDown;
    
    
    
        
    void onButtonPress();
    void onButtonRelease();
    void onScrollUp();
    void onScrollDown();
};