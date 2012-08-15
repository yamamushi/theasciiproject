class TCODLIB_GUI_API ScrollBox : public Widget {
    
private:
    
    std::vector<std::string> *textBuffer;
    char *scrollbackBuffer;
    
    
public :
    
    ScrollBox( int x, int y, int w, int h);
    virtual ~ScrollBox();
    void render(TCODConsole *console=con);
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