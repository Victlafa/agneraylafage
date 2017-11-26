#include "Surface.h"
#include "Tile.h"
#include "state/TypeID.h"
#include "state/State.h"
#include <iostream>

namespace render
{
    
    Surface::Surface () {}
    
    void Surface::loadTexture (const std::string& imgFile)
    {
        if(!this->texture.loadFromFile("./res/" + imgFile)) 
            std::cout<< "Erreur chargement texture de Surface ! \n"<< std::endl;
    }
    
    void Surface::initQuads ()
    {
        this->quadsList.reserve(29);
        for (int i = 0; i < 29; i ++)
        {
            // Preparation de la première ligne d'hexagones  :
            this->quadsList.push_back(sf::VertexArray(sf::Quads,4));
        }
    }
    
    // On fixe les coordonnees du sprite dans l'affichage final
    void Surface::setFinalLocation (int index, int shift, int x, int y, const Tile& tex)
    { 
        //std::cout << "surface setfinallocation quadslist.size() : " << quadsList.size() << std::endl;
        //quadsList.reserve(quadsList.size()+4);
        
        int halfHeight = tex.getHeight()/2;
        int halfWidth = tex.getWidth()/2;
        
        std::cout << "Surface::setFinalLocation - verif existence du tile : " << &tex << std::endl;
        
        if (&quadsList == nullptr)
            throw std::runtime_error("La liste des quads n'est pas initialisée !");
                
        this->quadsList[index][0].position = sf::Vector2f(x + halfWidth + shift*2*halfWidth, y + halfHeight);
        this->quadsList[index][1].position = sf::Vector2f(x + halfWidth + shift*2*halfWidth, y - halfHeight);
        this->quadsList[index][2].position = sf::Vector2f(x - halfWidth + shift*2*halfWidth, y - halfHeight);
        this->quadsList[index][3].position = sf::Vector2f(x - halfWidth + shift*2*halfWidth, y + halfHeight);
        
        std::cout << "x : " << this->quadsList[index][0].position.x << std::endl;
        std::cout << "y : " << this->quadsList[index][0].position.y << std::endl;
    }
    
    // On fixe les coordonnees du sprite dans la texture initiale
    void Surface::setTextureLocation (int index, const Tile& tex)
    { 
        int halfHeight = tex.getHeight()/2;
        int halfWidth = tex.getWidth()/2;
        int x = tex.getX();
        int y = tex.getY();
        //if(tex.getX()!=xText || tex.getY()!=yText) std::cout << "probleme de coordonnées" << std::endl;
        //std::cout << "surface setfinallocation quadslist.size() : " << quadsList.size() << std::endl;
        this->quadsList[index][0].texCoords = sf::Vector2f(x + halfWidth, y + halfHeight);
        this->quadsList[index][1].texCoords = sf::Vector2f(x + halfWidth, y - halfHeight);
        this->quadsList[index][2].texCoords = sf::Vector2f(x - halfWidth, y - halfHeight);
        this->quadsList[index][3].texCoords = sf::Vector2f(x - halfWidth, y + halfHeight);
    }
    
    void Surface::draw (sf::RenderTarget& target) const
    {
        for (auto elem : quadsList)
            target.draw(elem,&texture);
    }
    
    // Setters and Getters
    const sf::Texture& Surface::getTexture() const
    {
        return this->texture;
    }
    
    void Surface::setTexture(const sf::Texture& texture)
    {
        this->texture = texture;
    }
    
    const std::vector<sf::VertexArray>& Surface::getQuadsList() const
    {
        return this->quadsList;
    }
    
    void Surface::setQuadsList(const std::vector<sf::VertexArray>& quadsList)
    {
        this->quadsList = quadsList;
    }
}
