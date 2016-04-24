//
// Created by storm on 03/04/16.
//

# include "graphicHandler.h"

void GraphicHandler::drawPolygonFromFixtures(b2Fixture* fixtures)
{
    for (b2Fixture* f = fixtures; f; f = f->GetNext())
    {
        sf::ConvexShape polygon;
        polygon.setPointCount(4);
        b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
        //f->Is
        for (int i=0; i < polygonShape->GetVertexCount(); i++)
        {
            b2Vec2 vertex = polygonShape->GetVertex(i);
            polygon.setPoint(i, sf::Vector2f(vertex.x, vertex.y));
        }
        polygon.setOutlineThickness(1.0f);
        polygon.setFillColor(sf::Color::White);
        this->draw(polygon);
    }
}