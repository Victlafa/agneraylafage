// Generated by dia2code
#ifndef STATE__ELEMENT__H
#define STATE__ELEMENT__H


namespace state {

  /// class Element - 
  class Element {
    // Attributes
  private:
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
  };

};

#endif
