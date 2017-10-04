
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
    ~Element ();
    virtual int getx () = 0;
    virtual void setx (int x) = 0;
    virtual int gety () = 0;
    virtual void sety (int y) = 0;
    virtual TypeID const getTypeID () = 0;
  };

  enum CreaturesID {
    LUMBERJACKS,
    MINERS,
    BLACKSMITHS,
    COOKERS
  };

  /// class CreaturesGroup - 
  class CreaturesGroup {
    // Attributes
  private:
    const int stolenResourceNbr;
    bool placed;
    // Operations
  public:
    CreaturesGroup (CreaturesID type);
    ~CreaturesGroup ();
    int getx ();
    void setx (int x);
    int gety ();
    void sety (int y);
    TypeID const getTypeID ();
    bool getPlaced ();
    void toPlace (int x, int y);
  };

  /// class Cell - 
  class Cell : public Element {
    // Associations
    state::CreaturesGroup* unnamed;
    // Operations
  public:
    Cell ();
    ~Cell ();
    int getx ();
    void setx (int x);
    int gety ();
    void sety (int y);
    virtual TypeID const getTypeID () = 0;
  };

  enum SpecialCellID {
    BARBECUE,
    CANDY,
    POOL,
    SKY
  };

  /// class SpecialCell - 
  class SpecialCell : public Cell {
    // Associations
    state::SpecialCellID* unnamed;
    // Attributes
  private:
    std::string neededResType;
    int neededResNbr;
    // Operations
  public:
    SpecialCell (SpecialCellID type, std::string resType, int resNbr);
    ~SpecialCell ();
    std::string getResType ();
    int getResNbr ();
    void setResType (std::string resType);
    void setResNbr (int resNbr);
    TypeID const getTypeID ();
  };

  enum SimpleCellID {
    GRASS,
    DIRT,
    SAND
  };

  /// class SimpleCell - 
  class SimpleCell : public Cell {
    // Associations
    state::SimpleCellID* unnamed;
    // Attributes
  private:
    std::string genResType;
    int genResNbr;
    // Operations
  public:
    SimpleCell (SimpleCellID type, std::string resType, int resNbr);
    ~SimpleCell ();
    std::string getResType ();
    int getResNbr ();
    void addResType (std::string resType);
    void addResNbr (int resNbr);
    TypeID const getTypeID ();
  };

  enum ClanNameID {
    COOKERS,
    BLACKSMITHS,
    LUMBERJACKS,
    MINERS
  };

  /// class Player - 
  class Player {
    // Associations
    state::CreaturesGroup* unnamed;
    state::ClanNameID* unnamed;
    // Attributes
  private:
    int cellNbr;
    int zonesNbr;
    int conquestPoints;
    int creaturesLeft;
    std::vector<std::string> speCellsNames;
    int xLastCell;
    int yLastCell;
    // Operations
  public:
    Player ();
    ~Player ();
    int getCellsNbr ();
    int getZonesNbr ();
    int getConquestPoints ();
    int getCreaturesLeft ();
    std::vector<std::string> getSpeCellsNames ();
    int getXLastCell ();
    int getYLastCell ();
    void setCellsNbr (int count);
    void setZonesNbr (int count);
    void setConquestPts (int count);
    void setCreaLeft (int count);
    void decreaseCreaLeft ();
    void modifySpeCellsNames (std::string name, bool add);
    void setXLastCell (int x);
    void setYLastCell (int y);
  };

  enum TypeID {
    CREATURESGROUP,
    SPECIALCELL,
    SIMPLECELL
  };

  enum CellState {
    NORMAL,
    POISONED,
    PROTECTED
  };

  /// class PlayerResources - 
  class PlayerResources {
    // Associations
    state::Player* unnamed;
    // Attributes
  public:
    int wood;
    int stone;
    int metal;
    int food;
    // Operations
  public:
    PlayerResources ();
    ~PlayerResources ();
    int getResource (string type);
    void setResource (string type, int quantity, bool increase);
  };

  /// class ElementTab - 
  class ElementTab {
    // Associations
    state::Element* unnamed;
    // Attributes
  private:
    size_t width;
    size_t height;
    std::vector<std::unique_ptr<Element>> list;
    // Operations
  public:
    ElementTab (size_t width = 0, size_t height = 1);
    ~ElementTab ();
    size_t const getWidth ();
    size_t const getHeight ();
    size_t add (Element* elem);
    void resize (size_t width, size_t height);
    Element* const get (int i, int j = 0);
    void set (int i, int j = 0, Element* elem);
    const Element& operator ( )  (int i, int j = 0);
  };

  /// class State - 
  class State {
    // Associations
    state::Player* unnamed;
    state::ElementTab* unnamed;
    // Attributes
  private:
    ElementTab grid;
    ElementTab characters;
    int totalCellNbr;
    // Operations
  public:
    State ();
    ~State ();
    ElementTab& getGrid ();
    ElementTab& getCharacters ();
    int getCellNbr ();
  };

};

