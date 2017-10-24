// Generated by dia2code
#ifndef STATE__ELEMENT__H
#define STATE__ELEMENT__H


namespace state {
  class Element;
}


namespace state {

  /// class Element - 
  class Element {
    // Attributes
  protected:
    int x;
    int y;
    int creaturesNbr;
    // Operations
  public:
    Element ();
    virtual ~Element ();
    bool operator== (Element otherElement);
    // Setters and Getters
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    int getCreaturesNbr() const;
    void setCreaturesNbr(int creaturesNbr);
  };

};

#endif
