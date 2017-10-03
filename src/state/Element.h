// Generated by dia2code
#ifndef STATE__ELEMENT__H
#define STATE__ELEMENT__H


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
    virtual int getx () = 0;
    virtual void setx (int x) = 0;
    virtual int gety () = 0;
    virtual void sety (int y) = 0;
    virtual TypeID const getTypeID () = 0;
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
